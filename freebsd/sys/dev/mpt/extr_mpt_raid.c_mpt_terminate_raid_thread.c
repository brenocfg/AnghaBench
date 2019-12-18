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
struct mpt_softc {int shutdwn_raid; int /*<<< orphan*/ * raid_thread; int /*<<< orphan*/  raid_volumes; } ;

/* Variables and functions */
 int /*<<< orphan*/  PUSER ; 
 int /*<<< orphan*/  mpt_sleep (struct mpt_softc*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mpt_terminate_raid_thread(struct mpt_softc *mpt)
{

	if (mpt->raid_thread == NULL) {
		return;
	}
	mpt->shutdwn_raid = 1;
	wakeup(&mpt->raid_volumes);
	/*
	 * Sleep on a slightly different location
	 * for this interlock just for added safety.
	 */
	mpt_sleep(mpt, &mpt->raid_thread, PUSER, "thtrm", 0);
}