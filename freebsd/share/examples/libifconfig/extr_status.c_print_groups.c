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
struct ifgroupreq {int ifgr_len; struct ifg_req* ifgr_groups; } ;
struct ifg_req {char* ifgrq_group; } ;
struct ifaddrs {int /*<<< orphan*/  ifa_name; } ;
typedef  int /*<<< orphan*/  ifconfig_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (struct ifg_req*) ; 
 scalar_t__ ifconfig_get_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ifgroupreq*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
print_groups(ifconfig_handle_t *lifh, struct ifaddrs *ifa)
{
	struct ifgroupreq ifgr;
	struct ifg_req *ifg;
	int len;
	int cnt = 0;

	if (ifconfig_get_groups(lifh, ifa->ifa_name, &ifgr) != 0) {
		err(1, "Failed to get groups");
	}

	ifg = ifgr.ifgr_groups;
	len = ifgr.ifgr_len;
	for (; ifg && len >= sizeof(struct ifg_req); ifg++) {
		len -= sizeof(struct ifg_req);
		if (strcmp(ifg->ifgrq_group, "all")) {
			if (cnt == 0) {
				printf("\tgroups: ");
			}
			cnt++;
			printf("%s ", ifg->ifgrq_group);
		}
	}
	if (cnt) {
		printf("\n");
	}

	free(ifgr.ifgr_groups);
}