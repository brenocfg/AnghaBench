#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ x2; scalar_t__ x1; struct TYPE_3__* right; struct TYPE_3__* middle; struct TYPE_3__* left; } ;
typedef  TYPE_1__ tree23_t ;

/* Variables and functions */

__attribute__((used)) static void count_rec (tree23_t *T, int depth, int *A) {
  if (--depth < 0) {
    A[1]++;
    A[0]++;
    if (T->x2 > T->x1) {
      A[0]++;
    }
  } else {
    A[2]++;
    count_rec (T->left, depth, A);
    if (T->x1 < T->x2) {
      A[0]++;
      count_rec (T->middle, depth, A);
    }
    A[0]++;
    count_rec (T->right, depth, A);
  }
}