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
struct wpa_group {int /*<<< orphan*/  wpa_group_state; int /*<<< orphan*/  changed; } ;
struct wpa_authenticator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WPA_GROUP_FATAL_FAILURE ; 
 int /*<<< orphan*/  wpa_auth_for_each_sta (struct wpa_authenticator*,int /*<<< orphan*/ ,struct wpa_group*) ; 
 int /*<<< orphan*/  wpa_group_disconnect_cb ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wpa_group_fatal_failure(struct wpa_authenticator *wpa_auth,
				    struct wpa_group *group)
{
	wpa_printf(MSG_DEBUG, "WPA: group state machine entering state FATAL_FAILURE");
	group->changed = TRUE;
	group->wpa_group_state = WPA_GROUP_FATAL_FAILURE;
	wpa_auth_for_each_sta(wpa_auth, wpa_group_disconnect_cb, group);
}