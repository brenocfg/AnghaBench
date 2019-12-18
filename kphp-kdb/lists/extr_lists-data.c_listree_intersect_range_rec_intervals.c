#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* right; int /*<<< orphan*/  x; struct TYPE_9__* left; } ;
typedef  TYPE_1__ tree_ext_small_t ;
typedef  int /*<<< orphan*/  object_id_t ;
struct TYPE_10__ {int N; } ;
typedef  TYPE_2__ listree_t ;

/* Variables and functions */
 int /*<<< orphan*/  LA ; 
 TYPE_1__* NIL ; 
 int NODE_RPOS (TYPE_1__*) ; 
 scalar_t__ NODE_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  OARR_ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TF_MINUS ; 
 scalar_t__ TF_PLUS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  listree_intersect_array_rec_intervals (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ object_id_compare_prefix (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_x (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void listree_intersect_range_rec_intervals (tree_ext_small_t *T, listree_t *LT, int a, int b, object_id_t upper_bound) {
  if (T == NIL) {
    listree_intersect_array_rec_intervals (LT, a, b, upper_bound);
    return;
  }

  int N = LT->N; 
  int c = N - NODE_RPOS(T);		// # of array elements < T->x, i.e. A[0]...A[c-1]
  int lr = c - 1;			// left subtree corresponds to [a .. c-1]
  int rl = c + (NODE_TYPE(T) != TF_PLUS);	// right subtree corresponds to [rl .. b]

  assert (rl <= b + 1);

  if (object_id_compare_prefix (OARR_ENTRY (LA, 0), T->x) <= 0) {
    listree_intersect_range_rec_intervals (T->left, LT, a, lr, T->x);
  }

  if (NODE_TYPE(T) != TF_MINUS) {
    report_x (T->x);
  }

  if (object_id_compare_prefix (OARR_ENTRY (LA, 0), upper_bound) <= 0) {
    listree_intersect_range_rec_intervals (T->right, LT, rl, b, upper_bound);  
  }
}