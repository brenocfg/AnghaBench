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
typedef  TYPE_1__ tree23_t ;

/* Variables and functions */
 int /*<<< orphan*/ * nodes ; 
 int /*<<< orphan*/  np ; 

__attribute__((used)) static tree23_t *new_node2 (int x, tree23_t *l, tree23_t *r) {
  //printf ("new_node: np = %d\n", np);
  tree23_t *ret = (tree23_t *)&nodes[np++];
  ret->x1 = x;
  ret->x2 = x | 1;
  ret->left = l;
  ret->right = r;
  //printf ("new_node exit: np = %d\n", np);
  return ret;
}