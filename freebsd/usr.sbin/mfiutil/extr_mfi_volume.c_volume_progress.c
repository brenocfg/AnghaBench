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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int active; int /*<<< orphan*/  recon; int /*<<< orphan*/  fgi; int /*<<< orphan*/  bgi; int /*<<< orphan*/  cc; } ;
struct mfi_ld_info {TYPE_1__ progress; } ;

/* Variables and functions */
 int EINVAL ; 
 int MFI_LD_PROGRESS_BGI ; 
 int MFI_LD_PROGRESS_CC ; 
 int MFI_LD_PROGRESS_FGI ; 
 int MFI_LD_PROGRESS_RECON ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  mfi_display_progress (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ mfi_ld_get_info (int,int /*<<< orphan*/ ,struct mfi_ld_info*,int /*<<< orphan*/ *) ; 
 scalar_t__ mfi_lookup_volume (int,char*,int /*<<< orphan*/ *) ; 
 int mfi_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_unit ; 
 char* mfi_volume_name (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int
volume_progress(int ac, char **av)
{
	struct mfi_ld_info info;
	int error, fd;
	uint8_t target_id;

	if (ac != 2) {
		warnx("volume progress: %s", ac > 2 ? "extra arguments" :
		    "volume required");
		return (EINVAL);
	}

	fd = mfi_open(mfi_unit, O_RDONLY);
	if (fd < 0) {
		error = errno;
		warn("mfi_open");
		return (error);
	}

	if (mfi_lookup_volume(fd, av[1], &target_id) < 0) {
		error = errno;
		warn("Invalid volume: %s", av[1]);
		close(fd);
		return (error);
	}

	/* Get the info for this drive. */
	if (mfi_ld_get_info(fd, target_id, &info, NULL) < 0) {
		error = errno;
		warn("Failed to fetch info for volume %s",
		    mfi_volume_name(fd, target_id));
		close(fd);
		return (error);
	}

	/* Display any of the active events. */
	if (info.progress.active & MFI_LD_PROGRESS_CC)
		mfi_display_progress("Consistency Check", &info.progress.cc);
	if (info.progress.active & MFI_LD_PROGRESS_BGI)
		mfi_display_progress("Background Init", &info.progress.bgi);
	if (info.progress.active & MFI_LD_PROGRESS_FGI)
		mfi_display_progress("Foreground Init", &info.progress.fgi);
	if (info.progress.active & MFI_LD_PROGRESS_RECON)
		mfi_display_progress("Reconstruction", &info.progress.recon);
	if ((info.progress.active & (MFI_LD_PROGRESS_CC | MFI_LD_PROGRESS_BGI |
	    MFI_LD_PROGRESS_FGI | MFI_LD_PROGRESS_RECON)) == 0)
		printf("No activity in progress for volume %s.\n",
		    mfi_volume_name(fd, target_id));
	close(fd);

	return (0);
}