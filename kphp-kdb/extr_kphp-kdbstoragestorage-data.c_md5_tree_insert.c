#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int y; struct TYPE_8__* right; struct TYPE_8__* left; int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ md5_tree_t ;

/* Variables and functions */
 TYPE_1__* md5_new_tree_node (unsigned char*,int,long long) ; 
 int /*<<< orphan*/  md5_tree_split (TYPE_1__**,TYPE_1__**,TYPE_1__*,unsigned char*) ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static md5_tree_t *md5_tree_insert (md5_tree_t *T, unsigned char x[16], int y, long long offset) {
  md5_tree_t *V;
  if (!T) {
    V = md5_new_tree_node (x, y, offset);
    return V;
  }
  if (T->y >= y) {
    if (memcmp (&x[0], &T->x[0], 16) < 0) {
      T->left = md5_tree_insert (T->left, x, y, offset);
    } else {
      T->right = md5_tree_insert (T->right, x, y, offset);
    }
    return T;
  }
  V = md5_new_tree_node (x, y, offset);
  md5_tree_split (&V->left, &V->right, T, x);
  return V;
}