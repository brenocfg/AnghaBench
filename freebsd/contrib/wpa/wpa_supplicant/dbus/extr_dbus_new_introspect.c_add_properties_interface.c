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

/* Variables and functions */
 int /*<<< orphan*/  WPA_DBUS_PROPERTIES_GET ; 
 int /*<<< orphan*/  WPA_DBUS_PROPERTIES_GETALL ; 
 int /*<<< orphan*/  WPA_DBUS_PROPERTIES_INTERFACE ; 
 int /*<<< orphan*/  WPA_DBUS_PROPERTIES_SET ; 
 int /*<<< orphan*/  add_arg (struct wpabuf*,char*,char*,char*) ; 
 int /*<<< orphan*/  wpabuf_printf (struct wpabuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char*) ; 

__attribute__((used)) static void add_properties_interface(struct wpabuf *xml)
{
	wpabuf_printf(xml, "<interface name=\"%s\">",
		      WPA_DBUS_PROPERTIES_INTERFACE);

	wpabuf_printf(xml, "<method name=\"%s\">", WPA_DBUS_PROPERTIES_GET);
	add_arg(xml, "interface", "s", "in");
	add_arg(xml, "propname", "s", "in");
	add_arg(xml, "value", "v", "out");
	wpabuf_put_str(xml, "</method>");

	wpabuf_printf(xml, "<method name=\"%s\">", WPA_DBUS_PROPERTIES_GETALL);
	add_arg(xml, "interface", "s", "in");
	add_arg(xml, "props", "a{sv}", "out");
	wpabuf_put_str(xml, "</method>");

	wpabuf_printf(xml, "<method name=\"%s\">", WPA_DBUS_PROPERTIES_SET);
	add_arg(xml, "interface", "s", "in");
	add_arg(xml, "propname", "s", "in");
	add_arg(xml, "value", "v", "in");
	wpabuf_put_str(xml, "</method>");

	wpabuf_put_str(xml, "</interface>");
}