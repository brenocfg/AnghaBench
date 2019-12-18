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
struct wpa_dbus_object_desc {int dummy; } ;
struct dl_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_interfaces (struct dl_list*,struct wpabuf*) ; 
 int /*<<< orphan*/  dl_list_init (struct dl_list*) ; 
 int /*<<< orphan*/  extract_interfaces (struct dl_list*,struct wpa_dbus_object_desc*) ; 

__attribute__((used)) static void add_wpas_interfaces(struct wpabuf *xml,
				struct wpa_dbus_object_desc *obj_dsc)
{
	struct dl_list ifaces;

	dl_list_init(&ifaces);
	extract_interfaces(&ifaces, obj_dsc);
	add_interfaces(&ifaces, xml);
}