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
struct pthread {int /*<<< orphan*/ * tcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MSG (char*,struct pthread*) ; 
 scalar_t__ MAX_CACHED_THREADS ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THR_LOCK_ACQUIRE (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THR_LOCK_RELEASE (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _tcb_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ free_thread_count ; 
 int /*<<< orphan*/  free_thread_lock ; 
 int /*<<< orphan*/  free_threadq ; 
 int /*<<< orphan*/  tcb_lock ; 
 int /*<<< orphan*/  thr_destroy (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  tle ; 
 int /*<<< orphan*/  total_threads ; 

void
_thr_free(struct pthread *curthread, struct pthread *thread)
{
	DBG_MSG("Freeing thread %p\n", thread);

	/*
	 * Always free tcb, as we only know it is part of RTLD TLS
	 * block, but don't know its detail and can not assume how
	 * it works, so better to avoid caching it here.
	 */
	if (curthread != NULL) {
		THR_LOCK_ACQUIRE(curthread, &tcb_lock);
		_tcb_dtor(thread->tcb);
		THR_LOCK_RELEASE(curthread, &tcb_lock);
	} else {
		_tcb_dtor(thread->tcb);
	}
	thread->tcb = NULL;
	if ((curthread == NULL) || (free_thread_count >= MAX_CACHED_THREADS)) {
		thr_destroy(curthread, thread);
		atomic_fetchadd_int(&total_threads, -1);
	} else {
		/*
		 * Add the thread to the free thread list, this also avoids
		 * pthread id is reused too quickly, may help some buggy apps.
		 */
		THR_LOCK_ACQUIRE(curthread, &free_thread_lock);
		TAILQ_INSERT_TAIL(&free_threadq, thread, tle);
		free_thread_count++;
		THR_LOCK_RELEASE(curthread, &free_thread_lock);
	}
}