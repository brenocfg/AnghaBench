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
struct TYPE_3__ {scalar_t__ x; int cat; struct TYPE_3__* right; struct TYPE_3__* left; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 scalar_t__* LiA ; 
 scalar_t__* LiB ; 

__attribute__((used)) static void tree_set_catlist (tree_t *T, int mask) {
  if (!T) {
    return;
  }
  tree_set_catlist (T->left, mask);
  while (LiA < LiB && *LiA < T->x) {
    LiA++;
  }
  if (LiA < LiB && T->x == *LiA) {
    T->cat |= mask;
    LiA++;
  } else {
    T->cat &= ~mask;
  }
  tree_set_catlist (T->right, mask);
}