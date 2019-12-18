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
struct hapd_interfaces {int /*<<< orphan*/  ctrl_iface_group; } ;
struct group {int /*<<< orphan*/  gr_gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 struct group* getgrnam (char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int hostapd_get_ctrl_iface_group(struct hapd_interfaces *interfaces,
					const char *group)
{
#ifndef CONFIG_NATIVE_WINDOWS
	struct group *grp;
	grp = getgrnam(group);
	if (grp == NULL) {
		wpa_printf(MSG_ERROR, "Unknown group '%s'", group);
		return -1;
	}
	interfaces->ctrl_iface_group = grp->gr_gid;
#endif /* CONFIG_NATIVE_WINDOWS */
	return 0;
}