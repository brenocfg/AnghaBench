#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ x; struct TYPE_6__* left; } ;
typedef  TYPE_1__ tree_ext_t ;
struct iterator {int /*<<< orphan*/  array_x; int /*<<< orphan*/  x; scalar_t__ tree_x; TYPE_1__* node; scalar_t__ top; } ;

/* Variables and functions */
 TYPE_1__* NIL ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  it_go_right (struct iterator*,TYPE_1__*) ; 
 TYPE_1__* it_pop_stack (struct iterator*) ; 
 int /*<<< orphan*/  it_relax_x (struct iterator*) ; 

__attribute__((used)) static inline void it_advance_tree (struct iterator *cur) {
  assert (cur->node);
  tree_ext_t *T = cur->node->left;
  if (T != NIL) {
    it_go_right (cur, T);
    it_relax_x (cur);
  } else if (cur->top) {
    T = it_pop_stack (cur);
    cur->node = T;
    cur->tree_x = T->x;
    it_relax_x (cur);
  } else {
    cur->node = 0;
    cur->tree_x = 0;
    cur->x = cur->array_x;
  }
}