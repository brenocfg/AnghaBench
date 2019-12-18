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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct wpa_supplicant {TYPE_1__* current_ssid; TYPE_2__* global; } ;
struct TYPE_4__ {int /*<<< orphan*/ * p2p; scalar_t__ p2p_disabled; } ;
struct TYPE_3__ {scalar_t__ mode; scalar_t__ p2p_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  P2P_GROUP_REMOVAL_GO_ENDING_SESSION ; 
 scalar_t__ WLAN_REASON_DEAUTH_LEAVING ; 
 scalar_t__ WPAS_MODE_INFRA ; 
 int /*<<< orphan*/  p2p_deauth_notif (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpas_p2p_group_delete (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

int wpas_p2p_deauth_notif(struct wpa_supplicant *wpa_s, const u8 *bssid,
			  u16 reason_code, const u8 *ie, size_t ie_len,
			  int locally_generated)
{
	if (wpa_s->global->p2p_disabled || wpa_s->global->p2p == NULL)
		return 0;

	if (!locally_generated)
		p2p_deauth_notif(wpa_s->global->p2p, bssid, reason_code, ie,
				 ie_len);

	if (reason_code == WLAN_REASON_DEAUTH_LEAVING && !locally_generated &&
	    wpa_s->current_ssid &&
	    wpa_s->current_ssid->p2p_group &&
	    wpa_s->current_ssid->mode == WPAS_MODE_INFRA) {
		wpa_printf(MSG_DEBUG, "P2P: GO indicated that the P2P Group "
			   "session is ending");
		if (wpas_p2p_group_delete(wpa_s,
					  P2P_GROUP_REMOVAL_GO_ENDING_SESSION)
		    > 0)
			return 1;
	}

	return 0;
}