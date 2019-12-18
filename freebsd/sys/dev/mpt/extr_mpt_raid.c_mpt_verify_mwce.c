#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct mpt_softc {int raid_mwce_setting; } ;
struct mpt_raid_volume {int flags; TYPE_3__* config_page; } ;
struct mpt_raid_action_result {scalar_t__ action_status; } ;
struct TYPE_11__ {int /*<<< orphan*/  IOCStatus; } ;
typedef  TYPE_2__ request_t ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_13__ {int Settings; } ;
struct TYPE_10__ {int Flags; } ;
struct TYPE_12__ {TYPE_7__ VolumeSettings; TYPE_1__ VolumeStatus; } ;
typedef  TYPE_3__ CONFIG_PAGE_RAID_VOL_0 ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MPI_IOCSTATUS_SUCCESS ; 
 int MPI_RAIDVOL0_SETTING_WRITE_CACHING_ENABLE ; 
 int MPI_RAIDVOL0_STATUS_FLAG_RESYNC_IN_PROGRESS ; 
 scalar_t__ MPI_RAID_ACTION_ASTATUS_SUCCESS ; 
 int /*<<< orphan*/  MPI_RAID_ACTION_CHANGE_VOLUME_SETTINGS ; 
#define  MPT_RAID_MWCE_NC 131 
#define  MPT_RAID_MWCE_OFF 130 
#define  MPT_RAID_MWCE_ON 129 
#define  MPT_RAID_MWCE_REBUILD_ONLY 128 
 int MPT_RVF_WCE_CHANGED ; 
 scalar_t__ REQ_IOCSTATUS (TYPE_2__*) ; 
 struct mpt_raid_action_result* REQ_TO_RAID_ACTION_RESULT (TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_7__*,int) ; 
 int /*<<< orphan*/  mpt_free_request (struct mpt_softc*,TYPE_2__*) ; 
 TYPE_2__* mpt_get_request (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int mpt_issue_raid_req (struct mpt_softc*,struct mpt_raid_volume*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_vol_prt (struct mpt_softc*,struct mpt_raid_volume*,char*,...) ; 

__attribute__((used)) static void
mpt_verify_mwce(struct mpt_softc *mpt, struct mpt_raid_volume *mpt_vol)
{
	request_t *req;
	struct mpt_raid_action_result *ar;
	CONFIG_PAGE_RAID_VOL_0 *vol_pg;
	uint32_t data;
	int rv;
	int resyncing;
	int mwce;

	vol_pg = mpt_vol->config_page;
	resyncing = vol_pg->VolumeStatus.Flags
		  & MPI_RAIDVOL0_STATUS_FLAG_RESYNC_IN_PROGRESS;
	mwce = vol_pg->VolumeSettings.Settings
	     & MPI_RAIDVOL0_SETTING_WRITE_CACHING_ENABLE;

	/*
	 * If the setting matches the configuration,
	 * there is nothing to do.
	 */
	switch (mpt->raid_mwce_setting) {
	case MPT_RAID_MWCE_REBUILD_ONLY:
		if ((resyncing && mwce) || (!resyncing && !mwce)) {
			return;
		}
		mpt_vol->flags ^= MPT_RVF_WCE_CHANGED;
		if ((mpt_vol->flags & MPT_RVF_WCE_CHANGED) == 0) {
			/*
			 * Wait one more status update to see if
			 * resyncing gets enabled.  It gets disabled
			 * temporarilly when WCE is changed.
			 */
			return;
		}
		break;
	case MPT_RAID_MWCE_ON:
		if (mwce)
			return;
		break;
	case MPT_RAID_MWCE_OFF:
		if (!mwce)
			return;
		break;
	case MPT_RAID_MWCE_NC:
		return;
	}

	req = mpt_get_request(mpt, /*sleep_ok*/TRUE);
	if (req == NULL) {
		mpt_vol_prt(mpt, mpt_vol,
			    "mpt_verify_mwce: Get request failed!\n");
		return;
	}

	vol_pg->VolumeSettings.Settings ^=
	    MPI_RAIDVOL0_SETTING_WRITE_CACHING_ENABLE;
	memcpy(&data, &vol_pg->VolumeSettings, sizeof(data));
	vol_pg->VolumeSettings.Settings ^=
	    MPI_RAIDVOL0_SETTING_WRITE_CACHING_ENABLE;
	rv = mpt_issue_raid_req(mpt, mpt_vol, /*disk*/NULL, req,
				MPI_RAID_ACTION_CHANGE_VOLUME_SETTINGS,
				data, /*addr*/0, /*len*/0,
				/*write*/FALSE, /*wait*/TRUE);
	if (rv == ETIMEDOUT) {
		mpt_vol_prt(mpt, mpt_vol, "mpt_verify_mwce: "
			    "Write Cache Enable Timed-out\n");
		return;
	}
	ar = REQ_TO_RAID_ACTION_RESULT(req);
	if (rv != 0
	 || REQ_IOCSTATUS(req) != MPI_IOCSTATUS_SUCCESS
	 || (ar->action_status != MPI_RAID_ACTION_ASTATUS_SUCCESS)) {
		mpt_vol_prt(mpt, mpt_vol, "Write Cache Enable Failed: "
			    "%d:%x:%x\n", rv, req->IOCStatus,
			    ar->action_status);
	} else {
		vol_pg->VolumeSettings.Settings ^=
		    MPI_RAIDVOL0_SETTING_WRITE_CACHING_ENABLE;
	}
	mpt_free_request(mpt, req);
}