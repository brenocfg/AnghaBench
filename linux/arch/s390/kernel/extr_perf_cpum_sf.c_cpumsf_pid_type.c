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
typedef  int u32 ;
struct task_struct {int dummy; } ;
struct perf_event {int /*<<< orphan*/  ns; struct perf_event* parent; } ;
typedef  enum pid_type { ____Placeholder_pid_type } pid_type ;

/* Variables and functions */
 int __task_pid_nr_ns (struct task_struct*,int,int /*<<< orphan*/ ) ; 
 struct task_struct* find_task_by_pid_ns (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_pid_ns ; 
 int /*<<< orphan*/  pid_alive (struct task_struct*) ; 

__attribute__((used)) static u32 cpumsf_pid_type(struct perf_event *event,
			   u32 pid, enum pid_type type)
{
	struct task_struct *tsk;

	/* Idle process */
	if (!pid)
		goto out;

	tsk = find_task_by_pid_ns(pid, &init_pid_ns);
	pid = -1;
	if (tsk) {
		/*
		 * Only top level events contain the pid namespace in which
		 * they are created.
		 */
		if (event->parent)
			event = event->parent;
		pid = __task_pid_nr_ns(tsk, type, event->ns);
		/*
		 * See also 1d953111b648
		 * "perf/core: Don't report zero PIDs for exiting tasks".
		 */
		if (!pid && !pid_alive(tsk))
			pid = -1;
	}
out:
	return pid;
}