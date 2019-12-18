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
typedef  scalar_t__ u8 ;
struct wpa_supplicant {TYPE_3__* ap_iface; TYPE_2__* current_ssid; } ;
struct wpa_dbus_property_desc {int dummy; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
struct TYPE_6__ {TYPE_1__** bss; } ;
struct TYPE_5__ {scalar_t__* bssid; } ;
struct TYPE_4__ {scalar_t__* own_addr; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_BYTE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ WPAS_P2P_ROLE_CLIENT ; 
 int /*<<< orphan*/  wpas_dbus_simple_array_property_getter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ wpas_get_p2p_role (struct wpa_supplicant*) ; 

dbus_bool_t wpas_dbus_getter_p2p_group_bssid(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct wpa_supplicant *wpa_s = user_data;
	u8 role = wpas_get_p2p_role(wpa_s);
	u8 *p_bssid;

	if (role == WPAS_P2P_ROLE_CLIENT) {
		if (wpa_s->current_ssid == NULL)
			return FALSE;
		p_bssid = wpa_s->current_ssid->bssid;
	} else {
		if (wpa_s->ap_iface == NULL)
			return FALSE;
		p_bssid = wpa_s->ap_iface->bss[0]->own_addr;
	}

	return wpas_dbus_simple_array_property_getter(iter, DBUS_TYPE_BYTE,
						      p_bssid, ETH_ALEN,
						      error);
}