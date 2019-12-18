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
struct TYPE_2__ {scalar_t__ fsindex; unsigned long fsbase; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 struct task_struct* current ; 
 unsigned long x86_fsbase_read_cpu () ; 
 unsigned long x86_fsgsbase_read_task (struct task_struct*,scalar_t__) ; 

unsigned long x86_fsbase_read_task(struct task_struct *task)
{
	unsigned long fsbase;

	if (task == current)
		fsbase = x86_fsbase_read_cpu();
	else if (task->thread.fsindex == 0)
		fsbase = task->thread.fsbase;
	else
		fsbase = x86_fsgsbase_read_task(task, task->thread.fsindex);

	return fsbase;
}