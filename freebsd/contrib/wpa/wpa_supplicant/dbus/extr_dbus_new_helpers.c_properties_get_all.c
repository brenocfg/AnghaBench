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
struct wpa_dbus_object_desc {int dummy; } ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  dbus_message_get_signature (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_all_properties (int /*<<< orphan*/ *,char*,struct wpa_dbus_object_desc*) ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static DBusMessage * properties_get_all(DBusMessage *message, char *interface,
					struct wpa_dbus_object_desc *obj_dsc)
{
	if (os_strcmp(dbus_message_get_signature(message), "s") != 0)
		return dbus_message_new_error(message, DBUS_ERROR_INVALID_ARGS,
					      NULL);

	return get_all_properties(message, interface, obj_dsc);
}