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
typedef  int /*<<< orphan*/  tree23_leaf_t ;

/* Variables and functions */
 int /*<<< orphan*/  lp ; 
 scalar_t__ zmalloc (int) ; 

__attribute__((used)) static tree23_t *new_leaf (int x, int extra) {
  tree23_t *L = (tree23_t *) (zmalloc (sizeof (tree23_leaf_t) + 8*extra) + 8*extra);
  L->x1 = L->x2 = x;
  lp++;
  return L;
}