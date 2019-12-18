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
struct statinfo {struct devinfo* dinfo; } ;
struct devinfo {int numdevs; struct devinfo* mem_ptr; TYPE_1__* devices; } ;
struct TYPE_2__ {int device_type; } ;

/* Variables and functions */
 int DEVSTAT_TYPE_DIRECT ; 
 int DEVSTAT_TYPE_MASK ; 
 int DEVSTAT_TYPE_PASS ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  bzero (struct devinfo*,int) ; 
 scalar_t__ devstat_checkversion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devstat_errbuf ; 
 int devstat_getdevs (int /*<<< orphan*/ *,struct statinfo*) ; 
 int devstat_getnumdevs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (struct devinfo*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
haveadisk(void)
{
	register int i;
	struct statinfo stats;
	int num_devices, retval = 0;

	if ((num_devices = devstat_getnumdevs(NULL)) < 0) {
		syslog(LOG_ERR, "rstatd: can't get number of devices: %s",
		       devstat_errbuf);
		exit(1);
	}

	if (devstat_checkversion(NULL) < 0) {
		syslog(LOG_ERR, "rstatd: %s", devstat_errbuf);
		exit(1);
	}

	stats.dinfo = (struct devinfo *)malloc(sizeof(struct devinfo));
	bzero(stats.dinfo, sizeof(struct devinfo));

	if (devstat_getdevs(NULL, &stats) == -1) {
		syslog(LOG_ERR, "rstatd: can't get device list: %s",
		       devstat_errbuf);
		exit(1);
	}
	for (i = 0; i < stats.dinfo->numdevs; i++) {
		if (((stats.dinfo->devices[i].device_type
		      & DEVSTAT_TYPE_MASK) == DEVSTAT_TYPE_DIRECT)
		 && ((stats.dinfo->devices[i].device_type
		      & DEVSTAT_TYPE_PASS) == 0)) {
			retval = 1;
			break;
		}
	}

	if (stats.dinfo->mem_ptr)
		free(stats.dinfo->mem_ptr);

	free(stats.dinfo);
	return(retval);
}