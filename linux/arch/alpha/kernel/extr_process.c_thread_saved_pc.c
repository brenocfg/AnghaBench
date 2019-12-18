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
struct TYPE_3__ {unsigned long ksp; } ;
struct TYPE_4__ {TYPE_1__ pcb; } ;

/* Variables and functions */
 scalar_t__ task_stack_page (struct task_struct*) ; 
 TYPE_2__* task_thread_info (struct task_struct*) ; 

__attribute__((used)) static unsigned long
thread_saved_pc(struct task_struct *t)
{
	unsigned long base = (unsigned long)task_stack_page(t);
	unsigned long fp, sp = task_thread_info(t)->pcb.ksp;

	if (sp > base && sp+6*8 < base + 16*1024) {
		fp = ((unsigned long*)sp)[6];
		if (fp > sp && fp < base + 16*1024)
			return *(unsigned long *)fp;
	}

	return 0;
}