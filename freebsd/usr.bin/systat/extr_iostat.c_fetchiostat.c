#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct devinfo {int /*<<< orphan*/  generation; int /*<<< orphan*/  numdevs; } ;
struct TYPE_5__ {struct devinfo* dinfo; int /*<<< orphan*/  snap_time; int /*<<< orphan*/  cp_time; } ;
struct TYPE_4__ {int /*<<< orphan*/  snap_time; struct devinfo* dinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmdiostat (char*,int /*<<< orphan*/ *) ; 
 TYPE_2__ cur_dev ; 
 int /*<<< orphan*/  devstat_errbuf ; 
 int devstat_getdevs (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  generation ; 
 TYPE_1__ last_dev ; 
 int /*<<< orphan*/  num_devices ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ sysctlbyname (char*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
fetchiostat(void)
{
	struct devinfo *tmp_dinfo;
	size_t len;

	len = sizeof(cur_dev.cp_time);
	if (sysctlbyname("kern.cp_time", &cur_dev.cp_time, &len, NULL, 0)
	    || len != sizeof(cur_dev.cp_time)) {
		perror("kern.cp_time");
		exit (1);
	}
	tmp_dinfo = last_dev.dinfo;
	last_dev.dinfo = cur_dev.dinfo;
	cur_dev.dinfo = tmp_dinfo;

	last_dev.snap_time = cur_dev.snap_time;

	/*
	 * Here what we want to do is refresh our device stats.
	 * getdevs() returns 1 when the device list has changed.
	 * If the device list has changed, we want to go through
	 * the selection process again, in case a device that we
	 * were previously displaying has gone away.
	 */
	switch (devstat_getdevs(NULL, &cur_dev)) {
	case -1:
		errx(1, "%s", devstat_errbuf);
		break;
	case 1:
		cmdiostat("refresh", NULL);
		break;
	default:
		break;
	}
	num_devices = cur_dev.dinfo->numdevs;
	generation = cur_dev.dinfo->generation;

}