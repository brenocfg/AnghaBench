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
struct thread {TYPE_1__* td_ucred; struct proc* td_proc; } ;
struct sbuf {int dummy; } ;
struct proc {int /*<<< orphan*/  p_pid; int /*<<< orphan*/  p_comm; } ;
struct abort2_args {int nargs; int /*<<< orphan*/ * why; int /*<<< orphan*/ * args; } ;
struct TYPE_2__ {int /*<<< orphan*/  cr_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 int SIGABRT ; 
 int SIGKILL ; 
 int copyin (int /*<<< orphan*/ *,void**,int) ; 
 int /*<<< orphan*/  exit1 (struct thread*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_clear (struct sbuf*) ; 
 int sbuf_copyin (struct sbuf*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 
 int /*<<< orphan*/  sbuf_trim (struct sbuf*) ; 

int
sys_abort2(struct thread *td, struct abort2_args *uap)
{
	struct proc *p = td->td_proc;
	struct sbuf *sb;
	void *uargs[16];
	int error, i, sig;

	/*
	 * Do it right now so we can log either proper call of abort2(), or
	 * note, that invalid argument was passed. 512 is big enough to
	 * handle 16 arguments' descriptions with additional comments.
	 */
	sb = sbuf_new(NULL, NULL, 512, SBUF_FIXEDLEN);
	sbuf_clear(sb);
	sbuf_printf(sb, "%s(pid %d uid %d) aborted: ",
	    p->p_comm, p->p_pid, td->td_ucred->cr_uid);
	/*
	 * Since we can't return from abort2(), send SIGKILL in cases, where
	 * abort2() was called improperly
	 */
	sig = SIGKILL;
	/* Prevent from DoSes from user-space. */
	if (uap->nargs < 0 || uap->nargs > 16)
		goto out;
	if (uap->nargs > 0) {
		if (uap->args == NULL)
			goto out;
		error = copyin(uap->args, uargs, uap->nargs * sizeof(void *));
		if (error != 0)
			goto out;
	}
	/*
	 * Limit size of 'reason' string to 128. Will fit even when
	 * maximal number of arguments was chosen to be logged.
	 */
	if (uap->why != NULL) {
		error = sbuf_copyin(sb, uap->why, 128);
		if (error < 0)
			goto out;
	} else {
		sbuf_printf(sb, "(null)");
	}
	if (uap->nargs > 0) {
		sbuf_printf(sb, "(");
		for (i = 0;i < uap->nargs; i++)
			sbuf_printf(sb, "%s%p", i == 0 ? "" : ", ", uargs[i]);
		sbuf_printf(sb, ")");
	}
	/*
	 * Final stage: arguments were proper, string has been
	 * successfully copied from userspace, and copying pointers
	 * from user-space succeed.
	 */
	sig = SIGABRT;
out:
	if (sig == SIGKILL) {
		sbuf_trim(sb);
		sbuf_printf(sb, " (Reason text inaccessible)");
	}
	sbuf_cat(sb, "\n");
	sbuf_finish(sb);
	log(LOG_INFO, "%s", sbuf_data(sb));
	sbuf_delete(sb);
	exit1(td, 0, sig);
	return (0);
}