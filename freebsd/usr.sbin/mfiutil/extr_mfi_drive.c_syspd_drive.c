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
 int /*<<< orphan*/  MFI_PD_STATE_SYSTEM ; 
 int drive_set_state (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int
syspd_drive(int ac, char **av)
{

	if (ac != 2) {
		warnx("syspd: %s", ac > 2 ? "extra arguments" :
		    "drive required");
		return (EINVAL);
	}

	return (drive_set_state(av[1], MFI_PD_STATE_SYSTEM));
}