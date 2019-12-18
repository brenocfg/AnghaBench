#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hostapd_iface {size_t num_bss; TYPE_1__** bss; } ;
struct TYPE_3__ {int /*<<< orphan*/  radius; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_REASON_PREV_AUTH_NOT_VALID ; 
 int /*<<< orphan*/  hostapd_broadcast_wep_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  hostapd_flush_old_stations (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_client_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostapd_clear_old(struct hostapd_iface *iface)
{
	size_t j;

	/*
	 * Deauthenticate all stations since the new configuration may not
	 * allow them to use the BSS anymore.
	 */
	for (j = 0; j < iface->num_bss; j++) {
		hostapd_flush_old_stations(iface->bss[j],
					   WLAN_REASON_PREV_AUTH_NOT_VALID);
		hostapd_broadcast_wep_clear(iface->bss[j]);

#ifndef CONFIG_NO_RADIUS
		/* TODO: update dynamic data based on changed configuration
		 * items (e.g., open/close sockets, etc.) */
		radius_client_flush(iface->bss[j]->radius, 0);
#endif /* CONFIG_NO_RADIUS */
	}
}