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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct mfi_pd_info {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MFI_DCMD_PD_CLEAR_ABORT ; 
 scalar_t__ MFI_DCMD_PD_CLEAR_START ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  mbox_store_pdref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mfi_dcmd_command (int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int mfi_lookup_drive (int,char*,int /*<<< orphan*/ *) ; 
 int mfi_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mfi_pd_get_info (int,int /*<<< orphan*/ ,struct mfi_pd_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfi_unit ; 
 scalar_t__ strcmp (char*,char*) ; 
 char tolower (char) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
drive_clear(int ac, char **av)
{
	struct mfi_pd_info info;
	uint32_t opcode;
	uint16_t device_id;
	uint8_t mbox[4];
	char *s1;
	int error, fd;

	if (ac != 3) {
		warnx("drive clear: %s", ac > 3 ? "extra arguments" :
		    "drive and action requires");
		return (EINVAL);
	}

	for (s1 = av[2]; *s1 != '\0'; s1++)
		*s1 = tolower(*s1);
	if (strcmp(av[2], "start") == 0)
		opcode = MFI_DCMD_PD_CLEAR_START;
	else if ((strcmp(av[2], "stop") == 0) || (strcmp(av[2], "abort") == 0))
		opcode = MFI_DCMD_PD_CLEAR_ABORT;
	else {
		warnx("drive clear: invalid action, must be 'start' or 'stop'\n");
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

	/* Get the info for this drive. */
	if (mfi_pd_get_info(fd, device_id, &info, NULL) < 0) {
		error = errno;
		warn("Failed to fetch info for drive %u", device_id);
		close(fd);
		return (error);
	}

	mbox_store_pdref(&mbox[0], &info.ref);
	if (mfi_dcmd_command(fd, opcode, NULL, 0, mbox, 4, NULL) < 0) {
		error = errno;
		warn("Failed to %s clear on drive %u",
		    opcode == MFI_DCMD_PD_CLEAR_START ? "start" : "stop",
		    device_id);
		close(fd);
		return (error);
	}

	close(fd);
	return (0);
}