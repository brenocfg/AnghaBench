#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
typedef  int uintmax_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_int ;
struct mpt_softc {int raid_nonopt_volumes; int /*<<< orphan*/  raid_rescan; struct mpt_raid_disk* raid_disks; TYPE_13__* ioc_page2; struct mpt_raid_volume* raid_volumes; TYPE_12__* ioc_page3; } ;
struct TYPE_17__ {int /*<<< orphan*/  TotalBlocks; int /*<<< orphan*/  BlocksRemaining; } ;
struct mpt_raid_volume {int flags; TYPE_1__ sync_progress; TYPE_6__* config_page; } ;
struct TYPE_19__ {int Flags; } ;
struct TYPE_23__ {TYPE_3__ PhysDiskStatus; } ;
struct mpt_raid_disk {int flags; TYPE_7__ config_page; } ;
struct TYPE_24__ {int VolumePageNumber; } ;
struct TYPE_18__ {int Settings; } ;
struct TYPE_20__ {int Flags; scalar_t__ State; } ;
struct TYPE_22__ {scalar_t__ ResyncRate; TYPE_2__ VolumeSettings; TYPE_4__ VolumeStatus; } ;
struct TYPE_21__ {int PhysDiskNum; } ;
struct TYPE_14__ {int PageLength; } ;
struct TYPE_16__ {int MaxPhysDisks; int MaxVolumes; int NumActiveVolumes; TYPE_8__* RaidVolume; TYPE_11__ Header; } ;
struct TYPE_15__ {int NumPhysDisks; TYPE_5__* PhysDisk; TYPE_11__ Header; } ;
typedef  TYPE_5__ IOC_3_PHYS_DISK ;
typedef  TYPE_6__ CONFIG_PAGE_RAID_VOL_0 ;
typedef  TYPE_7__ CONFIG_PAGE_RAID_PHYS_DISK_0 ;
typedef  TYPE_8__ CONFIG_PAGE_IOC_2_RAID_VOL ;

/* Variables and functions */
#define  MPI_PHYSDISK0_STATUS_FLAG_OUT_OF_SYNC 133 
#define  MPI_PHYSDISK0_STATUS_FLAG_QUIESCED 132 
 int MPI_RAIDVOL0_SETTING_PRIORITY_RESYNC ; 
#define  MPI_RAIDVOL0_STATUS_FLAG_ENABLED 131 
#define  MPI_RAIDVOL0_STATUS_FLAG_QUIESCED 130 
#define  MPI_RAIDVOL0_STATUS_FLAG_RESYNC_IN_PROGRESS 129 
#define  MPI_RAIDVOL0_STATUS_FLAG_VOLUME_INACTIVE 128 
 scalar_t__ MPI_RAIDVOL0_STATUS_STATE_OPTIMAL ; 
 int MPT_RDF_ACTIVE ; 
 int MPT_RDF_ANNOUNCED ; 
 int MPT_RDF_REFERENCED ; 
 int MPT_RDF_UP2DATE ; 
 int MPT_RVF_ACTIVE ; 
 int MPT_RVF_ANNOUNCED ; 
 int MPT_RVF_REFERENCED ; 
 int MPT_RVF_UP2DATE ; 
 scalar_t__ MPT_U64_2_SCALAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  mpt2host_config_page_ioc2 (TYPE_13__*) ; 
 int /*<<< orphan*/  mpt2host_config_page_ioc3 (TYPE_12__*) ; 
 int /*<<< orphan*/  mpt_announce_disk (struct mpt_softc*,struct mpt_raid_disk*) ; 
 int /*<<< orphan*/  mpt_announce_vol (struct mpt_softc*,struct mpt_raid_volume*) ; 
 int /*<<< orphan*/  mpt_disk_prt (struct mpt_softc*,struct mpt_raid_disk*,char*,...) ; 
 int /*<<< orphan*/  mpt_disk_state (struct mpt_raid_disk*) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 
 int /*<<< orphan*/  mpt_prtc (struct mpt_softc*,char*) ; 
 int mpt_read_cur_cfg_page (struct mpt_softc*,int /*<<< orphan*/ ,TYPE_11__*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpt_refresh_raid_disk (struct mpt_softc*,struct mpt_raid_disk*,TYPE_5__*) ; 
 int /*<<< orphan*/  mpt_refresh_raid_vol (struct mpt_softc*,struct mpt_raid_volume*,TYPE_8__*) ; 
 int /*<<< orphan*/  mpt_schedule_raid_refresh (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_verify_mwce (struct mpt_softc*,struct mpt_raid_volume*) ; 
 int /*<<< orphan*/  mpt_verify_resync_rate (struct mpt_softc*,struct mpt_raid_volume*) ; 
 int /*<<< orphan*/  mpt_vol_prt (struct mpt_softc*,struct mpt_raid_volume*,char*,...) ; 
 int mpt_vol_state (struct mpt_raid_volume*) ; 
 int mpt_vol_type (struct mpt_raid_volume*) ; 

__attribute__((used)) static int
mpt_refresh_raid_data(struct mpt_softc *mpt)
{
	CONFIG_PAGE_IOC_2_RAID_VOL *ioc_vol;
	CONFIG_PAGE_IOC_2_RAID_VOL *ioc_last_vol;
	IOC_3_PHYS_DISK *ioc_disk;
	IOC_3_PHYS_DISK *ioc_last_disk;
	CONFIG_PAGE_RAID_VOL_0	*vol_pg;
	size_t len;
	int rv;
	int i;
	u_int nonopt_volumes;

	if (mpt->ioc_page2 == NULL || mpt->ioc_page3 == NULL) {
		return (0);
	}

	/*
	 * Mark all items as unreferenced by the configuration.
	 * This allows us to find, report, and discard stale
	 * entries.
	 */
	for (i = 0; i < mpt->ioc_page2->MaxPhysDisks; i++) {
		mpt->raid_disks[i].flags &= ~MPT_RDF_REFERENCED;
	}
	for (i = 0; i < mpt->ioc_page2->MaxVolumes; i++) {
		mpt->raid_volumes[i].flags &= ~MPT_RVF_REFERENCED;
	}

	/*
	 * Get Physical Disk information.
	 */
	len = mpt->ioc_page3->Header.PageLength * sizeof(uint32_t);
	rv = mpt_read_cur_cfg_page(mpt, /*PageAddress*/0,
				   &mpt->ioc_page3->Header, len,
				   /*sleep_ok*/TRUE, /*timeout_ms*/5000);
	if (rv) {
		mpt_prt(mpt,
		    "mpt_refresh_raid_data: Failed to read IOC Page 3\n");
		return (-1);
	}
	mpt2host_config_page_ioc3(mpt->ioc_page3);

	ioc_disk = mpt->ioc_page3->PhysDisk;
	ioc_last_disk = ioc_disk + mpt->ioc_page3->NumPhysDisks;
	for (; ioc_disk != ioc_last_disk; ioc_disk++) {
		struct mpt_raid_disk *mpt_disk;

		mpt_disk = mpt->raid_disks + ioc_disk->PhysDiskNum;
		mpt_disk->flags |= MPT_RDF_REFERENCED;
		if ((mpt_disk->flags & (MPT_RDF_ACTIVE|MPT_RDF_UP2DATE))
		 != (MPT_RDF_ACTIVE|MPT_RDF_UP2DATE)) {

			mpt_refresh_raid_disk(mpt, mpt_disk, ioc_disk);

		}
		mpt_disk->flags |= MPT_RDF_ACTIVE;
		mpt->raid_rescan++;
	}

	/*
	 * Refresh volume data.
	 */
	len = mpt->ioc_page2->Header.PageLength * sizeof(uint32_t);
	rv = mpt_read_cur_cfg_page(mpt, /*PageAddress*/0,
				   &mpt->ioc_page2->Header, len,
				   /*sleep_ok*/TRUE, /*timeout_ms*/5000);
	if (rv) {
		mpt_prt(mpt, "mpt_refresh_raid_data: "
			"Failed to read IOC Page 2\n");
		return (-1);
	}
	mpt2host_config_page_ioc2(mpt->ioc_page2);

	ioc_vol = mpt->ioc_page2->RaidVolume;
	ioc_last_vol = ioc_vol + mpt->ioc_page2->NumActiveVolumes;
	for (;ioc_vol != ioc_last_vol; ioc_vol++) {
		struct mpt_raid_volume *mpt_vol;

		mpt_vol = mpt->raid_volumes + ioc_vol->VolumePageNumber;
		mpt_vol->flags |= MPT_RVF_REFERENCED;
		vol_pg = mpt_vol->config_page;
		if (vol_pg == NULL)
			continue;
		if (((mpt_vol->flags & (MPT_RVF_ACTIVE|MPT_RVF_UP2DATE))
		  != (MPT_RVF_ACTIVE|MPT_RVF_UP2DATE))
		 || (vol_pg->VolumeStatus.Flags
		   & MPI_RAIDVOL0_STATUS_FLAG_RESYNC_IN_PROGRESS) != 0) {

			mpt_refresh_raid_vol(mpt, mpt_vol, ioc_vol);
		}
		mpt_vol->flags |= MPT_RVF_ACTIVE;
	}

	nonopt_volumes = 0;
	for (i = 0; i < mpt->ioc_page2->MaxVolumes; i++) {
		struct mpt_raid_volume *mpt_vol;
		uint64_t total;
		uint64_t left;
		int m;
		u_int prio;

		mpt_vol = &mpt->raid_volumes[i];

		if ((mpt_vol->flags & MPT_RVF_ACTIVE) == 0) {
			continue;
		}

		vol_pg = mpt_vol->config_page;
		if ((mpt_vol->flags & (MPT_RVF_REFERENCED|MPT_RVF_ANNOUNCED))
		 == MPT_RVF_ANNOUNCED) {
			mpt_vol_prt(mpt, mpt_vol, "No longer configured\n");
			mpt_vol->flags = 0;
			continue;
		}

		if ((mpt_vol->flags & MPT_RVF_ANNOUNCED) == 0) {
			mpt_announce_vol(mpt, mpt_vol);
			mpt_vol->flags |= MPT_RVF_ANNOUNCED;
		}

		if (vol_pg->VolumeStatus.State !=
		    MPI_RAIDVOL0_STATUS_STATE_OPTIMAL)
			nonopt_volumes++;

		if ((mpt_vol->flags & MPT_RVF_UP2DATE) != 0)
			continue;

		mpt_vol->flags |= MPT_RVF_UP2DATE;
		mpt_vol_prt(mpt, mpt_vol, "%s - %s\n",
		    mpt_vol_type(mpt_vol), mpt_vol_state(mpt_vol));
		mpt_verify_mwce(mpt, mpt_vol);

		if (vol_pg->VolumeStatus.Flags == 0) {
			continue;
		}

		mpt_vol_prt(mpt, mpt_vol, "Status (");
		for (m = 1; m <= 0x80; m <<= 1) {
			switch (vol_pg->VolumeStatus.Flags & m) {
			case MPI_RAIDVOL0_STATUS_FLAG_ENABLED:
				mpt_prtc(mpt, " Enabled");
				break;
			case MPI_RAIDVOL0_STATUS_FLAG_QUIESCED:
				mpt_prtc(mpt, " Quiesced");
				break;
			case MPI_RAIDVOL0_STATUS_FLAG_RESYNC_IN_PROGRESS:
				mpt_prtc(mpt, " Re-Syncing");
				break;
			case MPI_RAIDVOL0_STATUS_FLAG_VOLUME_INACTIVE:
				mpt_prtc(mpt, " Inactive");
				break;
			default:
				break;
			}
		}
		mpt_prtc(mpt, " )\n");

		if ((vol_pg->VolumeStatus.Flags
		   & MPI_RAIDVOL0_STATUS_FLAG_RESYNC_IN_PROGRESS) == 0)
			continue;

		mpt_verify_resync_rate(mpt, mpt_vol);

		left = MPT_U64_2_SCALAR(mpt_vol->sync_progress.BlocksRemaining);
		total = MPT_U64_2_SCALAR(mpt_vol->sync_progress.TotalBlocks);
		if (vol_pg->ResyncRate != 0) {

			prio = ((u_int)vol_pg->ResyncRate * 100000) / 0xFF;
			mpt_vol_prt(mpt, mpt_vol, "Rate %d.%d%%\n",
			    prio / 1000, prio % 1000);
		} else {
			prio = vol_pg->VolumeSettings.Settings
			     & MPI_RAIDVOL0_SETTING_PRIORITY_RESYNC;
			mpt_vol_prt(mpt, mpt_vol, "%s Priority Re-Sync\n",
			    prio ? "High" : "Low");
		}
		mpt_vol_prt(mpt, mpt_vol, "%ju of %ju "
			    "blocks remaining\n", (uintmax_t)left,
			    (uintmax_t)total);

		/* Periodically report on sync progress. */
		mpt_schedule_raid_refresh(mpt);
	}

	for (i = 0; i < mpt->ioc_page2->MaxPhysDisks; i++) {
		struct mpt_raid_disk *mpt_disk;
		CONFIG_PAGE_RAID_PHYS_DISK_0 *disk_pg;
		int m;

		mpt_disk = &mpt->raid_disks[i];
		disk_pg = &mpt_disk->config_page;

		if ((mpt_disk->flags & MPT_RDF_ACTIVE) == 0)
			continue;

		if ((mpt_disk->flags & (MPT_RDF_REFERENCED|MPT_RDF_ANNOUNCED))
		 == MPT_RDF_ANNOUNCED) {
			mpt_disk_prt(mpt, mpt_disk, "No longer configured\n");
			mpt_disk->flags = 0;
			mpt->raid_rescan++;
			continue;
		}

		if ((mpt_disk->flags & MPT_RDF_ANNOUNCED) == 0) {

			mpt_announce_disk(mpt, mpt_disk);
			mpt_disk->flags |= MPT_RVF_ANNOUNCED;
		}

		if ((mpt_disk->flags & MPT_RDF_UP2DATE) != 0)
			continue;

		mpt_disk->flags |= MPT_RDF_UP2DATE;
		mpt_disk_prt(mpt, mpt_disk, "%s\n", mpt_disk_state(mpt_disk));
		if (disk_pg->PhysDiskStatus.Flags == 0)
			continue;

		mpt_disk_prt(mpt, mpt_disk, "Status (");
		for (m = 1; m <= 0x80; m <<= 1) {
			switch (disk_pg->PhysDiskStatus.Flags & m) {
			case MPI_PHYSDISK0_STATUS_FLAG_OUT_OF_SYNC:
				mpt_prtc(mpt, " Out-Of-Sync");
				break;
			case MPI_PHYSDISK0_STATUS_FLAG_QUIESCED:
				mpt_prtc(mpt, " Quiesced");
				break;
			default:
				break;
			}
		}
		mpt_prtc(mpt, " )\n");
	}

	mpt->raid_nonopt_volumes = nonopt_volumes;
	return (0);
}