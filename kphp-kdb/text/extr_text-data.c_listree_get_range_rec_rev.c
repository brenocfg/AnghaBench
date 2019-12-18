#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rpos; int delta; int y; int x; struct TYPE_4__* right; struct TYPE_4__* left; } ;
typedef  TYPE_1__ tree_ext_t ;

/* Variables and functions */
 TYPE_1__* NIL ; 
 int* RA ; 
 int TF_MINUS ; 
 int /*<<< orphan*/  assert (int) ; 
 int* y_to_delta ; 

int listree_get_range_rec_rev (int *A, tree_ext_t *T, int N, int a, int b) {
  if (a > b) {
    return 1;
  }
  if (T == NIL) {
    assert (a <= b);
    if (!A) {
      return -2;
    }
    while (a <= b) {
      *--RA = A[a++];
    }
    return 1;
  }
  int c = N - T->rpos + T->left->delta;			/* # of el. of joined list < T->x */
  int c1 = c + ((T->y & 3) == TF_MINUS ? 0 : 1);        /* # of el. of joined list <= T->x */
  int s = T->left->delta + y_to_delta[T->y & 3];
  if (b < c) {
    return listree_get_range_rec_rev (A, T->left, N, a, b);
  }
  if (a >= c1) {
    return listree_get_range_rec_rev (A, T->right, N, a - s, b - s);
  }
  if (listree_get_range_rec_rev (A, T->left, N, a, c-1) < 0) {
    return -2;
  }
  /* now a < c1, b >= c, c <= c1 <= c+1 => a <= c, c1-1 <= b */
  if (c < c1) {
    *--RA = T->x;
  }
  return listree_get_range_rec_rev (A, T->right, N, c1 - s, b - s);
}