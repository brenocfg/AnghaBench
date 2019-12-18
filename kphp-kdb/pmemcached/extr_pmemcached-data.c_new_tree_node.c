#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int y; struct TYPE_7__* x; scalar_t__ right; scalar_t__ left; } ;
typedef  TYPE_1__ tree_t ;
typedef  TYPE_1__ hash_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_tree_nodes ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int entry_memory ; 
 TYPE_1__* zzmalloc (int) ; 

__attribute__((used)) static tree_t *new_tree_node (hash_entry_t *x, int y) {
  assert (x);
  tree_t *P;
  P = zzmalloc (sizeof (tree_t));
  assert (P);
  alloc_tree_nodes++;
  P->left = P->right = 0;
  P->x = x;
  P->y = y;
  entry_memory += sizeof (tree_t);
  return P;
}