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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MFI_DCMD_PD_LOCATE_START ; 
 scalar_t__ MFI_DCMD_PD_LOCATE_STOP ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  mbox_store_device_id (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mfi_dcmd_command (int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ *) ; 
 int mfi_lookup_drive (int,char*,int /*<<< orphan*/ *) ; 
 int mfi_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_unit ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int
drive_locate(int ac, char **av)
{
	uint16_t device_id;
	uint32_t opcode;
	int error, fd;
	uint8_t mbox[4];

	if (ac != 3) {
		warnx("locate: %s", ac > 3 ? "extra arguments" :
		    "drive and state required");
		return (EINVAL);
	}

	if (strcasecmp(av[2], "on") == 0 || strcasecmp(av[2], "start") == 0)
		opcode = MFI_DCMD_PD_LOCATE_START;
	else if (strcasecmp(av[2], "off") == 0 ||
	    strcasecmp(av[2], "stop") == 0)
		opcode = MFI_DCMD_PD_LOCATE_STOP;
	else {
		warnx("locate: invalid state %s", av[2]);
		return (EINVAL);
	}

	fd = mfi_open(mfi_unit, O_RDWR);
	if (fd < 0) {
		error = errno;
		warn("mfi_open");
		return (error);
	}

	error = mfi_lookup_drive(fd, av[1], &device_id);
	if (error) {
		close(fd);
		return (error);
	}


	mbox_store_device_id(&mbox[0], device_id);
	mbox[2] = 0;
	mbox[3] = 0;
	if (mfi_dcmd_command(fd, opcode, NULL, 0, mbox, 4, NULL) < 0) {
		error = errno;
		warn("Failed to %s locate on drive %u",
		    opcode == MFI_DCMD_PD_LOCATE_START ? "start" : "stop",
		    device_id);
		close(fd);
		return (error);
	}
	close(fd);

	return (0);
}