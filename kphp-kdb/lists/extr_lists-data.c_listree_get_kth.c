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
struct TYPE_9__ {int delta; struct TYPE_9__* right; struct TYPE_9__* left; } ;
typedef  TYPE_1__ tree_ext_small_t ;
struct TYPE_10__ {int N; TYPE_1__** root; } ;
typedef  TYPE_2__ listree_t ;

/* Variables and functions */
 TYPE_1__* NIL ; 
 int NODE_RPOS (TYPE_1__*) ; 
 size_t NODE_TYPE (TYPE_1__*) ; 
 size_t TF_MINUS ; 
 int /*<<< orphan*/  assert (int) ; 
 int in_array (TYPE_2__*,int) ; 
 int in_tree (TYPE_1__*) ; 
 scalar_t__* rpos_to_delta ; 

__attribute__((used)) static int listree_get_kth (listree_t *LT, int k) {
  tree_ext_small_t *T = *LT->root;
  int G_N = LT->N;
  if (k < 0 || k >= G_N + T->delta) {
    return -1;
  }
  int l = k;
  while (T != NIL) {
    /* T->lpos + T->left->delta = # of el. of joined list < T->x */
    if (l < G_N - NODE_RPOS(T) + T->left->delta) {
      T = T->left;
    } else if (l == G_N - NODE_RPOS(T) + T->left->delta && NODE_TYPE(T) != TF_MINUS) {
      return in_tree (T);
    } else {
      l -= T->left->delta + rpos_to_delta[NODE_TYPE(T)];
      T = T->right;
    }      
  }
  assert (l >= 0 && l < G_N);
  //assert (U->A);
  return in_array (LT, l);
}