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
struct iterator_stack_node {struct iterator_stack_node* prev; } ;

/* Variables and functions */
 struct iterator_stack_node* isn_free ; 

__attribute__((used)) static inline void free_stack_node (struct iterator_stack_node *S) {
  S->prev = isn_free;
  isn_free = S;
}