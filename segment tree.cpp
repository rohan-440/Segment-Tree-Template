#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9+7;

class Sgt {
public:
    vector<int> v;

    Sgt(int n) {
        v.resize(4 * n, INF);
    }

    void build(vector<int>& arr, int ind, int l, int r) {
        if (l == r) {
            v[ind] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * ind + 1, l, mid);
        build(arr, 2 * ind + 2, mid + 1, r);
        v[ind] = min(v[2 * ind + 1], v[2 * ind + 2]);
    }

    // Range update without lazy propagation: O((r-l+1) * log n)
    void range_update(int ind, int l, int r, int ql, int qr, int val) {
        if (l > qr || r < ql) return; // No overlap
        if (l == r) { // Leaf node
            v[ind] += val;
            return;
        }
        int mid = (l + r) / 2;
        range_update(2 * ind + 1, l, mid, ql, qr, val);
        range_update(2 * ind + 2, mid + 1, r, ql, qr, val);
        v[ind] = min(v[2 * ind + 1], v[2 * ind + 2]);
    }

    int get_min(int ind, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return INF; // No overlap
        if (l >= ql && r <= qr) return v[ind]; // Total overlap
        int mid = (l + r) / 2;
        int left = get_min(2 * ind + 1, l, mid, ql, qr);
        int right = get_min(2 * ind + 2, mid + 1, r, ql, qr);
        return min(left, right);
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    Sgt sgt(n);
    sgt.build(arr, 0, 0, n - 1);

    for (int i = 0; i < q; i++) {
        char type;
        cin >> type;
        if (type == 'q') {
            int l, r;
            cin >> l >> r;
            l--; r--; // Convert to 0-based indexing
            cout << sgt.get_min(0, 0, n - 1, l, r) << endl;
        } else if (type == 'u') {
            int l, r, val;
            cin >> l >> r >> val;
            l--; r--; // Convert to 0-based indexing
            sgt.range_update(0, 0, n - 1, l, r, val);
        }
    }

    return 0;
}
