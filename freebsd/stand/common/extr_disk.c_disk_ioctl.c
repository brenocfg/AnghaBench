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
typedef  int uint64_t ;
typedef  int u_long ;
typedef  int u_int ;
struct open_disk {int sectorsize; int mediasize; int entrysize; } ;
struct TYPE_2__ {struct open_disk* d_opendata; } ;
struct disk_devdesc {int /*<<< orphan*/  d_offset; TYPE_1__ dd; } ;

/* Variables and functions */
#define  DIOCGMEDIASIZE 129 
#define  DIOCGSECTORSIZE 128 
 int ENOTTY ; 

int
disk_ioctl(struct disk_devdesc *dev, u_long cmd, void *data)
{
	struct open_disk *od = dev->dd.d_opendata;

	if (od == NULL)
		return (ENOTTY);

	switch (cmd) {
	case DIOCGSECTORSIZE:
		*(u_int *)data = od->sectorsize;
		break;
	case DIOCGMEDIASIZE:
		if (dev->d_offset == 0)
			*(uint64_t *)data = od->mediasize;
		else
			*(uint64_t *)data = od->entrysize * od->sectorsize;
		break;
	default:
		return (ENOTTY);
	}

	return (0);
}