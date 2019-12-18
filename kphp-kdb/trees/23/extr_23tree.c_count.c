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
struct TYPE_3__ {int x1; int x2; struct TYPE_3__* right; struct TYPE_3__* middle; struct TYPE_3__* left; } ;
typedef  TYPE_1__ tree23_t ;

/* Variables and functions */

__attribute__((used)) static void count (tree23_t *T, int *lc, int *nc, int *cc) {
  if (!T) {
    *lc = 0; *nc = 0; *cc = 0;
    return;
  }
  if (T->x1 & 1) {
    ++*lc;
    ++*cc;
    if (!(T->x2 & 1)) ++*cc;
  } else {
    ++*nc;
    count (T->left, lc, nc, cc);
    if (!(T->x2 & 1)) {
      ++*cc;
      count (T->middle, lc, nc, cc);
    }
    ++*cc;
    count (T->right, lc, nc, cc);
  }
}