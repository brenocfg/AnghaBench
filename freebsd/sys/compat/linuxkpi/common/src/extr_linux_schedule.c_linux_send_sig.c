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
struct thread {int /*<<< orphan*/  td_proc; } ;
struct task_struct {struct thread* task_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdsignal (struct thread*,int) ; 

void
linux_send_sig(int signo, struct task_struct *task)
{
	struct thread *td;

	td = task->task_thread;
	PROC_LOCK(td->td_proc);
	tdsignal(td, signo);
	PROC_UNLOCK(td->td_proc);
}