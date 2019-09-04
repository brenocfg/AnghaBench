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
struct TYPE_3__ {int x1; int x2; struct TYPE_3__* middle; struct TYPE_3__* left; struct TYPE_3__* right; } ;
typedef  TYPE_1__ tree23_t ;

/* Variables and functions */

__attribute__((used)) static int tree23_lookup (tree23_t *T, int x) {
  if (!T) return 0;
  while (!(T->x1 & 1)) {
    if (x > T->x2) T = T->right;
    else
    if (x < T->x1) T = T->left;
    else
    if (x == T->x1) return 1;
    else
    if (x < (T->x2 & -2)) T = T->middle;
    else
    return 1;
  }
  return (x == (T->x1 & -2)) || (x == (T->x2 & -2));
}