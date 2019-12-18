#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct volume_info {int drive_count; struct drive_info* drives; } ;
struct drive_info {TYPE_5__* info; } ;
struct config_id_state {TYPE_4__* ioc2; } ;
typedef  scalar_t__ U32 ;
struct TYPE_19__ {scalar_t__ PageVersion; } ;
struct TYPE_14__ {int /*<<< orphan*/  HotSparePool; int /*<<< orphan*/  Settings; } ;
struct TYPE_13__ {int /*<<< orphan*/  State; int /*<<< orphan*/  Flags; } ;
struct TYPE_12__ {size_t PageLength; scalar_t__ PageNumber; int /*<<< orphan*/  PageType; } ;
struct TYPE_18__ {int VolumeID; int VolumeBus; int NumPhysDisks; long StripeSize; int MaxLBA; int MaxLBAHigh; TYPE_6__* PhysDisk; int /*<<< orphan*/  VolumeType; TYPE_3__ VolumeSettings; TYPE_2__ VolumeStatus; scalar_t__ VolumeIOC; TYPE_1__ Header; } ;
struct TYPE_17__ {int PhysDiskMap; int PhysDiskNum; } ;
struct TYPE_16__ {scalar_t__ MaxLBA; int PhysDiskNum; int PhysDiskBus; int PhysDiskID; } ;
struct TYPE_15__ {int CapabilitiesFlags; } ;
typedef  TYPE_6__ RAID_VOL0_PHYS_DISK ;
typedef  TYPE_7__ CONFIG_PAGE_RAID_VOL_0 ;
typedef  TYPE_8__ CONFIG_PAGE_HEADER ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_RAID_VOLUME ; 
 int MPI_IOCPAGE2_CAP_FLAGS_RAID_64_BIT_ADDRESSING ; 
 int MPI_RAIDVOL0_PHYSDISK_PRIMARY ; 
 int MPI_RAIDVOL0_PHYSDISK_SECONDARY ; 
 int /*<<< orphan*/  MPI_RAIDVOL0_SETTING_USE_DEFAULTS ; 
 int /*<<< orphan*/  MPI_RAIDVOL0_STATUS_FLAG_ENABLED ; 
 int /*<<< orphan*/  MPI_RAIDVOL0_STATUS_STATE_OPTIMAL ; 
 scalar_t__ MPI_RAIDVOLPAGE0_PAGEVERSION ; 
 int /*<<< orphan*/  MPI_RAID_HOT_SPARE_POOL_0 ; 
 int /*<<< orphan*/  MPI_RAID_VOL_TYPE_IM ; 
 int /*<<< orphan*/  MPI_RAID_VOL_TYPE_IME ; 
 int /*<<< orphan*/  MPI_RAID_VOL_TYPE_IS ; 
#define  RT_RAID0 130 
#define  RT_RAID1 129 
#define  RT_RAID1E 128 
 int /*<<< orphan*/  abort () ; 
 TYPE_7__* calloc (int,size_t) ; 
 int errno ; 
 int find_next_volume (struct config_id_state*) ; 
 int mpt_read_config_page_header (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static CONFIG_PAGE_RAID_VOL_0 *
build_volume(int fd, struct volume_info *info, int raid_type, long stripe_size,
    struct config_id_state *state, int verbose)
{
	CONFIG_PAGE_HEADER header;
	CONFIG_PAGE_RAID_VOL_0 *vol;
	RAID_VOL0_PHYS_DISK *rdisk;
	struct drive_info *dinfo;
        U32 MinLBA;
	uint64_t MaxLBA;
	size_t page_size;
	int error, i;

	error = mpt_read_config_page_header(fd, MPI_CONFIG_PAGETYPE_RAID_VOLUME,
	    0, 0, &header, NULL);
	if (error) {
		errno = error;
		return (NULL);
	}
	if (header.PageVersion > MPI_RAIDVOLPAGE0_PAGEVERSION) {
		warnx("Unsupported RAID volume page 0 version %d",
		    header.PageVersion);
		errno = EOPNOTSUPP;
		return (NULL);
	}
	page_size = sizeof(CONFIG_PAGE_RAID_VOL_0) +
	    sizeof(RAID_VOL0_PHYS_DISK) * (info->drive_count - 1);
	vol = calloc(1, page_size);
	if (vol == NULL)
		return (NULL);

	/* Header */
	vol->Header.PageType = MPI_CONFIG_PAGETYPE_RAID_VOLUME;
	vol->Header.PageNumber = 0;
	vol->Header.PageLength = page_size / 4;

	/* Properties */
	vol->VolumeID = find_next_volume(state);
	vol->VolumeBus = 0;
	vol->VolumeIOC = 0;	/* XXX */
	vol->VolumeStatus.Flags = MPI_RAIDVOL0_STATUS_FLAG_ENABLED;
	vol->VolumeStatus.State = MPI_RAIDVOL0_STATUS_STATE_OPTIMAL;
	vol->VolumeSettings.Settings = MPI_RAIDVOL0_SETTING_USE_DEFAULTS;
	vol->VolumeSettings.HotSparePool = MPI_RAID_HOT_SPARE_POOL_0;
	vol->NumPhysDisks = info->drive_count;

	/* Find the smallest drive. */
	MinLBA = info->drives[0].info->MaxLBA;
	for (i = 1; i < info->drive_count; i++)
		if (info->drives[i].info->MaxLBA < MinLBA)
			MinLBA = info->drives[i].info->MaxLBA;

	/*
	 * Now chop off 512MB at the end to leave room for the
	 * metadata.  The controller might only use 64MB, but we just
	 * chop off the max to be simple.
	 */
	MinLBA -= (512 * 1024 * 1024) / 512;

	switch (raid_type) {
	case RT_RAID0:
		vol->VolumeType = MPI_RAID_VOL_TYPE_IS;
		vol->StripeSize = stripe_size / 512;
		MaxLBA = (uint64_t)MinLBA * info->drive_count;
		break;
	case RT_RAID1:
		vol->VolumeType = MPI_RAID_VOL_TYPE_IM;
		MaxLBA = (uint64_t)MinLBA * (info->drive_count / 2);
		break;
	case RT_RAID1E:
		vol->VolumeType = MPI_RAID_VOL_TYPE_IME;
		vol->StripeSize = stripe_size / 512;
		MaxLBA = (uint64_t)MinLBA * info->drive_count / 2;
		break;
	default:
		/* Pacify gcc. */
		abort();		
	}

	/*
	 * If the controller doesn't support 64-bit addressing and the
	 * new volume is larger than 2^32 blocks, warn the user and
	 * truncate the volume.
	 */
	if (MaxLBA >> 32 != 0 &&
	    !(state->ioc2->CapabilitiesFlags &
	    MPI_IOCPAGE2_CAP_FLAGS_RAID_64_BIT_ADDRESSING)) {
		warnx(
	    "Controller does not support volumes > 2TB, truncating volume.");
		MaxLBA = 0xffffffff;
	}
	vol->MaxLBA = MaxLBA;
	vol->MaxLBAHigh = MaxLBA >> 32;

	/* Populate drives. */
	for (i = 0, dinfo = info->drives, rdisk = vol->PhysDisk;
	     i < info->drive_count; i++, dinfo++, rdisk++) {
		if (verbose)
			printf("Adding drive %u (%u:%u) to volume %u:%u\n",
			    dinfo->info->PhysDiskNum, dinfo->info->PhysDiskBus,
			    dinfo->info->PhysDiskID, vol->VolumeBus,
			    vol->VolumeID);
		if (raid_type == RT_RAID1) {
			if (i == 0)
				rdisk->PhysDiskMap =
				    MPI_RAIDVOL0_PHYSDISK_PRIMARY;
			else
				rdisk->PhysDiskMap =
				    MPI_RAIDVOL0_PHYSDISK_SECONDARY;
		} else
			rdisk->PhysDiskMap = i;
		rdisk->PhysDiskNum = dinfo->info->PhysDiskNum;
	}

	return (vol);
}