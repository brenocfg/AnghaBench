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
struct TYPE_3__ {int x1; int x2; } ;
typedef  TYPE_1__ tree23_t ;

/* Variables and functions */
 int /*<<< orphan*/ * leaves ; 
 int /*<<< orphan*/  lp ; 

__attribute__((used)) static tree23_t *new_leaf (int x) {
  //printf ("new_leaf: lp = %d\n", lp);
  tree23_t *ret = (tree23_t *)&leaves[lp++];
  ret->x1 = ret->x2 = x | 1;
  //printf ("new_leaf exit: lp = %d\n", lp);
  return ret;
}