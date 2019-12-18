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
struct sched_param {int dummy; } ;
struct linux_sched_setparam_args {int /*<<< orphan*/  pid; int /*<<< orphan*/  param; } ;
typedef  int /*<<< orphan*/  sched_param ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int copyin (int /*<<< orphan*/ ,struct sched_param*,int) ; 
 int kern_sched_setparam (struct thread*,struct thread*,struct sched_param*) ; 
 struct thread* linux_tdfind (struct thread*,int /*<<< orphan*/ ,int) ; 

int
linux_sched_setparam(struct thread *td,
    struct linux_sched_setparam_args *uap)
{
	struct sched_param sched_param;
	struct thread *tdt;
	int error;

	error = copyin(uap->param, &sched_param, sizeof(sched_param));
	if (error)
		return (error);

	tdt = linux_tdfind(td, uap->pid, -1);
	if (tdt == NULL)
		return (ESRCH);

	error = kern_sched_setparam(td, tdt, &sched_param);
	PROC_UNLOCK(tdt->td_proc);
	return (error);
}