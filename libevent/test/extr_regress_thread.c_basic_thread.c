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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct event_base {int dummy; } ;
struct event {int dummy; } ;
struct cond_wait {int lock; int cond; } ;
typedef  int /*<<< orphan*/  THREAD_FN ;

/* Variables and functions */
 int /*<<< orphan*/  EVLOCK_LOCK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVLOCK_UNLOCK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVTHREAD_ALLOC_COND (int) ; 
 int /*<<< orphan*/  EVTHREAD_ALLOC_LOCK (int,int /*<<< orphan*/ ) ; 
 scalar_t__ EVTHREAD_COND_WAIT (int,int) ; 
 int /*<<< orphan*/  EVTHREAD_FREE_COND (int) ; 
 int /*<<< orphan*/  EVTHREAD_FREE_LOCK (int,int /*<<< orphan*/ ) ; 
 int NUM_ITERATIONS ; 
 int NUM_THREADS ; 
 int /*<<< orphan*/  THREAD_RETURN () ; 
 int /*<<< orphan*/  assert (int) ; 
 int count ; 
 int count_lock ; 
 int /*<<< orphan*/  event_base_loopexit (struct event_base*,int /*<<< orphan*/ *) ; 
 scalar_t__ evtimer_add (struct event*,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_assign (struct event*,struct event_base*,int /*<<< orphan*/ ,struct cond_wait*) ; 
 int /*<<< orphan*/  evutil_timerclear (struct timeval*) ; 
 int /*<<< orphan*/  wake_all_timeout ; 

__attribute__((used)) static THREAD_FN
basic_thread(void *arg)
{
	struct cond_wait cw;
	struct event_base *base = arg;
	struct event ev;
	int i = 0;

	EVTHREAD_ALLOC_LOCK(cw.lock, 0);
	EVTHREAD_ALLOC_COND(cw.cond);
	assert(cw.lock);
	assert(cw.cond);

	evtimer_assign(&ev, base, wake_all_timeout, &cw);
	for (i = 0; i < NUM_ITERATIONS; i++) {
		struct timeval tv;
		evutil_timerclear(&tv);
		tv.tv_sec = 0;
		tv.tv_usec = 3000;

		EVLOCK_LOCK(cw.lock, 0);
		/* we need to make sure that event does not happen before
		 * we get to wait on the conditional variable */
		assert(evtimer_add(&ev, &tv) == 0);

		assert(EVTHREAD_COND_WAIT(cw.cond, cw.lock) == 0);
		EVLOCK_UNLOCK(cw.lock, 0);

		EVLOCK_LOCK(count_lock, 0);
		++count;
		EVLOCK_UNLOCK(count_lock, 0);
	}

	/* exit the loop only if all threads fired all timeouts */
	EVLOCK_LOCK(count_lock, 0);
	if (count >= NUM_THREADS * NUM_ITERATIONS)
		event_base_loopexit(base, NULL);
	EVLOCK_UNLOCK(count_lock, 0);

	EVTHREAD_FREE_LOCK(cw.lock, 0);
	EVTHREAD_FREE_COND(cw.cond);

	THREAD_RETURN();
}