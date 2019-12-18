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
struct TYPE_5__ {struct TYPE_5__* right; struct TYPE_5__* left; int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ md5_tree_t ;

/* Variables and functions */
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void md5_tree_split (md5_tree_t **L, md5_tree_t **R, md5_tree_t *T, unsigned char x[16]) {
  if (!T) { *L = *R = 0; return; }
  if (memcmp (&x[0], &T->x[0], 16) < 0) {
    *R = T;
    md5_tree_split (L, &T->left, T->left, x);
  } else {
    *L = T;
    md5_tree_split (&T->right, R, T->right, x);
  }
}