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
struct wpa_group {int GM; int GN; int GM_igtk; int GN_igtk; scalar_t__ GKeyDoneStations; int /*<<< orphan*/  GTKReKey; int /*<<< orphan*/  wpa_group_state; int /*<<< orphan*/  changed; scalar_t__ vlan_id; } ;
struct wpa_authenticator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WPA_GROUP_SETKEYS ; 
 int /*<<< orphan*/  wpa_auth_for_each_sta (struct wpa_authenticator*,int /*<<< orphan*/ ,struct wpa_group*) ; 
 int /*<<< orphan*/  wpa_group_update_sta ; 
 int /*<<< orphan*/  wpa_gtk_update (struct wpa_authenticator*,struct wpa_group*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void wpa_group_setkeys(struct wpa_authenticator *wpa_auth,
			      struct wpa_group *group)
{
	int tmp;

	wpa_printf(MSG_DEBUG, "WPA: group state machine entering state "
		   "SETKEYS (VLAN-ID %d)", group->vlan_id);
	group->changed = TRUE;
	group->wpa_group_state = WPA_GROUP_SETKEYS;
	group->GTKReKey = FALSE;
	tmp = group->GM;
	group->GM = group->GN;
	group->GN = tmp;
#ifdef CONFIG_IEEE80211W
	tmp = group->GM_igtk;
	group->GM_igtk = group->GN_igtk;
	group->GN_igtk = tmp;
#endif /* CONFIG_IEEE80211W */
	/* "GKeyDoneStations = GNoStations" is done in more robust way by
	 * counting the STAs that are marked with GUpdateStationKeys instead of
	 * including all STAs that could be in not-yet-completed state. */
	wpa_gtk_update(wpa_auth, group);

	if (group->GKeyDoneStations) {
		wpa_printf(MSG_DEBUG, "wpa_group_setkeys: Unexpected "
			   "GKeyDoneStations=%d when starting new GTK rekey",
			   group->GKeyDoneStations);
		group->GKeyDoneStations = 0;
	}
	wpa_auth_for_each_sta(wpa_auth, wpa_group_update_sta, group);
	wpa_printf(MSG_DEBUG, "wpa_group_setkeys: GKeyDoneStations=%d",
		   group->GKeyDoneStations);
}