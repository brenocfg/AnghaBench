#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct TYPE_3__ {unsigned long usp; unsigned long unique; } ;
struct TYPE_4__ {TYPE_1__ pcb; } ;

/* Variables and functions */
 int* regoff ; 
 unsigned long* task_stack_page (struct task_struct*) ; 
 TYPE_2__* task_thread_info (struct task_struct*) ; 
 unsigned long zero ; 

__attribute__((used)) static unsigned long *
get_reg_addr(struct task_struct * task, unsigned long regno)
{
	unsigned long *addr;

	if (regno == 30) {
		addr = &task_thread_info(task)->pcb.usp;
	} else if (regno == 65) {
		addr = &task_thread_info(task)->pcb.unique;
	} else if (regno == 31 || regno > 65) {
		zero = 0;
		addr = &zero;
	} else {
		addr = task_stack_page(task) + regoff[regno];
	}
	return addr;
}