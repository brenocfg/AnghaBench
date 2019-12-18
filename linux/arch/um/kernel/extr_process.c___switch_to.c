#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  switch_buf; struct task_struct* prev_sched; } ;
struct task_struct {TYPE_1__ thread; } ;
struct TYPE_6__ {void* prev_sched; } ;
struct TYPE_7__ {TYPE_2__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_switch_to (TYPE_3__*) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  set_current (struct task_struct*) ; 
 int /*<<< orphan*/  switch_threads (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void *__switch_to(struct task_struct *from, struct task_struct *to)
{
	to->thread.prev_sched = from;
	set_current(to);

	switch_threads(&from->thread.switch_buf, &to->thread.switch_buf);
	arch_switch_to(current);

	return current->thread.prev_sched;
}