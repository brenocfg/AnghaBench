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
struct wpa_group {int /*<<< orphan*/  wpa_group_state; int /*<<< orphan*/  changed; int /*<<< orphan*/  vlan_id; } ;
struct wpa_authenticator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WPA_GROUP_SETKEYSDONE ; 
 scalar_t__ wpa_group_config_group_keys (struct wpa_authenticator*,struct wpa_group*) ; 
 int /*<<< orphan*/  wpa_group_fatal_failure (struct wpa_authenticator*,struct wpa_group*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_group_setkeysdone(struct wpa_authenticator *wpa_auth,
				 struct wpa_group *group)
{
	wpa_printf(MSG_DEBUG, "WPA: group state machine entering state "
		   "SETKEYSDONE (VLAN-ID %d)", group->vlan_id);
	group->changed = TRUE;
	group->wpa_group_state = WPA_GROUP_SETKEYSDONE;

	if (wpa_group_config_group_keys(wpa_auth, group) < 0) {
		wpa_group_fatal_failure(wpa_auth, group);
		return -1;
	}

	return 0;
}