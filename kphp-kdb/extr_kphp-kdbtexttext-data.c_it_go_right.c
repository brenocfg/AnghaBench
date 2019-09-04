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
struct TYPE_5__ {int /*<<< orphan*/  x; struct TYPE_5__* right; } ;
typedef  TYPE_1__ tree_ext_t ;
struct iterator {int /*<<< orphan*/  tree_x; TYPE_1__* node; } ;

/* Variables and functions */
 TYPE_1__* NIL ; 
 int /*<<< orphan*/  it_push_stack (struct iterator*,TYPE_1__*) ; 

__attribute__((used)) static inline void it_go_right (struct iterator *cur, tree_ext_t *T) {
  while (T->right != NIL) {
    it_push_stack (cur, T);
    T = T->right;
  }
  cur->node = T;
  cur->tree_x = T->x;
}