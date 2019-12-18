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
struct thread {int /*<<< orphan*/  td_name; struct proc* td_proc; } ;
struct thr_set_name_args {scalar_t__ id; int /*<<< orphan*/ * name; } ;
struct proc {int /*<<< orphan*/  p_pid; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  lwpid_t ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ESRCH ; 
 int /*<<< orphan*/  MAXCOMLEN ; 
 int /*<<< orphan*/  PMC_CALL_HOOK_UNLOCKED (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PMC_FN_THR_CREATE_LOG ; 
 scalar_t__ PMC_PROC_IS_USING_PMCS (struct proc*) ; 
 scalar_t__ PMC_SYSTEM_SAMPLING_ACTIVE () ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int copyin (int /*<<< orphan*/ *,char*,int) ; 
 int copyinstr (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_clear_tdname (struct thread*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 struct thread* tdfind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_thr_set_name(struct thread *td, struct thr_set_name_args *uap)
{
	struct proc *p;
	char name[MAXCOMLEN + 1];
	struct thread *ttd;
	int error;

	error = 0;
	name[0] = '\0';
	if (uap->name != NULL) {
		error = copyinstr(uap->name, name, sizeof(name), NULL);
		if (error == ENAMETOOLONG) {
			error = copyin(uap->name, name, sizeof(name) - 1);
			name[sizeof(name) - 1] = '\0';
		}
		if (error)
			return (error);
	}
	p = td->td_proc;
	ttd = tdfind((lwpid_t)uap->id, p->p_pid);
	if (ttd == NULL)
		return (ESRCH);
	strcpy(ttd->td_name, name);
#ifdef HWPMC_HOOKS
	if (PMC_PROC_IS_USING_PMCS(p) || PMC_SYSTEM_SAMPLING_ACTIVE())
		PMC_CALL_HOOK_UNLOCKED(ttd, PMC_FN_THR_CREATE_LOG, NULL);
#endif
#ifdef KTR
	sched_clear_tdname(ttd);
#endif
	PROC_UNLOCK(p);
	return (error);
}