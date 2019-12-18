#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ HotSparePool; } ;
struct mpt_standalone_disk {int NumActiveVolumes; int NumActivePhysDisks; char* Name; int NumPhysDisks; int NumHotSpares; char* devname; TYPE_3__* HotSpare; TYPE_1__ VolumeSettings; TYPE_2__* PhysDisk; TYPE_4__* RaidVolume; } ;
struct TYPE_8__ {int /*<<< orphan*/  VolumeID; int /*<<< orphan*/  VolumeBus; int /*<<< orphan*/  VolumeType; } ;
struct TYPE_7__ {int PhysDiskNum; int /*<<< orphan*/  HotSparePool; } ;
struct TYPE_6__ {int PhysDiskNum; } ;
typedef  TYPE_2__ RAID_VOL0_PHYS_DISK ;
typedef  TYPE_3__ IOC_5_HOT_SPARE ;
typedef  struct mpt_standalone_disk CONFIG_PAGE_RAID_VOL_1 ;
typedef  struct mpt_standalone_disk CONFIG_PAGE_RAID_VOL_0 ;
typedef  struct mpt_standalone_disk CONFIG_PAGE_RAID_PHYS_DISK_0 ;
typedef  struct mpt_standalone_disk CONFIG_PAGE_IOC_5 ;
typedef  TYPE_4__ CONFIG_PAGE_IOC_2_RAID_VOL ;
typedef  struct mpt_standalone_disk CONFIG_PAGE_IOC_2 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct mpt_standalone_disk*) ; 
 scalar_t__ mpt_fetch_disks (int,int*,struct mpt_standalone_disk**) ; 
 int mpt_open (int) ; 
 struct mpt_standalone_disk* mpt_pd_info (int,int,int /*<<< orphan*/ *) ; 
 char* mpt_raid_level (int /*<<< orphan*/ ) ; 
 struct mpt_standalone_disk* mpt_read_ioc_page (int,int,int /*<<< orphan*/ *) ; 
 int mpt_unit ; 
 struct mpt_standalone_disk* mpt_vol_info (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mpt_standalone_disk* mpt_vol_names (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* mpt_volume_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_pd (struct mpt_standalone_disk*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_spare_pools (scalar_t__) ; 
 int /*<<< orphan*/  print_standalone (struct mpt_standalone_disk*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_vol (struct mpt_standalone_disk*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
show_config(int ac, char **av)
{
	CONFIG_PAGE_IOC_2 *ioc2;
	CONFIG_PAGE_IOC_2_RAID_VOL *vol;
	CONFIG_PAGE_IOC_5 *ioc5;
	IOC_5_HOT_SPARE *spare;
	CONFIG_PAGE_RAID_VOL_0 *vinfo;
	RAID_VOL0_PHYS_DISK *disk;
	CONFIG_PAGE_RAID_VOL_1 *vnames;
	CONFIG_PAGE_RAID_PHYS_DISK_0 *pinfo;
	struct mpt_standalone_disk *sdisks;
	int error, fd, i, j, nsdisks;

	if (ac != 1) {
		warnx("show config: extra arguments");
		return (EINVAL);
	}

	fd = mpt_open(mpt_unit);
	if (fd < 0) {
		error = errno;
		warn("mpt_open");
		return (error);
	}

	/* Get the config from the controller. */
	ioc2 = mpt_read_ioc_page(fd, 2, NULL);
	ioc5 = mpt_read_ioc_page(fd, 5, NULL);
	if (ioc2 == NULL || ioc5 == NULL) {
		error = errno;
		warn("Failed to get config");
		free(ioc2);
		close(fd);
		return (error);
	}
	if (mpt_fetch_disks(fd, &nsdisks, &sdisks) < 0) {
		error = errno;
		warn("Failed to get standalone drive list");
		free(ioc5);
		free(ioc2);
		close(fd);
		return (error);
	}

	/* Dump out the configuration. */
	printf("mpt%d Configuration: %d volumes, %d drives\n",
	    mpt_unit, ioc2->NumActiveVolumes, ioc2->NumActivePhysDisks +
	    nsdisks);
	vol = ioc2->RaidVolume;
	for (i = 0; i < ioc2->NumActiveVolumes; vol++, i++) {
		printf("    volume %s ", mpt_volume_name(vol->VolumeBus,
		    vol->VolumeID));
		vinfo = mpt_vol_info(fd, vol->VolumeBus, vol->VolumeID, NULL);
		if (vinfo == NULL) {
			printf("%s UNKNOWN", mpt_raid_level(vol->VolumeType));
		} else
			print_vol(vinfo, -1);
		vnames = mpt_vol_names(fd, vol->VolumeBus, vol->VolumeID, NULL);
		if (vnames != NULL) {
			if (vnames->Name[0] != '\0')
				printf(" <%s>", vnames->Name);
			free(vnames);
		}
		if (vinfo == NULL) {
			printf("\n");
			continue;
		}
		printf(" spans:\n");
		disk = vinfo->PhysDisk;
		for (j = 0; j < vinfo->NumPhysDisks; disk++, j++) {
			printf("        drive %u ", disk->PhysDiskNum);
			pinfo = mpt_pd_info(fd, disk->PhysDiskNum, NULL);
			if (pinfo != NULL) {
				print_pd(pinfo, -1, 0);
				free(pinfo);
			}
			printf("\n");
		}
		if (vinfo->VolumeSettings.HotSparePool != 0) {
			printf("        spare pools: ");
			print_spare_pools(vinfo->VolumeSettings.HotSparePool);
			printf("\n");
		}
		free(vinfo);
	}

	spare = ioc5->HotSpare;
	for (i = 0; i < ioc5->NumHotSpares; spare++, i++) {
		printf("    spare %u ", spare->PhysDiskNum);
		pinfo = mpt_pd_info(fd, spare->PhysDiskNum, NULL);
		if (pinfo != NULL) {
			print_pd(pinfo, -1, 0);
			free(pinfo);
		}
		printf(" backs pool %d\n", ffs(spare->HotSparePool) - 1);
	}
	for (i = 0; i < nsdisks; i++) {
		printf("    drive %s ", sdisks[i].devname);
		print_standalone(&sdisks[i], -1, 0);
		printf("\n");
	}
	free(ioc2);
	free(ioc5);
	free(sdisks);
	close(fd);

	return (0);
}