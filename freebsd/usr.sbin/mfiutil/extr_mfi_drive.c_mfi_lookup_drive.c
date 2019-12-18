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
typedef  int uint8_t ;
typedef  long uint16_t ;
typedef  size_t u_int ;
struct mfi_pd_list {size_t count; TYPE_1__* addr; } ;
struct TYPE_2__ {scalar_t__ scsi_dev_type; int encl_device_id; int encl_index; int slot_number; long device_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int errno ; 
 int /*<<< orphan*/  free (struct mfi_pd_list*) ; 
 scalar_t__ mfi_pd_get_list (int,struct mfi_pd_list**,int /*<<< orphan*/ *) ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 
 char toupper (char) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
mfi_lookup_drive(int fd, char *drive, uint16_t *device_id)
{
	struct mfi_pd_list *list;
	long val;
	int error;
	u_int i;
	char *cp;
	uint8_t encl, slot;

	/* Look for a raw device id first. */
	val = strtol(drive, &cp, 0);
	if (*cp == '\0') {
		if (val < 0 || val >= 0xffff)
			goto bad;
		*device_id = val;
		return (0);
	}

	/* Support for MegaCli style [Exx]:Syy notation. */
	if (toupper(drive[0]) == 'E' || toupper(drive[0]) == 'S') {
		if (drive[1] == '\0')
			goto bad;
		cp = drive;
		if (toupper(drive[0]) == 'E') {
			cp++;			/* Eat 'E' */
			val = strtol(cp, &cp, 0);
			if (val < 0 || val > 0xff || *cp != ':')
				goto bad;
			encl = val;
			cp++;			/* Eat ':' */
			if (toupper(*cp) != 'S')
				goto bad;
		} else
			encl = 0xff;
		cp++;				/* Eat 'S' */
		if (*cp == '\0')
			goto bad;
		val = strtol(cp, &cp, 0);
		if (val < 0 || val > 0xff || *cp != '\0')
			goto bad;
		slot = val;

		if (mfi_pd_get_list(fd, &list, NULL) < 0) {
			error = errno;
			warn("Failed to fetch drive list");
			return (error);
		}

		for (i = 0; i < list->count; i++) {
			if (list->addr[i].scsi_dev_type != 0)
				continue;

			if (((encl == 0xff &&
			    list->addr[i].encl_device_id == 0xffff) ||
			    list->addr[i].encl_index == encl) &&
			    list->addr[i].slot_number == slot) {
				*device_id = list->addr[i].device_id;
				free(list);
				return (0);
			}
		}
		free(list);
		warnx("Unknown drive %s", drive);
		return (EINVAL);
	}

bad:
	warnx("Invalid drive number %s", drive);
	return (EINVAL);
}