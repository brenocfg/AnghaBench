#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int y; int rpos; } ;
typedef  TYPE_1__ tree_ext_t ;
struct TYPE_9__ {int* A; int N; int last_A; int /*<<< orphan*/  root; } ;
typedef  TYPE_2__ listree_t ;

/* Variables and functions */
 TYPE_1__* NIL ; 
 scalar_t__ TF_MINUS ; 
 int TF_PLUS ; 
 int /*<<< orphan*/  assert (int) ; 
 int find_rpos (TYPE_2__*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,TYPE_1__*,int,int*,int,int,int /*<<< orphan*/ ,int,int) ; 
 int lrand48 () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tree_ext_delete (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tree_ext_insert (int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 TYPE_1__* tree_ext_lookup (int /*<<< orphan*/ ,int) ; 

void listree_delete (listree_t *U, int x) {
  int tp, rpos;
  tree_ext_t *T = tree_ext_lookup (U->root, x);

  if (T == NIL) {
    rpos = find_rpos (U, x);
    if (rpos <= 0 || U->A[U->N - rpos] != x) {
      fprintf (stderr, "listree_delete: T=%p rpos=%d U->A=%p U->N=%d U->last_A=%d U->root=%p U->A[N-rpos]=%d x=%d\n", T, rpos, U->A, U->N, U->last_A, U->root, rpos > 0 ? U->A[U->N - rpos] : -1, x);
      assert (rpos > 0 && U->A[U->N - rpos] == x);
    }
    U->root = tree_ext_insert (U->root, x, (lrand48 () << 2) + TF_MINUS, rpos);
  } else {
    tp = T->y & 3;
    rpos = T->rpos;
    assert (tp == TF_PLUS);
    U->root = tree_ext_delete (U->root, x);
//    if (tp != 1) {
//      U->root = tree_ext_insert (U->root, x, (lrand48 () << 2) + 3, rpos);
//    }
  }
}