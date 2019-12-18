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
struct alq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALD_LOCK () ; 
 int /*<<< orphan*/  ALD_UNLOCK () ; 
 struct alq* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct alq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWAIT ; 
 int /*<<< orphan*/  ald_active ; 
 int /*<<< orphan*/  ald_mtx ; 
 int /*<<< orphan*/  ald_proc ; 
 int /*<<< orphan*/  ald_queues ; 
 int ald_shutingdown ; 
 int /*<<< orphan*/  alq_shutdown (struct alq*) ; 
 int /*<<< orphan*/  aq_link ; 
 int /*<<< orphan*/  mtx_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ald_shutdown(void *arg, int howto)
{
	struct alq *alq;

	ALD_LOCK();

	/* Ensure no new queues can be created. */
	ald_shutingdown = 1;

	/* Shutdown all ALQs prior to terminating the ald_daemon. */
	while ((alq = LIST_FIRST(&ald_queues)) != NULL) {
		LIST_REMOVE(alq, aq_link);
		ALD_UNLOCK();
		alq_shutdown(alq);
		ALD_LOCK();
	}

	/* At this point, all ALQs are flushed and shutdown. */

	/*
	 * Wake ald_daemon so that it exits. It won't be able to do
	 * anything until we mtx_sleep because we hold the ald_mtx.
	 */
	wakeup(&ald_active);

	/* Wait for ald_daemon to exit. */
	mtx_sleep(ald_proc, &ald_mtx, PWAIT, "aldslp", 0);

	ALD_UNLOCK();
}