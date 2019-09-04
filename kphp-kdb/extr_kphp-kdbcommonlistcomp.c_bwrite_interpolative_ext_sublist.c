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
 int /*<<< orphan*/  bwrite_interpolative_ext_sublist_first_pass (struct bitwriter*,int*,int,int,int,struct left_subtree_bits_array*) ; 
 int /*<<< orphan*/  bwrite_interpolative_ext_sublist_second_pass (struct bitwriter*,int*,int,int,int,struct left_subtree_bits_array*,int*) ; 
 int /*<<< orphan*/  dyn_mark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_release (int /*<<< orphan*/ ) ; 
 int get_subtree_array_size (int,int,int) ; 
 int /*<<< orphan*/  memcpy (struct bitwriter*,struct bitwriter*,int) ; 
 int /*<<< orphan*/  zmalloc (int) ; 

void bwrite_interpolative_ext_sublist (struct bitwriter *bw, int *L, int u, int v, int left_subtree_size_threshold, int *redundant_bits) {
  struct bitwriter tmp;
  memcpy (&tmp, bw, sizeof (struct bitwriter));
  unsigned char c = *(bw->ptr);
  struct left_subtree_bits_array p;
  p.n = get_subtree_array_size (u, v, left_subtree_size_threshold);
  dyn_mark_t mrk;
  dyn_mark (mrk);
  p.a = zmalloc (p.n * sizeof (int));
  p.idx = 0;
  bwrite_interpolative_ext_sublist_first_pass (bw, L, u, v, left_subtree_size_threshold, &p);
  memcpy (bw, &tmp, sizeof (struct bitwriter));
  *(bw->ptr) = c;
  p.idx = 0;
  if (redundant_bits != NULL) {
    *redundant_bits = 0;
  }
  bwrite_interpolative_ext_sublist_second_pass (bw, L, u, v, left_subtree_size_threshold, &p, redundant_bits);
  dyn_release (mrk);
}