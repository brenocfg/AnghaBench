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
struct TYPE_5__ {int rpos; int y; int x; int delta; struct TYPE_5__* right; struct TYPE_5__* left; } ;
typedef  TYPE_1__ tree_ext_t ;
struct TYPE_6__ {int N; int* A; TYPE_1__* root; } ;
typedef  TYPE_2__ listree_t ;

/* Variables and functions */
 TYPE_1__* NIL ; 
 int TF_MINUS ; 
 int TF_PLUS ; 
 int /*<<< orphan*/  assert (int) ; 
 int* y_to_delta ; 

__attribute__((used)) static int listree_get_pos (listree_t *U, int x, int inexact) {
  tree_ext_t *T = U->root;
  int G_N = U->N;
  int sd = 0, a = 0, b = G_N - 1;
  while (T != NIL) {
    int c = G_N - T->rpos;		// # of array elements < T->x, i.e. A[0]...A[c-1]
    /* T->lpos + T->left->delta = # of el. of joined list < T->x */
    int node_type = T->y & 3;
    if (x < T->x) {
      T = T->left;
      b = c - 1;  // left subtree corresponds to [a .. c-1]
    } else if (x == T->x) {
      assert (inexact || node_type != TF_MINUS);
      return c + sd + T->left->delta - (node_type == TF_MINUS);
    } else {
      a = c + (node_type != TF_PLUS);	// right subtree corresponds to [rl .. b]
      sd += T->left->delta + y_to_delta[node_type];
      T = T->right;
    }      
  }
  assert (a >= 0 && a <= b + inexact && b < G_N);
  b++;
  a--;
  if (!U->A && b - a > 1) {
    return -2;
  }
  while (b - a > 1) {
    int c = (a + b) >> 1;
    //vkprintf (, "(a = %d, b = %d, c = %d, U->A = %p\n");
    if (x < U->A[c]) {
      b = c;
    } else if (x > U->A[c]) {
      a = c;
    } else {
      c += sd;
      assert (c >= 0 && c < G_N + U->root->delta);
      return c;
    }
  }
  assert (inexact);
  return a + sd;
}