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
struct TYPE_3__ {int x; int /*<<< orphan*/  extra; scalar_t__ right; scalar_t__ left; } ;
typedef  TYPE_1__ rbtree_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  np ; 
 scalar_t__ zmalloc (int) ; 

__attribute__((used)) static rbtree_t *new_node (int x, int extra, const void *data) {
  //printf ("new_node: np = %d\n", np);
  rbtree_t *N = (rbtree_t *) zmalloc (sizeof (rbtree_t) + 4*extra);
  N->x = x;
  N->left = N->right = 0;
  np++;
  if (extra > 0) {
    memcpy (N->extra, data, extra * 4);
  }
  //printf ("new_node exit: np = %d\n", np);
  return N;
}