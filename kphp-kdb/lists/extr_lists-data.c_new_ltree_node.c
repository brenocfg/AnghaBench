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
typedef  int /*<<< orphan*/  ltree_x_t ;
struct TYPE_5__ {int y; int /*<<< orphan*/  x; scalar_t__ right; scalar_t__ left; } ;
typedef  TYPE_1__ ltree_t ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_ltree_nodes ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ltree_node_size ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_list_bytes ; 
 TYPE_1__* zmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ltree_t *new_ltree_node (ltree_x_t x, int y) {
  ltree_t *P = zmalloc (ltree_node_size);
  assert (P);
  alloc_ltree_nodes++;
  P->left = P->right = 0;
  P->y = y;
  #ifndef LISTS_Z
  P->x = x;
  #else
  memcpy (P->x, x, object_list_bytes);
  #endif
  return P;
}