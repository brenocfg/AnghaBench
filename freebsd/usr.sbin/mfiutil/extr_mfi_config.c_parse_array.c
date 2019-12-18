#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int u_int ;
struct TYPE_5__ {scalar_t__ is_foreign; } ;
struct TYPE_6__ {TYPE_1__ pd_type; } ;
struct TYPE_7__ {TYPE_2__ v; } ;
struct TYPE_8__ {TYPE_3__ ddf; } ;
struct mfi_pd_info {scalar_t__ fw_state; TYPE_4__ state; } ;
struct array_info {int drive_count; struct mfi_pd_info* drives; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int MAX_DRIVES_PER_ARRAY ; 
 scalar_t__ MFI_PD_STATE_UNCONFIGURED_GOOD ; 
#define  RT_RAID1 133 
#define  RT_RAID10 132 
#define  RT_RAID5 131 
#define  RT_RAID50 130 
#define  RT_RAID6 129 
#define  RT_RAID60 128 
 struct mfi_pd_info* calloc (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct mfi_pd_info*) ; 
 int mfi_lookup_drive (int,char*,int*) ; 
 scalar_t__ mfi_pd_get_info (int,int,struct mfi_pd_info*,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
parse_array(int fd, int raid_type, char *array_str, struct array_info *info)
{
	struct mfi_pd_info *pinfo;
	uint16_t device_id;
	char *cp;
	u_int count;
	int error;

	cp = array_str;
	for (count = 0; cp != NULL; count++) {
		cp = strchr(cp, ',');
		if (cp != NULL) {
			cp++;
			if (*cp == ',') {
				warnx("Invalid drive list '%s'", array_str);
				return (EINVAL);
			}
		}
	}

	/* Validate the number of drives for this array. */
	if (count >= MAX_DRIVES_PER_ARRAY) {
		warnx("Too many drives for a single array: max is %d",
		    MAX_DRIVES_PER_ARRAY);
		return (EINVAL);
	}
	switch (raid_type) {
	case RT_RAID1:
	case RT_RAID10:
		if (count % 2 != 0) {
			warnx("RAID1 and RAID10 require an even number of "
			    "drives in each array");
			return (EINVAL);
		}
		break;
	case RT_RAID5:
	case RT_RAID50:
		if (count < 3) {
			warnx("RAID5 and RAID50 require at least 3 drives in "
			    "each array");
			return (EINVAL);
		}
		break;
	case RT_RAID6:
	case RT_RAID60:
		if (count < 4) {
			warnx("RAID6 and RAID60 require at least 4 drives in "
			    "each array");
			return (EINVAL);
		}
		break;
	}

	/* Validate each drive. */
	info->drives = calloc(count, sizeof(struct mfi_pd_info));
	if (info->drives == NULL) {
		warnx("malloc failed");
		return (ENOMEM);
	}
	info->drive_count = count;
	for (pinfo = info->drives; (cp = strsep(&array_str, ",")) != NULL;
	     pinfo++) {
		error = mfi_lookup_drive(fd, cp, &device_id);
		if (error) {
			free(info->drives);
			info->drives = NULL;
			return (error);
		}

		if (mfi_pd_get_info(fd, device_id, pinfo, NULL) < 0) {
			error = errno;
			warn("Failed to fetch drive info for drive %s", cp);
			free(info->drives);
			info->drives = NULL;
			return (error);
		}

		if (pinfo->fw_state != MFI_PD_STATE_UNCONFIGURED_GOOD) {
			warnx("Drive %u is not available", device_id);
			free(info->drives);
			info->drives = NULL;
			return (EINVAL);
		}

		if (pinfo->state.ddf.v.pd_type.is_foreign) {
			warnx("Drive %u is foreign", device_id);
			free(info->drives);
			info->drives = NULL;
			return (EINVAL);
		}
	}

	return (0);
}