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
struct TYPE_4__ {char* ad_name; int ad_out_size; scalar_t__ ad_out_data; int /*<<< orphan*/  ad_id; } ;
struct radarhandler {scalar_t__ s; int /*<<< orphan*/  ah_devid; TYPE_2__ atd; } ;
typedef  int /*<<< orphan*/  revs ;
typedef  scalar_t__ caddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  ah_devid; } ;
typedef  TYPE_1__ HAL_REVS ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  HAL_DIAG_REVS ; 
 int /*<<< orphan*/  SIOCGATHDIAG ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ ioctl (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
radar_opendev(struct radarhandler *radar, const char *devid)
{
	HAL_REVS revs;

	radar->s = socket(AF_INET, SOCK_DGRAM, 0);
	if (radar->s < 0) {
		warn("socket");
		return 0;
	}

	strncpy(radar->atd.ad_name, devid, sizeof (radar->atd.ad_name));

	/* Get the hardware revision, just to verify things are working */
	radar->atd.ad_id = HAL_DIAG_REVS;
	radar->atd.ad_out_data = (caddr_t) &revs;
	radar->atd.ad_out_size = sizeof(revs);
	if (ioctl(radar->s, SIOCGATHDIAG, &radar->atd) < 0) {
		warn(radar->atd.ad_name);
		return 0;
	}
	radar->ah_devid = revs.ah_devid;
	return 1;
}