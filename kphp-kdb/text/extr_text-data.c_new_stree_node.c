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
struct TYPE_5__ {int x; int y; scalar_t__ right; scalar_t__ left; } ;
typedef  TYPE_1__ stree_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  online_tree_nodes ; 
 TYPE_1__* zmalloc (int) ; 

__attribute__((used)) static inline stree_t *new_stree_node (int x, int y) {
  stree_t *P;
  P = zmalloc (sizeof (stree_t));
  assert (P);
  P->left = P->right = 0;
  P->x = x;
  P->y = y;
  ++online_tree_nodes;
  return P;
}