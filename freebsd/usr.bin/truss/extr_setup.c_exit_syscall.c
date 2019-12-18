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
typedef  size_t u_int ;
struct trussinfo {struct threadinfo* curthread; } ;
struct TYPE_3__ {char** s_args; int /*<<< orphan*/ * args; struct syscall* sc; } ;
struct threadinfo {TYPE_1__ cs; int /*<<< orphan*/  tid; struct procinfo* proc; int /*<<< orphan*/  after; int /*<<< orphan*/  in_syscall; } ;
struct syscall {size_t nargs; TYPE_2__* args; } ;
struct ptrace_sc_ret {scalar_t__ sr_error; int /*<<< orphan*/  sr_retval; } ;
struct ptrace_lwpinfo {int pl_flags; } ;
struct procinfo {int /*<<< orphan*/  pid; int /*<<< orphan*/ * abi; int /*<<< orphan*/  threadlist; } ;
typedef  int /*<<< orphan*/  psr ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {int type; size_t offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OUT ; 
 int PL_FLAG_EXEC ; 
 int /*<<< orphan*/  PT_DETACH ; 
 int /*<<< orphan*/  PT_GET_SC_RET ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/ * find_abi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_proc (struct procinfo*) ; 
 int /*<<< orphan*/  free_syscall (struct threadinfo*) ; 
 char* print_arg (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct trussinfo*) ; 
 int /*<<< orphan*/  print_syscall_ret (struct trussinfo*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
exit_syscall(struct trussinfo *info, struct ptrace_lwpinfo *pl)
{
	struct threadinfo *t;
	struct procinfo *p;
	struct syscall *sc;
	struct ptrace_sc_ret psr;
	u_int i;

	t = info->curthread;
	if (!t->in_syscall)
		return;

	clock_gettime(CLOCK_REALTIME, &t->after);
	p = t->proc;
	if (ptrace(PT_GET_SC_RET, t->tid, (caddr_t)&psr, sizeof(psr)) != 0) {
		free_syscall(t);
		return;
	}

	sc = t->cs.sc;
	/*
	 * Here, we only look for arguments that have OUT masked in --
	 * otherwise, they were handled in enter_syscall().
	 */
	for (i = 0; i < sc->nargs; i++) {
		char *temp;

		if (sc->args[i].type & OUT) {
			/*
			 * If an error occurred, then don't bother
			 * getting the data; it may not be valid.
			 */
			if (psr.sr_error != 0) {
				asprintf(&temp, "0x%lx",
				    t->cs.args[sc->args[i].offset]);
			} else {
				temp = print_arg(&sc->args[i],
				    t->cs.args, psr.sr_retval, info);
			}
			t->cs.s_args[i] = temp;
		}
	}

	print_syscall_ret(info, psr.sr_error, psr.sr_retval);
	free_syscall(t);

	/*
	 * If the process executed a new image, check the ABI.  If the
	 * new ABI isn't supported, stop tracing this process.
	 */
	if (pl->pl_flags & PL_FLAG_EXEC) {
		assert(LIST_NEXT(LIST_FIRST(&p->threadlist), entries) == NULL);
		p->abi = find_abi(p->pid);
		if (p->abi == NULL) {
			if (ptrace(PT_DETACH, p->pid, (caddr_t)1, 0) < 0)
				err(1, "Can not detach the process");
			free_proc(p);
		}
	}
}