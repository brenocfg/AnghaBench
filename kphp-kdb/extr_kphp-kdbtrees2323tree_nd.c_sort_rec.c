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
struct TYPE_3__ {int /*<<< orphan*/  x2; int /*<<< orphan*/  x1; struct TYPE_3__* right; struct TYPE_3__* middle; struct TYPE_3__* left; } ;
typedef  TYPE_1__ tree23_t ;

/* Variables and functions */

__attribute__((used)) static int *sort_rec (tree23_t *T, int *st, int depth) {
  if (--depth >= 0) {
    st = sort_rec (T->left, st, depth);
    *st++ = T->x1;
    if (T->x2 > T->x1) {
      st = sort_rec (T->middle, st, depth);
      *st++ = T->x2;
    }
    st = sort_rec (T->right, st, depth);
  } else {
    *st++ = T->x1;
    if (T->x2 > T->x1) {
      *st++ = T->x2;
    }
  }
  return st;
}