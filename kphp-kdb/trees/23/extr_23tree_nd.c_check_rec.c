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
struct TYPE_3__ {int x1; int x2; struct TYPE_3__* middle; struct TYPE_3__* right; struct TYPE_3__* left; } ;
typedef  TYPE_1__ tree23_t ;

/* Variables and functions */

__attribute__((used)) static int check_rec (tree23_t *T, int ll, int rr, int depth) {
  if (!T) {
    return 0;
  }
  if (T->x1 <= ll || T->x1 >= rr || T->x2 <= ll || T->x2 >= rr) {
    return 0;
  }
  if (T->x1 > T->x2) {
    return 0;
  }
  if (--depth >= 0) {
    if (!check_rec (T->left, ll, T->x1, depth) || 
        !check_rec (T->right, T->x2, rr, depth)) {
      return 0;
    }
    if (T->x1 < T->x2) {
      return check_rec (T->middle, T->x1, T->x2, depth);
    }
  }
  return 1;
}