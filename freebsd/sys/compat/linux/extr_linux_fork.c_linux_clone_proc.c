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
struct thread {int /*<<< orphan*/ * td_retval; TYPE_1__* td_proc; } ;
struct proc {int p_sigparent; int /*<<< orphan*/  p_pid; } ;
struct linux_emuldata {int /*<<< orphan*/ * child_clear_tid; int /*<<< orphan*/ * child_set_tid; } ;
struct linux_clone_args {int flags; int /*<<< orphan*/  tls; int /*<<< orphan*/  stack; int /*<<< orphan*/ * parent_tidptr; int /*<<< orphan*/ * child_tidptr; } ;
struct fork_req {int fr_flags; struct proc** fr_procp; } ;
typedef  int /*<<< orphan*/  fr ;
struct TYPE_2__ {int /*<<< orphan*/  p_pptr; } ;

/* Variables and functions */
 int EINVAL ; 
 struct thread* FIRST_THREAD_IN_PROC (struct proc*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int LINUX_CLONE_CHILD_CLEARTID ; 
 int LINUX_CLONE_CHILD_SETTID ; 
 int LINUX_CLONE_FILES ; 
 int LINUX_CLONE_FS ; 
 int LINUX_CLONE_PARENT ; 
 int LINUX_CLONE_PARENT_SETTID ; 
 int LINUX_CLONE_SETTLS ; 
 int LINUX_CLONE_SIGHAND ; 
 int LINUX_CLONE_VFORK ; 
 int LINUX_CLONE_VM ; 
 scalar_t__ LINUX_SIG_VALID (int) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  PTROUT (int /*<<< orphan*/ ) ; 
 int RFFDG ; 
 int RFMEM ; 
 int RFPPWAIT ; 
 int RFPROC ; 
 int RFSIGSHARE ; 
 int RFSTOPPED ; 
 int /*<<< orphan*/  SRQ_BORING ; 
 int /*<<< orphan*/  TD_SET_CAN_RUN (struct thread*) ; 
 int /*<<< orphan*/  bzero (struct fork_req*,int) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct linux_emuldata* em_find (struct thread*) ; 
 int fork1 (struct thread*,struct fork_req*) ; 
 int /*<<< orphan*/  linux_msg (struct thread*,char*) ; 
 int /*<<< orphan*/  linux_proc_init (struct thread*,struct thread*,int) ; 
 int /*<<< orphan*/  linux_set_cloned_tls (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_set_upcall_kse (struct thread*,int /*<<< orphan*/ ) ; 
 int linux_to_bsd_signal (int) ; 
 int /*<<< orphan*/  proc_reparent (struct proc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sched_add (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

__attribute__((used)) static int
linux_clone_proc(struct thread *td, struct linux_clone_args *args)
{
	struct fork_req fr;
	int error, ff = RFPROC | RFSTOPPED;
	struct proc *p2;
	struct thread *td2;
	int exit_signal;
	struct linux_emuldata *em;

	exit_signal = args->flags & 0x000000ff;
	if (LINUX_SIG_VALID(exit_signal)) {
		exit_signal = linux_to_bsd_signal(exit_signal);
	} else if (exit_signal != 0)
		return (EINVAL);

	if (args->flags & LINUX_CLONE_VM)
		ff |= RFMEM;
	if (args->flags & LINUX_CLONE_SIGHAND)
		ff |= RFSIGSHARE;
	/*
	 * XXX: In Linux, sharing of fs info (chroot/cwd/umask)
	 * and open files is independent.  In FreeBSD, its in one
	 * structure but in reality it does not cause any problems
	 * because both of these flags are usually set together.
	 */
	if (!(args->flags & (LINUX_CLONE_FILES | LINUX_CLONE_FS)))
		ff |= RFFDG;

	if (args->flags & LINUX_CLONE_PARENT_SETTID)
		if (args->parent_tidptr == NULL)
			return (EINVAL);

	if (args->flags & LINUX_CLONE_VFORK)
		ff |= RFPPWAIT;

	bzero(&fr, sizeof(fr));
	fr.fr_flags = ff;
	fr.fr_procp = &p2;
	error = fork1(td, &fr);
	if (error)
		return (error);

	td2 = FIRST_THREAD_IN_PROC(p2);

	/* create the emuldata */
	linux_proc_init(td, td2, args->flags);

	em = em_find(td2);
	KASSERT(em != NULL, ("clone_proc: emuldata not found.\n"));

	if (args->flags & LINUX_CLONE_CHILD_SETTID)
		em->child_set_tid = args->child_tidptr;
	else
		em->child_set_tid = NULL;

	if (args->flags & LINUX_CLONE_CHILD_CLEARTID)
		em->child_clear_tid = args->child_tidptr;
	else
		em->child_clear_tid = NULL;

	if (args->flags & LINUX_CLONE_PARENT_SETTID) {
		error = copyout(&p2->p_pid, args->parent_tidptr,
		    sizeof(p2->p_pid));
		if (error)
			linux_msg(td, "copyout p_pid failed!");
	}

	PROC_LOCK(p2);
	p2->p_sigparent = exit_signal;
	PROC_UNLOCK(p2);
	/*
	 * In a case of stack = NULL, we are supposed to COW calling process
	 * stack. This is what normal fork() does, so we just keep tf_rsp arg
	 * intact.
	 */
	linux_set_upcall_kse(td2, PTROUT(args->stack));

	if (args->flags & LINUX_CLONE_SETTLS)
		linux_set_cloned_tls(td2, args->tls);

	/*
	 * If CLONE_PARENT is set, then the parent of the new process will be
	 * the same as that of the calling process.
	 */
	if (args->flags & LINUX_CLONE_PARENT) {
		sx_xlock(&proctree_lock);
		PROC_LOCK(p2);
		proc_reparent(p2, td->td_proc->p_pptr, true);
		PROC_UNLOCK(p2);
		sx_xunlock(&proctree_lock);
	}

	/*
	 * Make this runnable after we are finished with it.
	 */
	thread_lock(td2);
	TD_SET_CAN_RUN(td2);
	sched_add(td2, SRQ_BORING);
	thread_unlock(td2);

	td->td_retval[0] = p2->p_pid;

	return (0);
}