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
typedef  scalar_t__ vm_ooffset_t ;
typedef  scalar_t__ u_int ;
struct vmspace {int dummy; } ;
struct ucred {int cr_ruid; int /*<<< orphan*/  cr_ruidinfo; } ;
struct timeval {int dummy; } ;
struct thread {scalar_t__ td_kstack; int td_kstack_pages; struct ucred* td_ucred; struct proc* td_proc; } ;
struct proc {int p_pid; int /*<<< orphan*/ * p_ucred; int /*<<< orphan*/  p_ktr; int /*<<< orphan*/  p_mtx; int /*<<< orphan*/  p_klist; int /*<<< orphan*/  p_vmspace; } ;
struct fork_req {int fr_flags; int fr_pages; int fr_pd_flags; int /*<<< orphan*/ * fr_pd_fd; int /*<<< orphan*/  fr_pd_fcaps; scalar_t__* fr_pidp; int /*<<< orphan*/ ** fr_procp; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct thread* FIRST_THREAD_IN_PROC (struct proc*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PD_ALLOWED_AT_FORK ; 
 int /*<<< orphan*/  PRIV_MAXPROC ; 
 int /*<<< orphan*/  PRIV_PROC_LIMIT ; 
 int RFCFDG ; 
 int RFFDG ; 
 int RFFLAGS ; 
 int RFMEM ; 
 int RFPROC ; 
 int RFPROCDESC ; 
 int RFSTOPPED ; 
 int RFTSIGFLAGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFTSIGMASK ; 
 scalar_t__ RFTSIGNUM (int) ; 
 int RFTSIGZMB ; 
 int /*<<< orphan*/  RLIMIT_NPROC ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ _SIG_MAXSIG ; 
 int /*<<< orphan*/  allproc_lock ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  chgproccnt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crhold (struct ucred*) ; 
 int /*<<< orphan*/  do_fork (struct thread*,struct fork_req*,struct proc*,struct thread*,struct vmspace*,struct file*) ; 
 int /*<<< orphan*/  fdclose (struct thread*,struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fork_norfproc (struct thread*,int) ; 
 int hz ; 
 int /*<<< orphan*/  knlist_alloc (int /*<<< orphan*/ *) ; 
 int kstack_pages ; 
 int /*<<< orphan*/  lim_cur (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_proc_destroy (struct proc*) ; 
 int /*<<< orphan*/  mac_proc_init (struct proc*) ; 
 int maxproc ; 
 int /*<<< orphan*/  nprocs ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 scalar_t__ ppsratecheck (struct timeval*,int*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_linkup (struct proc*,struct thread*) ; 
 int /*<<< orphan*/  proc_set_cred_init (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_zone ; 
 int procdesc_falloc (struct thread*,struct file**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  racct_proc_exit (struct proc*) ; 
 int racct_proc_fork (struct proc*,struct proc*) ; 
 int /*<<< orphan*/  swap_reserve (scalar_t__) ; 
 int /*<<< orphan*/  swap_reserve_force (scalar_t__) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 struct thread* thread_alloc (int) ; 
 int /*<<< orphan*/  thread_alloc_stack (struct thread*,int) ; 
 struct proc* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct proc*) ; 
 int /*<<< orphan*/  vm_thread_dispose (struct thread*) ; 
 struct vmspace* vmspace_fork (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  vmspace_free (struct vmspace*) ; 

int
fork1(struct thread *td, struct fork_req *fr)
{
	struct proc *p1, *newproc;
	struct thread *td2;
	struct vmspace *vm2;
	struct ucred *cred;
	struct file *fp_procdesc;
	vm_ooffset_t mem_charged;
	int error, nprocs_new;
	static int curfail;
	static struct timeval lastfail;
	int flags, pages;

	flags = fr->fr_flags;
	pages = fr->fr_pages;

	if ((flags & RFSTOPPED) != 0)
		MPASS(fr->fr_procp != NULL && fr->fr_pidp == NULL);
	else
		MPASS(fr->fr_procp == NULL);

	/* Check for the undefined or unimplemented flags. */
	if ((flags & ~(RFFLAGS | RFTSIGFLAGS(RFTSIGMASK))) != 0)
		return (EINVAL);

	/* Signal value requires RFTSIGZMB. */
	if ((flags & RFTSIGFLAGS(RFTSIGMASK)) != 0 && (flags & RFTSIGZMB) == 0)
		return (EINVAL);

	/* Can't copy and clear. */
	if ((flags & (RFFDG|RFCFDG)) == (RFFDG|RFCFDG))
		return (EINVAL);

	/* Check the validity of the signal number. */
	if ((flags & RFTSIGZMB) != 0 && (u_int)RFTSIGNUM(flags) > _SIG_MAXSIG)
		return (EINVAL);

	if ((flags & RFPROCDESC) != 0) {
		/* Can't not create a process yet get a process descriptor. */
		if ((flags & RFPROC) == 0)
			return (EINVAL);

		/* Must provide a place to put a procdesc if creating one. */
		if (fr->fr_pd_fd == NULL)
			return (EINVAL);

		/* Check if we are using supported flags. */
		if ((fr->fr_pd_flags & ~PD_ALLOWED_AT_FORK) != 0)
			return (EINVAL);
	}

	p1 = td->td_proc;

	/*
	 * Here we don't create a new process, but we divorce
	 * certain parts of a process from itself.
	 */
	if ((flags & RFPROC) == 0) {
		if (fr->fr_procp != NULL)
			*fr->fr_procp = NULL;
		else if (fr->fr_pidp != NULL)
			*fr->fr_pidp = 0;
		return (fork_norfproc(td, flags));
	}

	fp_procdesc = NULL;
	newproc = NULL;
	vm2 = NULL;

	/*
	 * Increment the nprocs resource before allocations occur.
	 * Although process entries are dynamically created, we still
	 * keep a global limit on the maximum number we will
	 * create. There are hard-limits as to the number of processes
	 * that can run, established by the KVA and memory usage for
	 * the process data.
	 *
	 * Don't allow a nonprivileged user to use the last ten
	 * processes; don't let root exceed the limit.
	 */
	nprocs_new = atomic_fetchadd_int(&nprocs, 1) + 1;
	if (nprocs_new >= maxproc - 10) {
		if (priv_check_cred(td->td_ucred, PRIV_MAXPROC) != 0 ||
		    nprocs_new >= maxproc) {
			error = EAGAIN;
			sx_xlock(&allproc_lock);
			if (ppsratecheck(&lastfail, &curfail, 1)) {
				printf("maxproc limit exceeded by uid %u "
				    "(pid %d); see tuning(7) and "
				    "login.conf(5)\n",
				    td->td_ucred->cr_ruid, p1->p_pid);
			}
			sx_xunlock(&allproc_lock);
			goto fail2;
		}
	}

	/*
	 * If required, create a process descriptor in the parent first; we
	 * will abandon it if something goes wrong. We don't finit() until
	 * later.
	 */
	if (flags & RFPROCDESC) {
		error = procdesc_falloc(td, &fp_procdesc, fr->fr_pd_fd,
		    fr->fr_pd_flags, fr->fr_pd_fcaps);
		if (error != 0)
			goto fail2;
	}

	mem_charged = 0;
	if (pages == 0)
		pages = kstack_pages;
	/* Allocate new proc. */
	newproc = uma_zalloc(proc_zone, M_WAITOK);
	td2 = FIRST_THREAD_IN_PROC(newproc);
	if (td2 == NULL) {
		td2 = thread_alloc(pages);
		if (td2 == NULL) {
			error = ENOMEM;
			goto fail2;
		}
		proc_linkup(newproc, td2);
	} else {
		if (td2->td_kstack == 0 || td2->td_kstack_pages != pages) {
			if (td2->td_kstack != 0)
				vm_thread_dispose(td2);
			if (!thread_alloc_stack(td2, pages)) {
				error = ENOMEM;
				goto fail2;
			}
		}
	}

	if ((flags & RFMEM) == 0) {
		vm2 = vmspace_fork(p1->p_vmspace, &mem_charged);
		if (vm2 == NULL) {
			error = ENOMEM;
			goto fail2;
		}
		if (!swap_reserve(mem_charged)) {
			/*
			 * The swap reservation failed. The accounting
			 * from the entries of the copied vm2 will be
			 * subtracted in vmspace_free(), so force the
			 * reservation there.
			 */
			swap_reserve_force(mem_charged);
			error = ENOMEM;
			goto fail2;
		}
	} else
		vm2 = NULL;

	/*
	 * XXX: This is ugly; when we copy resource usage, we need to bump
	 *      per-cred resource counters.
	 */
	proc_set_cred_init(newproc, crhold(td->td_ucred));

	/*
	 * Initialize resource accounting for the child process.
	 */
	error = racct_proc_fork(p1, newproc);
	if (error != 0) {
		error = EAGAIN;
		goto fail1;
	}

#ifdef MAC
	mac_proc_init(newproc);
#endif
	newproc->p_klist = knlist_alloc(&newproc->p_mtx);
	STAILQ_INIT(&newproc->p_ktr);

	/*
	 * Increment the count of procs running with this uid. Don't allow
	 * a nonprivileged user to exceed their current limit.
	 */
	cred = td->td_ucred;
	if (!chgproccnt(cred->cr_ruidinfo, 1, lim_cur(td, RLIMIT_NPROC))) {
		if (priv_check_cred(cred, PRIV_PROC_LIMIT) != 0)
			goto fail0;
		chgproccnt(cred->cr_ruidinfo, 1, 0);
	}

	do_fork(td, fr, newproc, td2, vm2, fp_procdesc);
	return (0);
fail0:
	error = EAGAIN;
#ifdef MAC
	mac_proc_destroy(newproc);
#endif
	racct_proc_exit(newproc);
fail1:
	crfree(newproc->p_ucred);
	newproc->p_ucred = NULL;
fail2:
	if (vm2 != NULL)
		vmspace_free(vm2);
	uma_zfree(proc_zone, newproc);
	if ((flags & RFPROCDESC) != 0 && fp_procdesc != NULL) {
		fdclose(td, fp_procdesc, *fr->fr_pd_fd);
		fdrop(fp_procdesc, td);
	}
	atomic_add_int(&nprocs, -1);
	pause("fork", hz / 2);
	return (error);
}