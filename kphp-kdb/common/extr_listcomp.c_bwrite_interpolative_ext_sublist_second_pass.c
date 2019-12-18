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
 scalar_t__ get_gamma_code_length (int) ; 

__attribute__((used)) static void bwrite_interpolative_ext_sublist_second_pass (struct bitwriter *bw, int *L, int u, int v, int left_subtree_size_threshold, struct left_subtree_bits_array *p, int *redundant_bits) {
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
    int lsb = p->a[p->idx];
    p->idx++;
    if (redundant_bits != NULL) {
      (*redundant_bits) += get_gamma_code_length (lsb + 1);
    }
    bwrite_gamma_code (bw, lsb + 1);
    int tree_bits = -bwrite_get_bits_written (bw);
    bwrite_interpolative_ext_sublist_second_pass (bw, L, u, m, left_subtree_size_threshold, p, redundant_bits);
    tree_bits += bwrite_get_bits_written (bw);
    assert (lsb == tree_bits);
  } else {
    bwrite_interpolative_ext_sublist_second_pass (bw, L, u, m, left_subtree_size_threshold, p, redundant_bits);
  }
  bwrite_interpolative_ext_sublist_second_pass (bw, L, m, v, left_subtree_size_threshold, p, redundant_bits);
}