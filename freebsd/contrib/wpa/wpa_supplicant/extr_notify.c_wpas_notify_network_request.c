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
struct wpa_supplicant {scalar_t__ p2p_mgmt; } ;
struct wpa_ssid {int dummy; } ;
typedef  enum wpa_ctrl_req_type { ____Placeholder_wpa_ctrl_req_type } wpa_ctrl_req_type ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_dbus_signal_network_request (struct wpa_supplicant*,struct wpa_ssid*,int,char const*) ; 

void wpas_notify_network_request(struct wpa_supplicant *wpa_s,
				 struct wpa_ssid *ssid,
				 enum wpa_ctrl_req_type rtype,
				 const char *default_txt)
{
	if (wpa_s->p2p_mgmt)
		return;

	wpas_dbus_signal_network_request(wpa_s, ssid, rtype, default_txt);
}