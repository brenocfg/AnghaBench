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
typedef  int /*<<< orphan*/  pair_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bwrite_coordinates_list (struct bitwriter*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bwrite_gamma_code (struct bitwriter*,int) ; 
 int bwrite_get_bits_written (struct bitwriter*) ; 
 int /*<<< orphan*/  bwrite_interpolative_encode_value (struct bitwriter*,int const,int const) ; 
 int const get_doc_id (int /*<<< orphan*/ *,int*,int const) ; 

__attribute__((used)) static void bwrite_ylist_sublist_first_pass (struct bitwriter *bw, pair_t *P, int *O, int u, int v, int left_subtree_size_threshold, struct left_subtree_bits_array *p) {
  const int sz = v - u;
  if (sz <= 1) { return; }
  const int  m = (u + v) >> 1,
            hi = get_doc_id (P, O, v) - (v - m),
            lo = get_doc_id (P, O, u) + (m - u),
             a = get_doc_id (P, O, m) - lo,
             r = hi - lo + 1;
  bwrite_interpolative_encode_value (bw, a, r);
  bwrite_coordinates_list (bw, P + O[m], O[m+1] - O[m]);
  if (sz >= left_subtree_size_threshold) {
    assert (p->idx < p->n);
    int *q = &p->a[p->idx];
    p->idx++;
    int tree_bits = -bwrite_get_bits_written (bw);
    bwrite_ylist_sublist_first_pass (bw, P, O, u, m, left_subtree_size_threshold, p);
    tree_bits += bwrite_get_bits_written (bw);
    *q = tree_bits;
    bwrite_gamma_code (bw, tree_bits + 1);
  } else {
    bwrite_ylist_sublist_first_pass (bw, P, O, u, m, left_subtree_size_threshold, p);
  }
  bwrite_ylist_sublist_first_pass (bw, P, O, m, v, left_subtree_size_threshold, p);
}