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
struct wpa_dbus_property_desc {scalar_t__ setter; scalar_t__ getter; int /*<<< orphan*/  type; int /*<<< orphan*/  dbus_property; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpabuf_printf (struct wpabuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void add_property(struct wpabuf *xml,
			 const struct wpa_dbus_property_desc *dsc)
{
	wpabuf_printf(xml, "<property name=\"%s\" type=\"%s\" "
		      "access=\"%s%s\"/>",
		      dsc->dbus_property, dsc->type,
		      dsc->getter ? "read" : "",
		      dsc->setter ? "write" : "");
}