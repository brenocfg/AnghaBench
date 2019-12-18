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
typedef  int u_int64_t ;
struct statinfo {struct devinfo* dinfo; } ;
struct devinfo {int numdevs; struct devinfo* mem_ptr; TYPE_1__* devices; } ;
struct TYPE_2__ {int device_type; scalar_t__* operations; } ;

/* Variables and functions */
 int DEVSTAT_N_TRANS_FLAGS ; 
 int DEVSTAT_TYPE_DIRECT ; 
 int DEVSTAT_TYPE_MASK ; 
 int DEVSTAT_TYPE_PASS ; 
 int INT_MAX ; 
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

void
updatexfers(int numdevs, int *devs)
{
	register int i, j, k, t;
	struct statinfo stats;
	int num_devices = 0;
	u_int64_t total_transfers;

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

	for (i = 0, j = 0; i < stats.dinfo->numdevs && j < numdevs; i++) {
		if (((stats.dinfo->devices[i].device_type
		      & DEVSTAT_TYPE_MASK) == DEVSTAT_TYPE_DIRECT)
		 && ((stats.dinfo->devices[i].device_type
		      & DEVSTAT_TYPE_PASS) == 0)) {
			total_transfers = 0;
			for (k = 0; k < DEVSTAT_N_TRANS_FLAGS; k++)
				total_transfers +=
				    stats.dinfo->devices[i].operations[k];
			/*
			 * XXX KDM If the total transfers for this device
			 * are greater than the amount we can fit in a
			 * signed integer, just set them to the maximum
			 * amount we can fit in a signed integer.  I have a
			 * feeling that the rstat protocol assumes 32-bit
			 * integers, so this could well break on a 64-bit
			 * architecture like the Alpha.
			 */
			if (total_transfers > INT_MAX)
				t = INT_MAX;
			else
				t = total_transfers;
			devs[j] = t;
			j++;
		}
	}

	if (stats.dinfo->mem_ptr)
		free(stats.dinfo->mem_ptr);

	free(stats.dinfo);
}