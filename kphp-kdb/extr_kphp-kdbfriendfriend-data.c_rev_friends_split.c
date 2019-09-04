#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int x1; int x2; struct TYPE_5__* right; struct TYPE_5__* left; } ;
typedef  TYPE_1__ rev_friends_t ;

/* Variables and functions */

__attribute__((used)) static void rev_friends_split (rev_friends_t **L, rev_friends_t **R, rev_friends_t *T, int x1, int x2) {
  if (!T) { *L = *R = 0; return; }
  if (x1 < T->x1 || (x1 == T->x1 && x2 < T->x2)) {
    *R = T;
    rev_friends_split (L, &T->left, T->left, x1, x2);
  } else {
    *L = T;
    rev_friends_split (&T->right, R, T->right, x1, x2);
  }
}