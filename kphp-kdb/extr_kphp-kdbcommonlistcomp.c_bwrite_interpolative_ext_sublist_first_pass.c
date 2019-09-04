#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct left_subtree_bits_array {size_t idx; size_t n; int* a; } ;
struct bitwriter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bwrite_gamma_code (struct bitwriter*,int) ; 
 int bwrite_get_bits_written (struct bitwriter*) ; 
 int /*<<< orphan*/  bwrite_interpolative_encode_value (struct bitwriter*,int const,int const) ; 

__attribute__((used)) static void bwrite_interpolative_ext_sublist_first_pass (struct bitwriter *bw, int *L, int u, int v, int left_subtree_size_threshold, struct left_subtree_bits_array *p) {
  const int sz = v - u;
  if (sz <= 1) { return; }
  const int  m = (u + v) >> 1,
            hi = L[v] - (v - m),
            lo = L[u] + (m - u),
             a = L[m] - lo,
             r = hi - lo + 1;
  bwrite_interpolative_encode_value (bw, a, r);
  if (sz >= left_subtree_size_threshold) {
    assert (p->idx < p->n);
    int *q = &p->a[p->idx];
    p->idx++;
    int tree_bits = -bwrite_get_bits_written (bw);
    bwrite_interpolative_ext_sublist_first_pass (bw, L, u, m, left_subtree_size_threshold, p);
    tree_bits += bwrite_get_bits_written (bw);
    *q = tree_bits;
    bwrite_gamma_code (bw, tree_bits + 1);
  } else {
    bwrite_interpolative_ext_sublist_first_pass (bw, L, u, m, left_subtree_size_threshold, p);
  }
  bwrite_interpolative_ext_sublist_first_pass (bw, L, m, v, left_subtree_size_threshold, p);
}