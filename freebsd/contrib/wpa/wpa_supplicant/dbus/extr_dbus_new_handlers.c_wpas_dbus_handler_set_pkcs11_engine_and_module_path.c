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
struct wpa_supplicant {scalar_t__ dbus_new_path; TYPE_1__* global; } ;
struct TYPE_2__ {int /*<<< orphan*/  dbus; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_FAILED ; 
 int /*<<< orphan*/  DBUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  WPAS_DBUS_NEW_IFACE_INTERFACE ; 
 int /*<<< orphan*/  dbus_message_iter_get_basic (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strlen (char*) ; 
 int /*<<< orphan*/  wpa_dbus_mark_property_changed (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpas_set_pkcs11_engine_and_module_path (struct wpa_supplicant*,char*,char*) ; 

DBusMessage * wpas_dbus_handler_set_pkcs11_engine_and_module_path(
	DBusMessage *message, struct wpa_supplicant *wpa_s)
{
	DBusMessageIter iter;
	char *value = NULL;
	char *pkcs11_engine_path = NULL;
	char *pkcs11_module_path = NULL;

	dbus_message_iter_init(message, &iter);
	dbus_message_iter_get_basic(&iter, &value);
	if (value == NULL) {
		return dbus_message_new_error(
			message, DBUS_ERROR_INVALID_ARGS,
			"Invalid pkcs11_engine_path argument");
	}
	/* Empty path defaults to NULL */
	if (os_strlen(value))
		pkcs11_engine_path = value;

	dbus_message_iter_next(&iter);
	dbus_message_iter_get_basic(&iter, &value);
	if (value == NULL) {
		os_free(pkcs11_engine_path);
		return dbus_message_new_error(
			message, DBUS_ERROR_INVALID_ARGS,
			"Invalid pkcs11_module_path argument");
	}
	/* Empty path defaults to NULL */
	if (os_strlen(value))
		pkcs11_module_path = value;

	if (wpas_set_pkcs11_engine_and_module_path(wpa_s, pkcs11_engine_path,
						   pkcs11_module_path))
		return dbus_message_new_error(
			message, DBUS_ERROR_FAILED,
			"Reinit of the EAPOL state machine with the new PKCS #11 engine and module path failed.");

	if (wpa_s->dbus_new_path) {
		wpa_dbus_mark_property_changed(
			wpa_s->global->dbus, wpa_s->dbus_new_path,
			WPAS_DBUS_NEW_IFACE_INTERFACE, "PKCS11EnginePath");
		wpa_dbus_mark_property_changed(
			wpa_s->global->dbus, wpa_s->dbus_new_path,
			WPAS_DBUS_NEW_IFACE_INTERFACE, "PKCS11ModulePath");
	}

	return NULL;
}