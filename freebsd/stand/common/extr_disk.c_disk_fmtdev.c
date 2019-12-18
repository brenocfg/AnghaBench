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
struct TYPE_4__ {TYPE_1__* d_dev; int /*<<< orphan*/  d_unit; } ;
struct disk_devdesc {scalar_t__ d_slice; scalar_t__ d_partition; TYPE_2__ dd; } ;
struct TYPE_3__ {char* dv_name; } ;

/* Variables and functions */
 scalar_t__ D_PARTISGPT ; 
 scalar_t__ D_PARTNONE ; 
 scalar_t__ D_SLICENONE ; 
 int sprintf (char*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

char*
disk_fmtdev(struct disk_devdesc *dev)
{
	static char buf[128];
	char *cp;

	cp = buf + sprintf(buf, "%s%d", dev->dd.d_dev->dv_name, dev->dd.d_unit);
	if (dev->d_slice > D_SLICENONE) {
#ifdef LOADER_GPT_SUPPORT
		if (dev->d_partition == D_PARTISGPT) {
			sprintf(cp, "p%d:", dev->d_slice);
			return (buf);
		} else
#endif
#ifdef LOADER_MBR_SUPPORT
			cp += sprintf(cp, "s%d", dev->d_slice);
#endif
	}
	if (dev->d_partition > D_PARTNONE)
		cp += sprintf(cp, "%c", dev->d_partition + 'a');
	strcat(cp, ":");
	return (buf);
}