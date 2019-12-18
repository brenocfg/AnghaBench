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
 int /*<<< orphan*/  ALQ_LOCK (struct alq*) ; 
 int /*<<< orphan*/  ALQ_UNLOCK (struct alq*) ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIRST_THREAD_IN_PROC (int /*<<< orphan*/ ) ; 
 struct alq* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PWAIT ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_FIRST ; 
 int /*<<< orphan*/  ald_active ; 
 int /*<<< orphan*/  ald_deactivate (struct alq*) ; 
 int /*<<< orphan*/  ald_mtx ; 
 int /*<<< orphan*/  ald_proc ; 
 int /*<<< orphan*/  ald_shutdown ; 
 scalar_t__ ald_shutingdown ; 
 int /*<<< orphan*/  ald_thread ; 
 int alq_doio (struct alq*) ; 
 int /*<<< orphan*/  alq_eventhandler_tag ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown_pre_sync ; 
 int /*<<< orphan*/  wakeup_one (struct alq*) ; 

__attribute__((used)) static void
ald_daemon(void)
{
	int needwakeup;
	struct alq *alq;

	ald_thread = FIRST_THREAD_IN_PROC(ald_proc);

	alq_eventhandler_tag = EVENTHANDLER_REGISTER(shutdown_pre_sync,
	    ald_shutdown, NULL, SHUTDOWN_PRI_FIRST);

	ALD_LOCK();

	for (;;) {
		while ((alq = LIST_FIRST(&ald_active)) == NULL &&
		    !ald_shutingdown)
			mtx_sleep(&ald_active, &ald_mtx, PWAIT, "aldslp", 0);

		/* Don't shutdown until all active ALQs are flushed. */
		if (ald_shutingdown && alq == NULL) {
			ALD_UNLOCK();
			break;
		}

		ALQ_LOCK(alq);
		ald_deactivate(alq);
		ALD_UNLOCK();
		needwakeup = alq_doio(alq);
		ALQ_UNLOCK(alq);
		if (needwakeup)
			wakeup_one(alq);
		ALD_LOCK();
	}

	kproc_exit(0);
}