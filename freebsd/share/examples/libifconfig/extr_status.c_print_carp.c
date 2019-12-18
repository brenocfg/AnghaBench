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
struct ifaddrs {int /*<<< orphan*/  ifa_name; } ;
struct carpreq {int carpr_count; size_t carpr_state; int carpr_vhid; int carpr_advbase; int carpr_advskew; } ;
typedef  int /*<<< orphan*/  ifconfig_handle_t ;

/* Variables and functions */
 int CARP_MAXVHID ; 
 char** carp_states ; 
 scalar_t__ ifconfig_carp_get_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct carpreq*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_carp(ifconfig_handle_t *lifh, struct ifaddrs *ifa)
{
	struct carpreq carpr[CARP_MAXVHID];
	int i;

	if (ifconfig_carp_get_info(lifh, ifa->ifa_name, carpr, CARP_MAXVHID)) {
		return; /* Probably not configured on this interface */
	}
	for (i = 0; i < carpr[0].carpr_count; i++) {
		printf("\tcarp: %s vhid %d advbase %d advskew %d",
		    carp_states[carpr[i].carpr_state], carpr[i].carpr_vhid,
		    carpr[i].carpr_advbase, carpr[i].carpr_advskew);
		printf("\n");
	}
}