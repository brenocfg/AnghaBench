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
struct TYPE_2__ {int d_unit; } ;
struct disk_devdesc {int d_slice; int d_partition; TYPE_1__ dd; } ;

/* Variables and functions */
 int D_PARTISGPT ; 
 int D_PARTNONE ; 
 int D_PARTWILD ; 
 int D_SLICENONE ; 
 int D_SLICEWILD ; 
 int EINVAL ; 
 int EPART ; 
 int ESLICE ; 
 int EUNIT ; 
 char* strchr (char const*,char) ; 
 int strtol (char const*,char**,int) ; 

int
disk_parsedev(struct disk_devdesc *dev, const char *devspec, const char **path)
{
	int unit, slice, partition;
	const char *np;
	char *cp;

	np = devspec;
	unit = -1;
	/*
	 * If there is path/file info after the device info, then any missing
	 * slice or partition info should be considered a request to search for
	 * an appropriate partition.  Otherwise we want to open the raw device
	 * itself and not try to fill in missing info by searching.
	 */
	if ((cp = strchr(np, ':')) != NULL && cp[1] != '\0') {
		slice = D_SLICEWILD;
		partition = D_PARTWILD;
	} else {
		slice = D_SLICENONE;
		partition = D_PARTNONE;
	}

	if (*np != '\0' && *np != ':') {
		unit = strtol(np, &cp, 10);
		if (cp == np)
			return (EUNIT);
#ifdef LOADER_GPT_SUPPORT
		if (*cp == 'p') {
			np = cp + 1;
			slice = strtol(np, &cp, 10);
			if (np == cp)
				return (ESLICE);
			/* we don't support nested partitions on GPT */
			if (*cp != '\0' && *cp != ':')
				return (EINVAL);
			partition = D_PARTISGPT;
		} else
#endif
#ifdef LOADER_MBR_SUPPORT
		if (*cp == 's') {
			np = cp + 1;
			slice = strtol(np, &cp, 10);
			if (np == cp)
				return (ESLICE);
		}
#endif
		if (*cp != '\0' && *cp != ':') {
			partition = *cp - 'a';
			if (partition < 0)
				return (EPART);
			cp++;
		}
	} else
		return (EINVAL);

	if (*cp != '\0' && *cp != ':')
		return (EINVAL);
	dev->dd.d_unit = unit;
	dev->d_slice = slice;
	dev->d_partition = partition;
	if (path != NULL)
		*path = (*cp == '\0') ? cp: cp + 1;
	return (0);
}