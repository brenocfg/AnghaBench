#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u_int ;
struct mpt_softc {int raid_resync_rate; } ;
struct mpt_raid_volume {TYPE_2__* config_page; } ;
struct mpt_raid_action_result {scalar_t__ action_status; } ;
struct TYPE_9__ {int /*<<< orphan*/  IOCStatus; } ;
typedef  TYPE_1__ request_t ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_11__ {int Settings; } ;
struct TYPE_10__ {scalar_t__ ResyncRate; TYPE_6__ VolumeSettings; } ;
typedef  TYPE_2__ CONFIG_PAGE_RAID_VOL_0 ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MPI_IOCSTATUS_SUCCESS ; 
 int MPI_RAIDVOL0_SETTING_PRIORITY_RESYNC ; 
 scalar_t__ MPI_RAID_ACTION_ASTATUS_SUCCESS ; 
 int /*<<< orphan*/  MPI_RAID_ACTION_CHANGE_VOLUME_SETTINGS ; 
 int /*<<< orphan*/  MPI_RAID_ACTION_SET_RESYNC_RATE ; 
 int MPT_RAID_RESYNC_RATE_NC ; 
 scalar_t__ REQ_IOCSTATUS (TYPE_1__*) ; 
 struct mpt_raid_action_result* REQ_TO_RAID_ACTION_RESULT (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (int*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  mpt_free_request (struct mpt_softc*,TYPE_1__*) ; 
 TYPE_1__* mpt_get_request (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int mpt_issue_raid_req (struct mpt_softc*,struct mpt_raid_volume*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_vol_prt (struct mpt_softc*,struct mpt_raid_volume*,char*,...) ; 

__attribute__((used)) static void
mpt_verify_resync_rate(struct mpt_softc *mpt, struct mpt_raid_volume *mpt_vol)
{
	request_t *req;
	struct mpt_raid_action_result *ar;
	CONFIG_PAGE_RAID_VOL_0	*vol_pg;
	u_int prio;
	int rv;

	vol_pg = mpt_vol->config_page;

	if (mpt->raid_resync_rate == MPT_RAID_RESYNC_RATE_NC)
		return;

	/*
	 * If the current RAID resync rate does not
	 * match our configured rate, update it.
	 */
	prio = vol_pg->VolumeSettings.Settings
	     & MPI_RAIDVOL0_SETTING_PRIORITY_RESYNC;
	if (vol_pg->ResyncRate != 0
	 && vol_pg->ResyncRate != mpt->raid_resync_rate) {

		req = mpt_get_request(mpt, /*sleep_ok*/TRUE);
		if (req == NULL) {
			mpt_vol_prt(mpt, mpt_vol, "mpt_verify_resync_rate: "
				    "Get request failed!\n");
			return;
		}

		rv = mpt_issue_raid_req(mpt, mpt_vol, /*disk*/NULL, req,
					MPI_RAID_ACTION_SET_RESYNC_RATE,
					mpt->raid_resync_rate, /*addr*/0,
					/*len*/0, /*write*/FALSE, /*wait*/TRUE);
		if (rv == ETIMEDOUT) {
			mpt_vol_prt(mpt, mpt_vol, "mpt_refresh_raid_data: "
				    "Resync Rate Setting Timed-out\n");
			return;
		}

		ar = REQ_TO_RAID_ACTION_RESULT(req);
		if (rv != 0
		 || REQ_IOCSTATUS(req) != MPI_IOCSTATUS_SUCCESS
		 || (ar->action_status != MPI_RAID_ACTION_ASTATUS_SUCCESS)) {
			mpt_vol_prt(mpt, mpt_vol, "Resync Rate Setting Failed: "
				    "%d:%x:%x\n", rv, req->IOCStatus,
				    ar->action_status);
		} else 
			vol_pg->ResyncRate = mpt->raid_resync_rate;
		mpt_free_request(mpt, req);
	} else if ((prio && mpt->raid_resync_rate < 128)
		|| (!prio && mpt->raid_resync_rate >= 128)) {
		uint32_t data;

		req = mpt_get_request(mpt, /*sleep_ok*/TRUE);
		if (req == NULL) {
			mpt_vol_prt(mpt, mpt_vol, "mpt_verify_resync_rate: "
				    "Get request failed!\n");
			return;
		}

		vol_pg->VolumeSettings.Settings ^=
		    MPI_RAIDVOL0_SETTING_PRIORITY_RESYNC;
		memcpy(&data, &vol_pg->VolumeSettings, sizeof(data));
		vol_pg->VolumeSettings.Settings ^=
		    MPI_RAIDVOL0_SETTING_PRIORITY_RESYNC;
		rv = mpt_issue_raid_req(mpt, mpt_vol, /*disk*/NULL, req,
					MPI_RAID_ACTION_CHANGE_VOLUME_SETTINGS,
					data, /*addr*/0, /*len*/0,
					/*write*/FALSE, /*wait*/TRUE);
		if (rv == ETIMEDOUT) {
			mpt_vol_prt(mpt, mpt_vol, "mpt_refresh_raid_data: "
				    "Resync Rate Setting Timed-out\n");
			return;
		}
		ar = REQ_TO_RAID_ACTION_RESULT(req);
		if (rv != 0
		 || REQ_IOCSTATUS(req) != MPI_IOCSTATUS_SUCCESS
		 || (ar->action_status != MPI_RAID_ACTION_ASTATUS_SUCCESS)) {
			mpt_vol_prt(mpt, mpt_vol, "Resync Rate Setting Failed: "
				    "%d:%x:%x\n", rv, req->IOCStatus,
				    ar->action_status);
		} else {
			vol_pg->VolumeSettings.Settings ^=
			    MPI_RAIDVOL0_SETTING_PRIORITY_RESYNC;
		}

		mpt_free_request(mpt, req);
	}
}