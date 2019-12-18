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
struct TYPE_2__ {int HotSparePool; } ;
struct mpt_standalone_disk {TYPE_1__ PhysDiskSettings; } ;
struct mpt_drive_list {int dummy; } ;
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  struct mpt_standalone_disk CONFIG_PAGE_RAID_PHYS_DISK_0 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MPI_RAID_ACTION_CHANGE_PHYSDISK_SETTINGS ; 
 int MPI_RAID_HOT_SPARE_POOL_0 ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int find_volume_spare_pool (int,char*,int*) ; 
 int /*<<< orphan*/  free (struct mpt_standalone_disk*) ; 
 scalar_t__ mpt_create_physdisk (int,struct mpt_standalone_disk*,int /*<<< orphan*/ *) ; 
 int mpt_fetch_disks (int,int*,struct mpt_standalone_disk**) ; 
 int /*<<< orphan*/  mpt_free_pd_list (struct mpt_drive_list*) ; 
 scalar_t__ mpt_lock_physdisk (struct mpt_standalone_disk*) ; 
 int mpt_lookup_drive (struct mpt_drive_list*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ mpt_lookup_standalone_disk (char*,struct mpt_standalone_disk*,int,int*) ; 
 int mpt_open (int /*<<< orphan*/ ) ; 
 struct mpt_standalone_disk* mpt_pd_info (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mpt_drive_list* mpt_pd_list (int) ; 
 int mpt_raid_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_unit ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnc (int,char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
add_spare(int ac, char **av)
{
	CONFIG_PAGE_RAID_PHYS_DISK_0 *info;
	struct mpt_standalone_disk *sdisks;
	struct mpt_drive_list *list;
	U8 PhysDiskNum;
	int error, fd, i, nsdisks, pool;

	if (ac < 2) {
		warnx("add spare: drive required");
		return (EINVAL);
	}
	if (ac > 3) {
		warnx("add spare: extra arguments");
		return (EINVAL);
	}

	fd = mpt_open(mpt_unit);
	if (fd < 0) {
		error = errno;
		warn("mpt_open");
		return (error);
	}

	if (ac == 3) {
		error = find_volume_spare_pool(fd, av[2], &pool);
		if (error) {
			close(fd);
			return (error);
		}
	} else
		pool = MPI_RAID_HOT_SPARE_POOL_0;

	list = mpt_pd_list(fd);
	if (list == NULL)
		return (errno);

	error = mpt_lookup_drive(list, av[1], &PhysDiskNum);
	if (error) {
		error = mpt_fetch_disks(fd, &nsdisks, &sdisks);
		if (error != 0) {
			warn("Failed to fetch standalone disk list");
			mpt_free_pd_list(list);
			close(fd);
			return (error);
		}

		if (mpt_lookup_standalone_disk(av[1], sdisks, nsdisks, &i) <
		    0) {
			error = errno;
			warn("Unable to lookup drive %s", av[1]);
			mpt_free_pd_list(list);
			close(fd);
			return (error);
		}

		if (mpt_lock_physdisk(&sdisks[i]) < 0) {
			mpt_free_pd_list(list);
			close(fd);
			return (errno);
		}

		if (mpt_create_physdisk(fd, &sdisks[i], &PhysDiskNum) < 0) {
			error = errno;
			warn("Failed to create physical disk page");
			mpt_free_pd_list(list);
			close(fd);
			return (error);
		}
		free(sdisks);
	}
	mpt_free_pd_list(list);

	info = mpt_pd_info(fd, PhysDiskNum, NULL);
	if (info == NULL) {
		error = errno;
		warn("Failed to fetch drive info");
		close(fd);
		return (error);
	}

	info->PhysDiskSettings.HotSparePool = pool;
	error = mpt_raid_action(fd, MPI_RAID_ACTION_CHANGE_PHYSDISK_SETTINGS, 0,
	    0, PhysDiskNum, *(U32 *)&info->PhysDiskSettings, NULL, 0, NULL,
	    NULL, 0, NULL, NULL, 0);
	if (error) {
		warnc(error, "Failed to assign spare");
		close(fd);
		return (error);
	}

	free(info);
	close(fd);

	return (0);
}