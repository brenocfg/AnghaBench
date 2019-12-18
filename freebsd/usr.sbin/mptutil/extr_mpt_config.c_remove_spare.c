#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mpt_drive_list {int dummy; } ;
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_5__ {scalar_t__ HotSparePool; } ;
struct TYPE_6__ {int /*<<< orphan*/  PhysDiskID; int /*<<< orphan*/  PhysDiskBus; TYPE_1__ PhysDiskSettings; } ;
typedef  TYPE_2__ CONFIG_PAGE_RAID_PHYS_DISK_0 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ mpt_delete_physdisk (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_free_pd_list (struct mpt_drive_list*) ; 
 int mpt_lookup_drive (struct mpt_drive_list*,char*,int /*<<< orphan*/ *) ; 
 int mpt_open (int /*<<< orphan*/ ) ; 
 TYPE_2__* mpt_pd_info (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mpt_drive_list* mpt_pd_list (int) ; 
 int /*<<< orphan*/  mpt_rescan_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_unit ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
remove_spare(int ac, char **av)
{
	CONFIG_PAGE_RAID_PHYS_DISK_0 *info;
	struct mpt_drive_list *list;
	U8 PhysDiskNum;
	int error, fd;

	if (ac != 2) {
		warnx("remove spare: drive required");
		return (EINVAL);
	}

	fd = mpt_open(mpt_unit);
	if (fd < 0) {
		error = errno;
		warn("mpt_open");
		return (error);
	}

	list = mpt_pd_list(fd);
	if (list == NULL) {
		close(fd);
		return (errno);
	}

	error = mpt_lookup_drive(list, av[1], &PhysDiskNum);
	if (error) {
		warn("Failed to find drive %s", av[1]);
		close(fd);
		return (error);
	}
	mpt_free_pd_list(list);

	
	info = mpt_pd_info(fd, PhysDiskNum, NULL);
	if (info == NULL) {
		error = errno;
		warn("Failed to fetch drive info");
		close(fd);
		return (error);
	}

	if (info->PhysDiskSettings.HotSparePool == 0) {
		warnx("Drive %u is not a hot spare", PhysDiskNum);
		free(info);
		close(fd);
		return (EINVAL);
	}

	if (mpt_delete_physdisk(fd, PhysDiskNum) < 0) {
		error = errno;
		warn("Failed to delete physical disk page");
		free(info);
		close(fd);
		return (error);
	}

	mpt_rescan_bus(info->PhysDiskBus, info->PhysDiskID);
	free(info);
	close(fd);

	return (0);
}