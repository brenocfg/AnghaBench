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
typedef  long uint8_t ;
struct mpt_drive_list {long ndrives; TYPE_1__** drives; } ;
typedef  long U8 ;
struct TYPE_2__ {long PhysDiskBus; long PhysDiskID; long PhysDiskNum; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 

int
mpt_lookup_drive(struct mpt_drive_list *list, const char *drive,
    U8 *PhysDiskNum)
{
	long val;
	uint8_t bus, id;
	char *cp;

	/* Look for a raw device id first. */
	val = strtol(drive, &cp, 0);
	if (*cp == '\0') {
		if (val < 0 || val > 0xff)
			goto bad;
		*PhysDiskNum = val;
		return (0);
	}

	/* Look for a <bus>:<id> string. */
	if (*cp == ':') {
		if (val < 0 || val > 0xff)
			goto bad;
		bus = val;
		val = strtol(cp + 1, &cp, 0);
		if (*cp != '\0')
			goto bad;
		if (val < 0 || val > 0xff)
			goto bad;
		id = val;

		for (val = 0; val < list->ndrives; val++) {
			if (list->drives[val]->PhysDiskBus == bus &&
			    list->drives[val]->PhysDiskID == id) {
				*PhysDiskNum = list->drives[val]->PhysDiskNum;
				return (0);
			}
		}
		return (ENOENT);
	}

bad:
	return (EINVAL);
}