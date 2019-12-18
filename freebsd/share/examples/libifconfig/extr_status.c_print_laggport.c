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
struct lagg_reqport {char* rp_ifname; } ;
struct ifaddrs {int /*<<< orphan*/  ifa_name; } ;
typedef  int /*<<< orphan*/  ifconfig_handle_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ifconfig_err_errno (int /*<<< orphan*/ *) ; 
 scalar_t__ ifconfig_lagg_get_laggport_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct lagg_reqport*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
print_laggport(ifconfig_handle_t *lifh, struct ifaddrs *ifa)
{
	struct lagg_reqport rp;

	if (ifconfig_lagg_get_laggport_status(lifh, ifa->ifa_name, &rp) < 0) {
		if ((ifconfig_err_errno(lifh) == EINVAL) ||
		    (ifconfig_err_errno(lifh) == ENOENT)) {
			return;
		} else {
			err(1, "Failed to get lagg port status");
		}
	}

	printf("\tlaggdev: %s\n", rp.rp_ifname);
}