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
struct volume_info {int drive_count; struct drive_info* drives; } ;
struct drive_info {int /*<<< orphan*/ * sdisk; int /*<<< orphan*/ * info; } ;
struct config_id_state {int /*<<< orphan*/ * sdisks; int /*<<< orphan*/  nsdisks; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  U8 ;

/* Variables and functions */
 int EINVAL ; 
#define  RT_RAID0 130 
#define  RT_RAID1 129 
#define  RT_RAID1E 128 
 struct drive_info* calloc (int,int) ; 
 int errno ; 
 scalar_t__ mpt_lock_physdisk (int /*<<< orphan*/ *) ; 
 int mpt_lookup_drive (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ mpt_lookup_standalone_disk (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * mpt_pd_info (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
parse_volume(int fd, int raid_type, struct config_id_state *state,
    char *volume_str, struct volume_info *info)
{
	struct drive_info *dinfo;
	U8 PhysDiskNum;
	char *cp;
	int count, error, i;

	cp = volume_str;
	for (count = 0; cp != NULL; count++) {
		cp = strchr(cp, ',');
		if (cp != NULL) {
			cp++;
			if (*cp == ',') {
				warnx("Invalid drive list '%s'", volume_str);
				return (EINVAL);
			}
		}
	}

	/* Validate the number of drives for this volume. */
	switch (raid_type) {
	case RT_RAID0:
		if (count < 2) {
			warnx("RAID0 requires at least 2 drives in each "
			    "array");
			return (EINVAL);
		}
		break;
	case RT_RAID1:
		if (count != 2) {
			warnx("RAID1 requires exactly 2 drives in each "
			    "array");
			return (EINVAL);
		}
		break;
	case RT_RAID1E:
		if (count < 3) {
			warnx("RAID1E requires at least 3 drives in each "
			    "array");
			return (EINVAL);
		}
		break;
	}

	/* Validate each drive. */
	info->drives = calloc(count, sizeof(struct drive_info));
	info->drive_count = count;
	for (dinfo = info->drives; (cp = strsep(&volume_str, ",")) != NULL;
	     dinfo++) {
		/* If this drive is already a RAID phys just fetch the info. */
		error = mpt_lookup_drive(state->list, cp, &PhysDiskNum);
		if (error == 0) {
			dinfo->info = mpt_pd_info(fd, PhysDiskNum, NULL);
			if (dinfo->info == NULL)
				return (errno);
			continue;
		}

		/* See if it is a standalone disk. */
		if (mpt_lookup_standalone_disk(cp, state->sdisks,
		    state->nsdisks, &i) < 0) {
			error = errno;
			warn("Unable to lookup drive %s", cp);
			return (error);
		}
		dinfo->sdisk = &state->sdisks[i];

		/* Lock the disk, we will create phys disk pages later. */
		if (mpt_lock_physdisk(dinfo->sdisk) < 0)
			return (errno);
	}

	return (0);
}