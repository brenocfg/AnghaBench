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
struct TYPE_8__ {int y; struct TYPE_8__* left; struct TYPE_8__* right; } ;
typedef  TYPE_1__ stree_t ;

/* Variables and functions */
 TYPE_1__* FreedNodes ; 
 TYPE_1__* stree_merge (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static stree_t *stree_prune (stree_t *T, int min_y) {
  if (!T || T->y >= min_y) {
    return T;
  }
  stree_t *R = stree_merge (stree_prune (T->left, min_y), stree_prune (T->right, min_y));
  T->left = FreedNodes;
  FreedNodes = T;
  return R;
}