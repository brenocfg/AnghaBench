#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct mpt_softc {scalar_t__ shutdwn_raid; scalar_t__ raid_wakeup; scalar_t__ raid_rescan; int /*<<< orphan*/ * raid_thread; int /*<<< orphan*/  phydisk_sim; int /*<<< orphan*/  raid_volumes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  MPT_LOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  MPT_UNLOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  PUSER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 
 scalar_t__ mpt_refresh_raid_data (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_schedule_raid_refresh (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_sleep (struct mpt_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ **) ; 
 union ccb* xpt_alloc_ccb () ; 
 int xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_rescan (union ccb*) ; 

__attribute__((used)) static void
mpt_raid_thread(void *arg)
{
	struct mpt_softc *mpt;
	int firstrun;

	mpt = (struct mpt_softc *)arg;
	firstrun = 1;
	MPT_LOCK(mpt);
	while (mpt->shutdwn_raid == 0) {

		if (mpt->raid_wakeup == 0) {
			mpt_sleep(mpt, &mpt->raid_volumes, PUSER, "idle", 0);
			continue;
		}

		mpt->raid_wakeup = 0;

		if (mpt_refresh_raid_data(mpt)) {
			mpt_schedule_raid_refresh(mpt);	/* XX NOT QUITE RIGHT */
			continue;
		}

		/*
		 * Now that we have our first snapshot of RAID data,
		 * allow CAM to access our physical disk bus.
		 */
		if (firstrun) {
			firstrun = 0;
			xpt_release_simq(mpt->phydisk_sim, TRUE);
		}

		if (mpt->raid_rescan != 0) {
			union ccb *ccb;
			int error;

			mpt->raid_rescan = 0;
			MPT_UNLOCK(mpt);

			ccb = xpt_alloc_ccb();

			MPT_LOCK(mpt);
			error = xpt_create_path(&ccb->ccb_h.path, NULL,
			    cam_sim_path(mpt->phydisk_sim),
			    CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD);
			if (error != CAM_REQ_CMP) {
				xpt_free_ccb(ccb);
				mpt_prt(mpt, "Unable to rescan RAID Bus!\n");
			} else {
				xpt_rescan(ccb);
			}
		}
	}
	mpt->raid_thread = NULL;
	wakeup(&mpt->raid_thread);
	MPT_UNLOCK(mpt);
	kproc_exit(0);
}