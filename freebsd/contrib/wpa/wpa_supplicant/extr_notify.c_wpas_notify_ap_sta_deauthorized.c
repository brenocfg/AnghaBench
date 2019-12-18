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
 int /*<<< orphan*/  wpas_dbus_signal_p2p_peer_disconnected (struct wpa_supplicant*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpas_dbus_signal_sta_deauthorized (struct wpa_supplicant*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpas_dbus_unregister_sta (struct wpa_supplicant*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void wpas_notify_ap_sta_deauthorized(struct wpa_supplicant *wpa_s,
					    const u8 *sta,
					    const u8 *p2p_dev_addr)
{
#ifdef CONFIG_P2P
	/*
	 * Create 'peer-disconnected' signal on group object if this
	 * is a P2P group.
	 */
	if (p2p_dev_addr)
		wpas_dbus_signal_p2p_peer_disconnected(wpa_s, p2p_dev_addr);
#endif /* CONFIG_P2P */

	/* Notify listeners a station has been deauthorized */
	wpas_dbus_signal_sta_deauthorized(wpa_s, sta);

	/* Unregister the station */
	wpas_dbus_unregister_sta(wpa_s, sta);
}