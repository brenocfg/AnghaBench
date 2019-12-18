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
struct pthread {int flags; int /*<<< orphan*/  tid; int /*<<< orphan*/  refcount; int /*<<< orphan*/  force_exit; int /*<<< orphan*/  cycle; int /*<<< orphan*/  state; int /*<<< orphan*/ * specific; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  PANIC (char*,...) ; 
 int /*<<< orphan*/  PS_DEAD ; 
 scalar_t__ SHOULD_REPORT_EVENT (struct pthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TD_DEATH ; 
 int THR_FLAGS_NEED_SUSPEND ; 
 scalar_t__ THR_IN_CRITICAL (struct pthread*) ; 
 int /*<<< orphan*/  THR_LOCK (struct pthread*) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _malloc_thread_cleanup () ; 
 int /*<<< orphan*/  _thr_isthreaded () ; 
 int /*<<< orphan*/  _thr_report_death (struct pthread*) ; 
 int /*<<< orphan*/  _thr_try_gc (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  _thr_umtx_wake (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _thread_active_threads ; 
 int /*<<< orphan*/  _thread_cleanupspecific () ; 
 int atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thr_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
exit_thread(void)
{
	struct pthread *curthread = _get_curthread();

	free(curthread->name);
	curthread->name = NULL;

	/* Check if there is thread specific data: */
	if (curthread->specific != NULL) {
		/* Run the thread-specific data destructors: */
		_thread_cleanupspecific();
	}

	if (!_thr_isthreaded())
		exit(0);

	if (atomic_fetchadd_int(&_thread_active_threads, -1) == 1) {
		exit(0);
		/* Never reach! */
	}

	/* Tell malloc that the thread is exiting. */
	_malloc_thread_cleanup();

	THR_LOCK(curthread);
	curthread->state = PS_DEAD;
	if (curthread->flags & THR_FLAGS_NEED_SUSPEND) {
		curthread->cycle++;
		_thr_umtx_wake(&curthread->cycle, INT_MAX, 0);
	}
	if (!curthread->force_exit && SHOULD_REPORT_EVENT(curthread, TD_DEATH))
		_thr_report_death(curthread);
	/*
	 * Thread was created with initial refcount 1, we drop the
	 * reference count to allow it to be garbage collected.
	 */
	curthread->refcount--;
	_thr_try_gc(curthread, curthread); /* thread lock released */

#if defined(_PTHREADS_INVARIANTS)
	if (THR_IN_CRITICAL(curthread))
		PANIC("thread %p exits with resources held!", curthread);
#endif
	/*
	 * Kernel will do wakeup at the address, so joiner thread
	 * will be resumed if it is sleeping at the address.
	 */
	thr_exit(&curthread->tid);
	PANIC("thr_exit() returned");
	/* Never reach! */
}