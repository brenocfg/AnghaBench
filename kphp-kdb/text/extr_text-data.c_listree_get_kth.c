#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int delta; int rpos; int y; int x; struct TYPE_5__* right; struct TYPE_5__* left; } ;
typedef  TYPE_1__ tree_ext_t ;
struct TYPE_6__ {int N; int* A; TYPE_1__* root; } ;
typedef  TYPE_2__ listree_t ;

/* Variables and functions */
 TYPE_1__* NIL ; 
 int TF_MINUS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__* y_to_delta ; 

int listree_get_kth (listree_t *U, int k) {
  tree_ext_t *T = U->root;
  if (k < 0 || k >= U->N + T->delta) {
    return -1;
  }
  int l = k;
  while (T != NIL) {
    /* T->lpos + T->left->delta = # of el. of joined list < T->x */
    if (l < U->N - T->rpos + T->left->delta) {
      T = T->left;
    } else if (l == U->N - T->rpos + T->left->delta && (T->y & 3) != TF_MINUS) {
      return T->x;
    } else {
      l -= T->left->delta + y_to_delta[T->y & 3];
      T = T->right;
    }      
    /* T->lpos + T->left->delta + (...) = # of el. of joined list <= T->x */
    /* ((T->y & 3) != TF_MINUS) == (T->x is in list)
       ((T->y & 3) != TF_MINUS) + y_to_delta[T->y & 3] == (T->x in joined list)
    */
    /* old version, somehow equivalent
    if (l >= T->lpos + T->left->delta + ((T->y & 3) == TF_MINUS ? 0 : 1)) {
//    if (l > T->lpos + T->left->delta + y_to_delta[T->y & 3]) {
//      l -= T->left->delta + ((T->y & 3) == TF_MINUS ? 0 : 1);
      l -= T->left->delta + y_to_delta[T->y & 3];
      T = T->right;
    } else {
      return T->x;
    }
    */
  }
  assert (l >= 0 && l < U->N);
  if (!U->A) {
    return -2;
  } else {
    return U->A[l];
  }
}