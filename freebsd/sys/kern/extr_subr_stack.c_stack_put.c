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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct stack {scalar_t__ depth; int /*<<< orphan*/ * pcs; } ;

/* Variables and functions */
 scalar_t__ STACK_MAX ; 

int
stack_put(struct stack *st, vm_offset_t pc)
{

	if (st->depth < STACK_MAX) {
		st->pcs[st->depth++] = pc;
		return (0);
	} else
		return (-1);
}