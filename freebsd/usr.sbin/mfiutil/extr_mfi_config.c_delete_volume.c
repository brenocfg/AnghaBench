#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  ld; } ;
struct TYPE_4__ {TYPE_1__ properties; } ;
struct mfi_ld_info {TYPE_2__ ld_config; } ;
typedef  int /*<<< orphan*/  mbox ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MFI_DCMD_LD_DELETE ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  mbox_store_ldref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mfi_dcmd_command (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ mfi_ld_get_info (int,int /*<<< orphan*/ ,struct mfi_ld_info*,int /*<<< orphan*/ *) ; 
 scalar_t__ mfi_lookup_volume (int,char*,int /*<<< orphan*/ *) ; 
 int mfi_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_reconfig_supported () ; 
 int /*<<< orphan*/  mfi_unit ; 
 scalar_t__ mfi_volume_busy (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_volume_name (int,int /*<<< orphan*/ ) ; 
 int remove_spare (int,char**) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
delete_volume(int ac, char **av)
{
	struct mfi_ld_info info;
	int error, fd;
	uint8_t target_id, mbox[4];

	/*
	 * Backwards compat.  Map 'delete volume' to 'delete' and
	 * 'delete spare' to 'remove'.
	 */
	if (ac > 1) {
		if (strcmp(av[1], "volume") == 0) {
			av++;
			ac--;
		} else if (strcmp(av[1], "spare") == 0) {
			av++;
			ac--;
			return (remove_spare(ac, av));
		}
	}

	if (ac != 2) {
		warnx("delete volume: volume required");
		return (EINVAL);
	}

	fd = mfi_open(mfi_unit, O_RDWR);
	if (fd < 0) {
		error = errno;
		warn("mfi_open");
		return (error);
	}

	if (!mfi_reconfig_supported()) {
		warnx("The current mfi(4) driver does not support "
		    "configuration changes.");
		close(fd);
		return (EOPNOTSUPP);
	}

	if (mfi_lookup_volume(fd, av[1], &target_id) < 0) {
		error = errno;
		warn("Invalid volume %s", av[1]);
		close(fd);
		return (error);
	}

	if (mfi_ld_get_info(fd, target_id, &info, NULL) < 0) {
		error = errno;
		warn("Failed to get info for volume %d", target_id);
		close(fd);
		return (error);
	}

	if (mfi_volume_busy(fd, target_id)) {
		warnx("Volume %s is busy and cannot be deleted",
		    mfi_volume_name(fd, target_id));
		close(fd);
		return (EBUSY);
	}

	mbox_store_ldref(mbox, &info.ld_config.properties.ld);
	if (mfi_dcmd_command(fd, MFI_DCMD_LD_DELETE, NULL, 0, mbox,
	    sizeof(mbox), NULL) < 0) {
		error = errno;
		warn("Failed to delete volume");
		close(fd);
		return (error);
	}

	close(fd);

	return (0);
}