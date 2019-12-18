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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int active; int /*<<< orphan*/  clear; int /*<<< orphan*/  patrol; int /*<<< orphan*/  rbld; } ;
struct mfi_pd_info {TYPE_1__ prog_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int MFI_DNAME_DEVICE_ID ; 
 int MFI_DNAME_HONOR_OPTS ; 
 int MFI_PD_PROGRESS_CLEAR ; 
 int MFI_PD_PROGRESS_PATROL ; 
 int MFI_PD_PROGRESS_REBUILD ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  mfi_display_progress (char*,int /*<<< orphan*/ *) ; 
 char* mfi_drive_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mfi_lookup_drive (int,char*,int /*<<< orphan*/ *) ; 
 int mfi_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mfi_pd_get_info (int,int /*<<< orphan*/ ,struct mfi_pd_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfi_unit ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int
drive_progress(int ac, char **av)
{
	struct mfi_pd_info info;
	uint16_t device_id;
	int error, fd;

	if (ac != 2) {
		warnx("drive progress: %s", ac > 2 ? "extra arguments" :
		    "drive required");
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
	close(fd);

	/* Display any of the active events. */
	if (info.prog_info.active & MFI_PD_PROGRESS_REBUILD)
		mfi_display_progress("Rebuild", &info.prog_info.rbld);
	if (info.prog_info.active & MFI_PD_PROGRESS_PATROL)
		mfi_display_progress("Patrol Read", &info.prog_info.patrol);
	if (info.prog_info.active & MFI_PD_PROGRESS_CLEAR)
		mfi_display_progress("Clear", &info.prog_info.clear);
	if ((info.prog_info.active & (MFI_PD_PROGRESS_REBUILD |
	    MFI_PD_PROGRESS_PATROL | MFI_PD_PROGRESS_CLEAR)) == 0)
		printf("No activity in progress for drive %s.\n",
		mfi_drive_name(NULL, device_id,
		    MFI_DNAME_DEVICE_ID|MFI_DNAME_HONOR_OPTS));

	return (0);
}