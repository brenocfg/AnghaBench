#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ifmediareq {scalar_t__ ifm_count; int ifm_status; int /*<<< orphan*/  ifm_active; int /*<<< orphan*/  ifm_name; } ;

/* Variables and functions */
 int IFM_AVALID ; 
 int IFM_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIOCGIFMEDIA ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifmediareq*) ; 
 int /*<<< orphan*/  memset (struct ifmediareq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

int
wlan_check_media(char *ifname)
{
	struct ifmediareq ifmr;

	memset(&ifmr, 0, sizeof(struct ifmediareq));
	strlcpy(ifmr.ifm_name, ifname, sizeof(ifmr.ifm_name));

	if (ioctl(sock, SIOCGIFMEDIA, &ifmr) < 0 || ifmr.ifm_count == 0)
		return (0);     /* Interface doesn't support SIOCGIFMEDIA. */

	if ((ifmr.ifm_status & IFM_AVALID) == 0)
		return (0);

	return (IFM_TYPE(ifmr.ifm_active));
}