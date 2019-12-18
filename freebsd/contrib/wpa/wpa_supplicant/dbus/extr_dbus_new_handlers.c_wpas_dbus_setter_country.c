#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {TYPE_1__* conf; int /*<<< orphan*/ * drv_priv; } ;
struct wpa_dbus_property_desc {int dummy; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
struct TYPE_2__ {char* country; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_FAILED ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dbus_set_error_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpa_drv_set_country (struct wpa_supplicant*,char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_dbus_simple_property_setter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 

dbus_bool_t wpas_dbus_setter_country(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct wpa_supplicant *wpa_s = user_data;
	const char *country;

	if (!wpas_dbus_simple_property_setter(iter, error, DBUS_TYPE_STRING,
					      &country))
		return FALSE;

	if (!country[0] || !country[1]) {
		dbus_set_error_const(error, DBUS_ERROR_FAILED,
				     "invalid country code");
		return FALSE;
	}

	if (wpa_s->drv_priv != NULL && wpa_drv_set_country(wpa_s, country)) {
		wpa_printf(MSG_DEBUG, "Failed to set country");
		dbus_set_error_const(error, DBUS_ERROR_FAILED,
				     "failed to set country code");
		return FALSE;
	}

	wpa_s->conf->country[0] = country[0];
	wpa_s->conf->country[1] = country[1];
	return TRUE;
}