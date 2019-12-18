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
struct wpabuf {int dummy; } ;
typedef  int /*<<< orphan*/  DBusConnection ;

/* Variables and functions */
 int /*<<< orphan*/  dbus_connection_list_registered (int /*<<< orphan*/ *,char const*,char***) ; 
 int /*<<< orphan*/  dbus_free_string_array (char**) ; 
 int /*<<< orphan*/  wpabuf_printf (struct wpabuf*,char*,char*) ; 

__attribute__((used)) static void add_child_nodes(struct wpabuf *xml, DBusConnection *con,
			    const char *path)
{
	char **children;
	int i;

	/* add child nodes to introspection tree */
	dbus_connection_list_registered(con, path, &children);
	for (i = 0; children[i]; i++)
		wpabuf_printf(xml, "<node name=\"%s\"/>", children[i]);
	dbus_free_string_array(children);
}