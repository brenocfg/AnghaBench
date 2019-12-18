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
struct mpt_softc {int /*<<< orphan*/  phydisk_sim; int /*<<< orphan*/  unit; int /*<<< orphan*/  raid_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MPT_LOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  MPT_UNLOCK (struct mpt_softc*) ; 
 int kproc_create (int /*<<< orphan*/ ,struct mpt_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_raid_thread ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpt_spawn_raid_thread(struct mpt_softc *mpt)
{
	int error;

	/*
	 * Freeze out any CAM transactions until our thread
	 * is able to run at least once.  We need to update
	 * our RAID pages before acception I/O or we may
	 * reject I/O to an ID we later determine is for a
	 * hidden physdisk.
	 */
	MPT_LOCK(mpt);
	xpt_freeze_simq(mpt->phydisk_sim, 1);
	MPT_UNLOCK(mpt);
	error = kproc_create(mpt_raid_thread, mpt,
	    &mpt->raid_thread, /*flags*/0, /*altstack*/0,
	    "mpt_raid%d", mpt->unit);
	if (error != 0) {
		MPT_LOCK(mpt);
		xpt_release_simq(mpt->phydisk_sim, /*run_queue*/FALSE);
		MPT_UNLOCK(mpt);
	}
	return (error);
}