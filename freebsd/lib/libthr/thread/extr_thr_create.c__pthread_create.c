#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct thr_param {void (* start_func ) (void*) ;char* tls_base; int tls_size; struct rtprio* rtp; int /*<<< orphan*/  flags; void** parent_tid; void** child_tid; int /*<<< orphan*/  stack_size; int /*<<< orphan*/  stack_base; struct pthread* arg; } ;
struct tcb {int dummy; } ;
struct sched_param {int /*<<< orphan*/  sched_priority; } ;
struct rtprio {int dummy; } ;
struct TYPE_5__ {int cpusetsize; scalar_t__ sched_inherit; int flags; scalar_t__ suspend; int /*<<< orphan*/  sched_policy; int /*<<< orphan*/  prio; int /*<<< orphan*/  stacksize_attr; int /*<<< orphan*/  stackaddr_attr; int /*<<< orphan*/ * cpuset; } ;
struct pthread {void* (* start_routine ) (void*) ;int cancel_enable; int flags; int refcount; int force_exit; int /*<<< orphan*/  cycle; void* tid; int /*<<< orphan*/  state; int /*<<< orphan*/  sigmask; TYPE_1__ attr; scalar_t__ tcb; int /*<<< orphan*/ * mq; scalar_t__ cancel_async; void* arg; int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  struct pthread* pthread_t ;
typedef  TYPE_1__* pthread_attr_t ;
typedef  int /*<<< orphan*/  param ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_LEVEL_WHICH ; 
 int /*<<< orphan*/  CPU_WHICH_TID ; 
 int EAGAIN ; 
 int EPROCLIM ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  PS_DEAD ; 
 int /*<<< orphan*/  PS_RUNNING ; 
 int PTHREAD_CREATE_DETACHED ; 
 scalar_t__ PTHREAD_INHERIT_SCHED ; 
 int PTHREAD_SCOPE_SYSTEM ; 
 scalar_t__ SHOULD_REPORT_EVENT (struct pthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGCANCEL ; 
 int /*<<< orphan*/  SIGDELSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGFILLSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TD_CREATE ; 
 scalar_t__ THR_CREATE_SUSPENDED ; 
 int THR_FLAGS_DETACHED ; 
 int THR_FLAGS_NEED_SUSPEND ; 
 int /*<<< orphan*/  THR_MAGIC ; 
 int /*<<< orphan*/  THR_SYSTEM_SCOPE ; 
 int /*<<< orphan*/  THR_THREAD_LOCK (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  THR_THREAD_UNLOCK (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  TID (struct pthread*) ; 
 void* TID_TERMINATED ; 
 int TMQ_NITEMS ; 
 int /*<<< orphan*/  __sys_sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _malloc_first_thread () ; 
 TYPE_1__ _pthread_attr_default ; 
 int _rtld_get_stack_prot () ; 
 int /*<<< orphan*/  _schedparam_to_rtp (int /*<<< orphan*/ ,struct sched_param*,struct rtprio*) ; 
 struct pthread* _thr_alloc (struct pthread*) ; 
 int /*<<< orphan*/  _thr_check_init () ; 
 int /*<<< orphan*/  _thr_free (struct pthread*,struct pthread*) ; 
 scalar_t__ _thr_isthreaded () ; 
 int /*<<< orphan*/  _thr_link (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  _thr_report_creation (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  _thr_setthreaded (int) ; 
 int /*<<< orphan*/  _thr_stack_fix_protection (struct pthread*) ; 
 int /*<<< orphan*/  _thr_try_gc (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  _thr_umtx_wake (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _thread_active_threads ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ cpuset_setaffinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ create_stack (TYPE_1__*) ; 
 int errno ; 
 int /*<<< orphan*/  memset (struct thr_param*,int /*<<< orphan*/ ,int) ; 
 int thr_new (struct thr_param*,int) ; 
 scalar_t__ thread_start ; 

int
_pthread_create(pthread_t * __restrict thread,
    const pthread_attr_t * __restrict attr, void *(*start_routine) (void *),
    void * __restrict arg)
{
	struct pthread *curthread, *new_thread;
	struct thr_param param;
	struct sched_param sched_param;
	struct rtprio rtp;
	sigset_t set, oset;
	cpuset_t *cpusetp;
	int i, cpusetsize, create_suspended, locked, old_stack_prot, ret;

	cpusetp = NULL;
	ret = cpusetsize = 0;
	_thr_check_init();

	/*
	 * Tell libc and others now they need lock to protect their data.
	 */
	if (_thr_isthreaded() == 0) {
		_malloc_first_thread();
		_thr_setthreaded(1);
	}

	curthread = _get_curthread();
	if ((new_thread = _thr_alloc(curthread)) == NULL)
		return (EAGAIN);

	memset(&param, 0, sizeof(param));

	if (attr == NULL || *attr == NULL)
		/* Use the default thread attributes: */
		new_thread->attr = _pthread_attr_default;
	else {
		new_thread->attr = *(*attr);
		cpusetp = new_thread->attr.cpuset;
		cpusetsize = new_thread->attr.cpusetsize;
		new_thread->attr.cpuset = NULL;
		new_thread->attr.cpusetsize = 0;
	}
	if (new_thread->attr.sched_inherit == PTHREAD_INHERIT_SCHED) {
		/* inherit scheduling contention scope */
		if (curthread->attr.flags & PTHREAD_SCOPE_SYSTEM)
			new_thread->attr.flags |= PTHREAD_SCOPE_SYSTEM;
		else
			new_thread->attr.flags &= ~PTHREAD_SCOPE_SYSTEM;

		new_thread->attr.prio = curthread->attr.prio;
		new_thread->attr.sched_policy = curthread->attr.sched_policy;
	}

	new_thread->tid = TID_TERMINATED;

	old_stack_prot = _rtld_get_stack_prot();
	if (create_stack(&new_thread->attr) != 0) {
		/* Insufficient memory to create a stack: */
		_thr_free(curthread, new_thread);
		return (EAGAIN);
	}
	/*
	 * Write a magic value to the thread structure
	 * to help identify valid ones:
	 */
	new_thread->magic = THR_MAGIC;
	new_thread->start_routine = start_routine;
	new_thread->arg = arg;
	new_thread->cancel_enable = 1;
	new_thread->cancel_async = 0;
	/* Initialize the mutex queue: */
	for (i = 0; i < TMQ_NITEMS; i++)
		TAILQ_INIT(&new_thread->mq[i]);

	/* Initialise hooks in the thread structure: */
	if (new_thread->attr.suspend == THR_CREATE_SUSPENDED) {
		new_thread->flags = THR_FLAGS_NEED_SUSPEND;
		create_suspended = 1;
	} else {
		create_suspended = 0;
	}

	new_thread->state = PS_RUNNING;

	if (new_thread->attr.flags & PTHREAD_CREATE_DETACHED)
		new_thread->flags |= THR_FLAGS_DETACHED;

	/* Add the new thread. */
	new_thread->refcount = 1;
	_thr_link(curthread, new_thread);

	/*
	 * Handle the race between __pthread_map_stacks_exec and
	 * thread linkage.
	 */
	if (old_stack_prot != _rtld_get_stack_prot())
		_thr_stack_fix_protection(new_thread);

	/* Return thread pointer eariler so that new thread can use it. */
	(*thread) = new_thread;
	if (SHOULD_REPORT_EVENT(curthread, TD_CREATE) || cpusetp != NULL) {
		THR_THREAD_LOCK(curthread, new_thread);
		locked = 1;
	} else
		locked = 0;
	param.start_func = (void (*)(void *)) thread_start;
	param.arg = new_thread;
	param.stack_base = new_thread->attr.stackaddr_attr;
	param.stack_size = new_thread->attr.stacksize_attr;
	param.tls_base = (char *)new_thread->tcb;
	param.tls_size = sizeof(struct tcb);
	param.child_tid = &new_thread->tid;
	param.parent_tid = &new_thread->tid;
	param.flags = 0;
	if (new_thread->attr.flags & PTHREAD_SCOPE_SYSTEM)
		param.flags |= THR_SYSTEM_SCOPE;
	if (new_thread->attr.sched_inherit == PTHREAD_INHERIT_SCHED)
		param.rtp = NULL;
	else {
		sched_param.sched_priority = new_thread->attr.prio;
		_schedparam_to_rtp(new_thread->attr.sched_policy,
			&sched_param, &rtp);
		param.rtp = &rtp;
	}

	/* Schedule the new thread. */
	if (create_suspended) {
		SIGFILLSET(set);
		SIGDELSET(set, SIGTRAP);
		__sys_sigprocmask(SIG_SETMASK, &set, &oset);
		new_thread->sigmask = oset;
		SIGDELSET(new_thread->sigmask, SIGCANCEL);
	}

	ret = thr_new(&param, sizeof(param));

	if (ret != 0) {
		ret = errno;
		/*
		 * Translate EPROCLIM into well-known POSIX code EAGAIN.
		 */
		if (ret == EPROCLIM)
			ret = EAGAIN;
	}

	if (create_suspended)
		__sys_sigprocmask(SIG_SETMASK, &oset, NULL);

	if (ret != 0) {
		if (!locked)
			THR_THREAD_LOCK(curthread, new_thread);
		new_thread->state = PS_DEAD;
		new_thread->tid = TID_TERMINATED;
		new_thread->flags |= THR_FLAGS_DETACHED;
		new_thread->refcount--;
		if (new_thread->flags & THR_FLAGS_NEED_SUSPEND) {
			new_thread->cycle++;
			_thr_umtx_wake(&new_thread->cycle, INT_MAX, 0);
		}
		_thr_try_gc(curthread, new_thread); /* thread lock released */
		atomic_add_int(&_thread_active_threads, -1);
	} else if (locked) {
		if (cpusetp != NULL) {
			if (cpuset_setaffinity(CPU_LEVEL_WHICH, CPU_WHICH_TID,
				TID(new_thread), cpusetsize, cpusetp)) {
				ret = errno;
				/* kill the new thread */
				new_thread->force_exit = 1;
				new_thread->flags |= THR_FLAGS_DETACHED;
				_thr_try_gc(curthread, new_thread);
				 /* thread lock released */
				goto out;
			}
		}

		_thr_report_creation(curthread, new_thread);
		THR_THREAD_UNLOCK(curthread, new_thread);
	}
out:
	if (ret)
		(*thread) = 0;
	return (ret);
}