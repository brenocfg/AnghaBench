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
typedef  int /*<<< orphan*/  DBusConnection ;

/* Variables and functions */
 int WPAS_DBUS_OBJECT_PATH_MAX ; 
 int /*<<< orphan*/  dbus_connection_list_registered (int /*<<< orphan*/ *,char const*,char***) ; 
 int /*<<< orphan*/  dbus_free_string_array (char**) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  wpa_dbus_flush_object_changed_properties (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void recursive_flush_changed_properties(DBusConnection *con,
					       const char *path)
{
	char **objects = NULL;
	char subobj_path[WPAS_DBUS_OBJECT_PATH_MAX];
	int i;

	wpa_dbus_flush_object_changed_properties(con, path);

	if (!dbus_connection_list_registered(con, path, &objects))
		goto out;

	for (i = 0; objects[i]; i++) {
		os_snprintf(subobj_path, WPAS_DBUS_OBJECT_PATH_MAX,
			    "%s/%s", path, objects[i]);
		recursive_flush_changed_properties(con, subobj_path);
	}

out:
	dbus_free_string_array(objects);
}