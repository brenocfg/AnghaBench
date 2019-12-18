#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tree_ext_t ;
struct iterator_stack_node {int /*<<< orphan*/ * node; struct iterator_stack_node* prev; } ;
struct iterator {struct iterator_stack_node* top; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_stack_node (struct iterator_stack_node*) ; 

__attribute__((used)) static inline tree_ext_t *it_pop_stack (struct iterator *cur) {
  struct iterator_stack_node *S = cur->top;
  cur->top = S->prev;
  free_stack_node (S);
  return S->node;
}