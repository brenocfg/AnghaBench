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
struct wpa_dbus_property_desc {int dummy; } ;
struct peer_handler_args {int /*<<< orphan*/  p2p_device_addr; TYPE_2__* wpa_s; } ;
struct p2p_peer_info {int /*<<< orphan*/  device_name; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
struct TYPE_4__ {TYPE_1__* global; } ;
struct TYPE_3__ {int /*<<< orphan*/  p2p; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_FAILED ; 
 int /*<<< orphan*/  DBUS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dbus_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dbus_set_error_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_strdup (int /*<<< orphan*/ ) ; 
 struct p2p_peer_info* p2p_get_peer_found (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbus_p2p_check_enabled (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpas_dbus_simple_property_getter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 

dbus_bool_t wpas_dbus_getter_p2p_peer_device_name(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct peer_handler_args *peer_args = user_data;
	const struct p2p_peer_info *info;
	char *tmp;

	if (!wpa_dbus_p2p_check_enabled(peer_args->wpa_s, NULL, NULL, error))
		return FALSE;

	/* get the peer info */
	info = p2p_get_peer_found(peer_args->wpa_s->global->p2p,
				  peer_args->p2p_device_addr, 0);
	if (info == NULL) {
		dbus_set_error(error, DBUS_ERROR_FAILED,
			       "failed to find peer");
		return FALSE;
	}

	tmp = os_strdup(info->device_name);
	if (!tmp) {
		dbus_set_error_const(error, DBUS_ERROR_NO_MEMORY, "no memory");
		return FALSE;
	}

	if (!wpas_dbus_simple_property_getter(iter, DBUS_TYPE_STRING, &tmp,
					      error)) {
		dbus_set_error_const(error, DBUS_ERROR_NO_MEMORY, "no memory");
		os_free(tmp);
		return FALSE;
	}

	os_free(tmp);
	return TRUE;
}