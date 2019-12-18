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
struct mpt_softc {scalar_t__ shutdwn_recovery; int /*<<< orphan*/ * recovery_thread; int /*<<< orphan*/  request_timeout_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPT_LOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  MPT_UNLOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  PUSER ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_recover_commands (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_sleep (struct mpt_softc*,struct mpt_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
mpt_recovery_thread(void *arg)
{
	struct mpt_softc *mpt;

	mpt = (struct mpt_softc *)arg;
	MPT_LOCK(mpt);
	for (;;) {
		if (TAILQ_EMPTY(&mpt->request_timeout_list) != 0) {
			if (mpt->shutdwn_recovery == 0) {
				mpt_sleep(mpt, mpt, PUSER, "idle", 0);
			}
		}
		if (mpt->shutdwn_recovery != 0) {
			break;
		}
		mpt_recover_commands(mpt);
	}
	mpt->recovery_thread = NULL;
	wakeup(&mpt->recovery_thread);
	MPT_UNLOCK(mpt);
	kproc_exit(0);
}