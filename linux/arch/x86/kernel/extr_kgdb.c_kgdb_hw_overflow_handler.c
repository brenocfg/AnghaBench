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
struct TYPE_3__ {int debugreg6; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {int dummy; } ;
struct perf_sample_data {int dummy; } ;
struct perf_event {int dummy; } ;
struct TYPE_4__ {scalar_t__ enabled; } ;

/* Variables and functions */
 int DR_TRAP0 ; 
 TYPE_2__* breakinfo ; 
 struct task_struct* current ; 

__attribute__((used)) static void kgdb_hw_overflow_handler(struct perf_event *event,
		struct perf_sample_data *data, struct pt_regs *regs)
{
	struct task_struct *tsk = current;
	int i;

	for (i = 0; i < 4; i++)
		if (breakinfo[i].enabled)
			tsk->thread.debugreg6 |= (DR_TRAP0 << i);
}