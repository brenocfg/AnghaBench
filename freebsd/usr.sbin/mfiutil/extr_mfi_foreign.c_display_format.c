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
typedef  int uint8_t ;
struct mfi_foreign_scan_info {int count; } ;
typedef  int /*<<< orphan*/  mfi_dcmd_t ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MFI_DCMD_CFG_FOREIGN_SCAN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int foreign_show_cfg (int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ mfi_dcmd_command (int,int /*<<< orphan*/ ,struct mfi_foreign_scan_info*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mfi_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_unit ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
display_format(int ac, char **av, int diagnostic, mfi_dcmd_t display_cmd)
{
	struct mfi_foreign_scan_info info;
	uint8_t i;
	int error, fd;

	if (ac > 2) {
		warnx("foreign display: extra arguments");
                return (EINVAL);
	}

	fd = mfi_open(mfi_unit, O_RDONLY);
	if (fd < 0) {
		error = errno;
		warn("mfi_open");
		return (error);
	}

	if (mfi_dcmd_command(fd, MFI_DCMD_CFG_FOREIGN_SCAN, &info,
	    sizeof(info), NULL, 0, NULL) < 0) {
		error = errno;
		warn("Failed to scan foreign configuration");
		close(fd);
		return (error);
	}

	if (info.count == 0) {
		warnx("foreign display: no foreign configs found");
		close(fd);
		return (EINVAL);
	}

	if (ac == 1) {
		for (i = 0; i < info.count; i++) {
			error = foreign_show_cfg(fd,
				display_cmd, i, diagnostic);
			if(error != 0) {
				close(fd);
				return (error);
			}
			if (i < info.count - 1)
				printf("\n");
		}
	} else if (ac == 2) {
		error = foreign_show_cfg(fd,
			display_cmd, atoi(av[1]), diagnostic);
		if (error != 0) {
			close(fd);
			return (error);
		}
	}
	
	close(fd);
	return (0);
}