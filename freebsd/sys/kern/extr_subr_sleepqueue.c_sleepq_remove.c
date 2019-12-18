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
struct thread {void* td_wchan; } ;
struct sleepqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  TD_ON_SLEEPQ (struct thread*) ; 
 int /*<<< orphan*/  kick_proc0 () ; 
 int /*<<< orphan*/  sleepq_lock (void*) ; 
 struct sleepqueue* sleepq_lookup (void*) ; 
 int /*<<< orphan*/  sleepq_release (void*) ; 
 int sleepq_resume_thread (struct sleepqueue*,struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
sleepq_remove(struct thread *td, void *wchan)
{
	struct sleepqueue *sq;
	int wakeup_swapper;

	/*
	 * Look up the sleep queue for this wait channel, then re-check
	 * that the thread is asleep on that channel, if it is not, then
	 * bail.
	 */
	MPASS(wchan != NULL);
	sleepq_lock(wchan);
	sq = sleepq_lookup(wchan);
	/*
	 * We can not lock the thread here as it may be sleeping on a
	 * different sleepq.  However, holding the sleepq lock for this
	 * wchan can guarantee that we do not miss a wakeup for this
	 * channel.  The asserts below will catch any false positives.
	 */
	if (!TD_ON_SLEEPQ(td) || td->td_wchan != wchan) {
		sleepq_release(wchan);
		return;
	}
	/* Thread is asleep on sleep queue sq, so wake it up. */
	thread_lock(td);
	MPASS(sq != NULL);
	MPASS(td->td_wchan == wchan);
	wakeup_swapper = sleepq_resume_thread(sq, td, 0);
	thread_unlock(td);
	sleepq_release(wchan);
	if (wakeup_swapper)
		kick_proc0();
}