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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_dbus_register_sta (struct wpa_supplicant*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpas_dbus_signal_p2p_peer_joined (struct wpa_supplicant*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpas_dbus_signal_sta_authorized (struct wpa_supplicant*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpas_p2p_notify_ap_sta_authorized (struct wpa_supplicant*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void wpas_notify_ap_sta_authorized(struct wpa_supplicant *wpa_s,
					  const u8 *sta,
					  const u8 *p2p_dev_addr)
{
#ifdef CONFIG_P2P
	wpas_p2p_notify_ap_sta_authorized(wpa_s, p2p_dev_addr);

	/*
	 * Create 'peer-joined' signal on group object -- will also
	 * check P2P itself.
	 */
	if (p2p_dev_addr)
		wpas_dbus_signal_p2p_peer_joined(wpa_s, p2p_dev_addr);
#endif /* CONFIG_P2P */

	/* Register the station */
	wpas_dbus_register_sta(wpa_s, sta);

	/* Notify listeners a new station has been authorized */
	wpas_dbus_signal_sta_authorized(wpa_s, sta);
}