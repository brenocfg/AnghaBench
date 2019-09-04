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
struct left_subtree_bits_array {int n; scalar_t__ idx; int /*<<< orphan*/  a; } ;
struct bitwriter {unsigned char* ptr; } ;
typedef  int /*<<< orphan*/  dyn_mark_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bwrite_mlist_sublist_first_pass (struct bitwriter*,int*,int*,int /*<<< orphan*/ ,int const,int,struct left_subtree_bits_array*,int) ; 
 int /*<<< orphan*/  bwrite_mlist_sublist_second_pass (struct bitwriter*,int*,int*,int /*<<< orphan*/ ,int const,int,struct left_subtree_bits_array*,int*,int) ; 
 int /*<<< orphan*/  bwrite_nbits (struct bitwriter*,int,int) ; 
 int /*<<< orphan*/  dyn_mark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_release (int /*<<< orphan*/ ) ; 
 int get_subtree_array_size (int /*<<< orphan*/ ,int const,int) ; 
 int /*<<< orphan*/  memcpy (struct bitwriter*,struct bitwriter*,int) ; 
 int /*<<< orphan*/  zmalloc (int) ; 

void bwrite_mlist (struct bitwriter *bw, int *L, int *M, int K, int left_subtree_size_threshold, int *redundant_bits) {
  assert (L[0] == -1);
  const int v = K + 1;
  int i, all_ones = 1;
  for (i = 1; i <= K; i++) {
    assert (M[i] >= 1);
    if (M[i] > 1) {
      all_ones = 0;
      break;
    }
  }
  struct bitwriter tmp;
  memcpy (&tmp, bw, sizeof (struct bitwriter));
  unsigned char c = *(bw->ptr);
  struct left_subtree_bits_array p;
  p.n = get_subtree_array_size (0, v, left_subtree_size_threshold);
  dyn_mark_t mrk;
  dyn_mark (mrk);
  p.a = zmalloc (p.n * sizeof (int));
  p.idx = 0;
  bwrite_nbits (bw, all_ones, 1);
  bwrite_mlist_sublist_first_pass (bw, L, M, 0, v, left_subtree_size_threshold, &p, all_ones);
  memcpy (bw, &tmp, sizeof (struct bitwriter));
  *(bw->ptr) = c;
  p.idx = 0;
  if (redundant_bits != NULL) {
    *redundant_bits = 0;
  }
  bwrite_nbits (bw, all_ones, 1);
  bwrite_mlist_sublist_second_pass (bw, L, M, 0, v, left_subtree_size_threshold, &p, redundant_bits, all_ones);
  dyn_release (mrk);
}