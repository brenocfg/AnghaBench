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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wpa_supplicant {TYPE_2__* ap_iface; TYPE_1__* go_params; } ;
struct wpa_dbus_property_desc {int dummy; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
struct TYPE_4__ {int /*<<< orphan*/  freq; } ;
struct TYPE_3__ {int /*<<< orphan*/  freq; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_UINT16 ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ WPAS_P2P_ROLE_CLIENT ; 
 int /*<<< orphan*/  wpas_dbus_simple_property_getter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ wpas_get_p2p_role (struct wpa_supplicant*) ; 

dbus_bool_t wpas_dbus_getter_p2p_group_frequency(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct wpa_supplicant *wpa_s = user_data;
	u16 op_freq;
	u8 role = wpas_get_p2p_role(wpa_s);

	if (role == WPAS_P2P_ROLE_CLIENT) {
		if (wpa_s->go_params == NULL)
			return FALSE;
		op_freq = wpa_s->go_params->freq;
	} else {
		if (wpa_s->ap_iface == NULL)
			return FALSE;
		op_freq = wpa_s->ap_iface->freq;
	}

	return wpas_dbus_simple_property_getter(iter, DBUS_TYPE_UINT16,
						&op_freq, error);
}