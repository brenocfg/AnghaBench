#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int id; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 unsigned int MMU_NO_CONTEXT ; 
 int /*<<< orphan*/  _tlbil_pid (unsigned int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

void local_flush_tlb_mm(struct mm_struct *mm)
{
	unsigned int pid;

	preempt_disable();
	pid = mm->context.id;
	if (pid != MMU_NO_CONTEXT)
		_tlbil_pid(pid);
	preempt_enable();
}