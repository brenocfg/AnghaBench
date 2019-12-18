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
typedef  int /*<<< orphan*/  U8 ;

/* Variables and functions */
 int EINVAL ; 
 int MPI_RAID_ACTION_ADATA_DEL_PHYS_DISKS ; 
 int MPI_RAID_ACTION_ADATA_ZERO_LBA0 ; 
 int /*<<< orphan*/  MPI_RAID_ACTION_DELETE_VOLUME ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ mpt_lock_volume (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mpt_lookup_volume (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mpt_open (int /*<<< orphan*/ ) ; 
 int mpt_raid_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_rescan_bus (int,int) ; 
 int /*<<< orphan*/  mpt_unit ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnc (int,char*,...) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
delete_volume(int ac, char **av)
{
	U8 VolumeBus, VolumeID;
	int error, fd;

	if (ac != 2) {
		warnx("delete: volume required");
		return (EINVAL);
	}

	fd = mpt_open(mpt_unit);
	if (fd < 0) {
		error = errno;
		warn("mpt_open");
		return (error);
	}

	error = mpt_lookup_volume(fd, av[1], &VolumeBus, &VolumeID);
	if (error) {
		warnc(error, "Invalid volume %s", av[1]);
		close(fd);
		return (error);
	}

	if (mpt_lock_volume(VolumeBus, VolumeID) < 0) {
		close(fd);
		return (errno);
	}

	error = mpt_raid_action(fd, MPI_RAID_ACTION_DELETE_VOLUME, VolumeBus,
	    VolumeID, 0, MPI_RAID_ACTION_ADATA_DEL_PHYS_DISKS |
	    MPI_RAID_ACTION_ADATA_ZERO_LBA0, NULL, 0, NULL, NULL, 0, NULL,
	    NULL, 0);
	if (error) {
		warnc(error, "Failed to delete volume");
		close(fd);
		return (error);
	}

	mpt_rescan_bus(-1, -1);
	close(fd);

	return (0);
}