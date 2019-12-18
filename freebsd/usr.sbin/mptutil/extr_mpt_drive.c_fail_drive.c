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
 int /*<<< orphan*/  MPI_PHYSDISK0_STATUS_FAILED_REQUESTED ; 
 int /*<<< orphan*/  MPI_RAID_ACTION_FAIL_PHYSDISK ; 
 int drive_set_state (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int
fail_drive(int ac, char **av)
{

	if (ac != 2) {
		warnx("fail: %s", ac > 2 ? "extra arguments" :
		    "drive required");
		return (EINVAL);
	}

	return (drive_set_state(av[1], MPI_RAID_ACTION_FAIL_PHYSDISK,
	    MPI_PHYSDISK0_STATUS_FAILED_REQUESTED, "FAILED"));
}