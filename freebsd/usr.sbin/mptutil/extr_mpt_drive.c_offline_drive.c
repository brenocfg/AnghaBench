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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MPI_PHYSDISK0_STATUS_OFFLINE_REQUESTED ; 
 int /*<<< orphan*/  MPI_RAID_ACTION_PHYSDISK_OFFLINE ; 
 int drive_set_state (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int
offline_drive(int ac, char **av)
{

	if (ac != 2) {
		warnx("offline: %s", ac > 2 ? "extra arguments" :
		    "drive required");
		return (EINVAL);
	}

	return (drive_set_state(av[1], MPI_RAID_ACTION_PHYSDISK_OFFLINE,
	    MPI_PHYSDISK0_STATUS_OFFLINE_REQUESTED, "OFFLINE"));
}