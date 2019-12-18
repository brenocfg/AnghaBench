#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_6__ {scalar_t__ PageType; } ;
struct TYPE_7__ {char* Name; TYPE_1__ Header; } ;
typedef  TYPE_2__ CONFIG_PAGE_RAID_VOL_1 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 scalar_t__ MPI_CONFIG_PAGEATTR_CHANGEABLE ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int mpt_lookup_volume (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mpt_open (int) ; 
 int mpt_unit ; 
 TYPE_2__* mpt_vol_names (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* mpt_volume_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mpt_write_config_page (int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnc (int,char*,char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
volume_name(int ac, char **av)
{
	CONFIG_PAGE_RAID_VOL_1 *vnames;
	U8 VolumeBus, VolumeID;
	int error, fd;

	if (ac != 3) {
		warnx("name: volume and name required");
		return (EINVAL);
	}

	if (strlen(av[2]) >= sizeof(vnames->Name)) {
		warnx("name: new name is too long");
		return (ENOSPC);
	}

	fd = mpt_open(mpt_unit);
	if (fd < 0) {
		error = errno;
		warn("mpt_open");
		return (error);
	}

	error = mpt_lookup_volume(fd, av[1], &VolumeBus, &VolumeID);
	if (error) {
		warnc(error, "Invalid volume: %s", av[1]);
		return (error);
	}

	vnames = mpt_vol_names(fd, VolumeBus, VolumeID, NULL);
	if (vnames == NULL) {
		error = errno;
		warn("Failed to fetch volume names");
		close(fd);
		return (error);
	}

	if (vnames->Header.PageType != MPI_CONFIG_PAGEATTR_CHANGEABLE) {
		warnx("Volume name is read only");
		free(vnames);
		close(fd);
		return (EOPNOTSUPP);
	}
	printf("mpt%u changing volume %s name from \"%s\" to \"%s\"\n",
	    mpt_unit, mpt_volume_name(VolumeBus, VolumeID), vnames->Name,
	    av[2]);
	bzero(vnames->Name, sizeof(vnames->Name));
	strcpy(vnames->Name, av[2]);

	if (mpt_write_config_page(fd, vnames, NULL) < 0) {
		error = errno;
		warn("Failed to set volume name");
		free(vnames);
		close(fd);
		return (error);
	}

	free(vnames);
	close(fd);

	return (0);
}