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
struct mfi_ld_props {char* name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ mfi_ld_get_props (int,int /*<<< orphan*/ ,struct mfi_ld_props*) ; 
 scalar_t__ mfi_ld_set_props (int,struct mfi_ld_props*) ; 
 scalar_t__ mfi_lookup_volume (int,char*,int /*<<< orphan*/ *) ; 
 int mfi_open (int,int /*<<< orphan*/ ) ; 
 int mfi_unit ; 
 char* mfi_volume_name (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
volume_name(int ac, char **av)
{
	struct mfi_ld_props props;
	int error, fd;
	uint8_t target_id;

	if (ac != 3) {
		warnx("name: volume and name required");
		return (EINVAL);
	}

	if (strlen(av[2]) >= sizeof(props.name)) {
		warnx("name: new name is too long");
		return (ENOSPC);
	}

	fd = mfi_open(mfi_unit, O_RDWR);
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

	if (mfi_ld_get_props(fd, target_id, &props) < 0) {
		error = errno;
		warn("Failed to fetch volume properties");
		close(fd);
		return (error);
	}

	printf("mfi%u volume %s name changed from \"%s\" to \"%s\"\n", mfi_unit,
	    mfi_volume_name(fd, target_id), props.name, av[2]);
	bzero(props.name, sizeof(props.name));
	strcpy(props.name, av[2]);
	if (mfi_ld_set_props(fd, &props) < 0) {
		error = errno;
		warn("Failed to set volume properties");
		close(fd);
		return (error);
	}

	close(fd);

	return (0);
}