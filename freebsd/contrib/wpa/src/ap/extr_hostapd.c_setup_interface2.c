#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hostapd_iface {TYPE_3__* interfaces; TYPE_2__** bss; TYPE_1__* conf; scalar_t__ wait_channel_update; } ;
struct TYPE_6__ {scalar_t__ terminate_on_error; } ;
struct TYPE_5__ {int /*<<< orphan*/  msg_ctx; } ;
struct TYPE_4__ {scalar_t__ ieee80211h; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_EVENT_DISABLED ; 
 int /*<<< orphan*/  HAPD_IFACE_DISABLED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  eloop_terminate () ; 
 int hostapd_check_ht_capab (struct hostapd_iface*) ; 
 scalar_t__ hostapd_get_hw_features (struct hostapd_iface*) ; 
 int hostapd_select_hw_mode (struct hostapd_iface*) ; 
 int /*<<< orphan*/  hostapd_set_state (struct hostapd_iface*,int /*<<< orphan*/ ) ; 
 int hostapd_setup_interface_complete (struct hostapd_iface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int setup_interface2(struct hostapd_iface *iface)
{
	iface->wait_channel_update = 0;

	if (hostapd_get_hw_features(iface)) {
		/* Not all drivers support this yet, so continue without hw
		 * feature data. */
	} else {
		int ret = hostapd_select_hw_mode(iface);
		if (ret < 0) {
			wpa_printf(MSG_ERROR, "Could not select hw_mode and "
				   "channel. (%d)", ret);
			goto fail;
		}
		if (ret == 1) {
			wpa_printf(MSG_DEBUG, "Interface initialization will be completed in a callback (ACS)");
			return 0;
		}
		ret = hostapd_check_ht_capab(iface);
		if (ret < 0)
			goto fail;
		if (ret == 1) {
			wpa_printf(MSG_DEBUG, "Interface initialization will "
				   "be completed in a callback");
			return 0;
		}

		if (iface->conf->ieee80211h)
			wpa_printf(MSG_DEBUG, "DFS support is enabled");
	}
	return hostapd_setup_interface_complete(iface, 0);

fail:
	hostapd_set_state(iface, HAPD_IFACE_DISABLED);
	wpa_msg(iface->bss[0]->msg_ctx, MSG_INFO, AP_EVENT_DISABLED);
	if (iface->interfaces && iface->interfaces->terminate_on_error)
		eloop_terminate();
	return -1;
}