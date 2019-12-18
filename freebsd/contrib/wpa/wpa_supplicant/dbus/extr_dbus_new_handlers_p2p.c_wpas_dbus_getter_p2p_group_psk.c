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
typedef  int u8 ;
struct wpa_supplicant {struct wpa_ssid* current_ssid; } ;
struct wpa_ssid {int* psk; scalar_t__ psk_set; } ;
struct wpa_dbus_property_desc {int dummy; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_BYTE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  wpas_dbus_simple_array_property_getter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *) ; 

dbus_bool_t wpas_dbus_getter_p2p_group_psk(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct wpa_supplicant *wpa_s = user_data;
	u8 *p_psk = NULL;
	u8 psk_len = 0;
	struct wpa_ssid *ssid = wpa_s->current_ssid;

	if (ssid == NULL)
		return FALSE;

	if (ssid->psk_set) {
		p_psk = ssid->psk;
		psk_len = sizeof(ssid->psk);
	}

	return wpas_dbus_simple_array_property_getter(iter, DBUS_TYPE_BYTE,
						      p_psk, psk_len, error);
}