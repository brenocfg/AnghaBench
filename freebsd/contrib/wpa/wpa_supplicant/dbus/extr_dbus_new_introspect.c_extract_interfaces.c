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
struct wpa_dbus_object_desc {int /*<<< orphan*/  properties; int /*<<< orphan*/  signals; int /*<<< orphan*/  methods; } ;
struct dl_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  extract_interfaces_methods (struct dl_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_interfaces_properties (struct dl_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_interfaces_signals (struct dl_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void extract_interfaces(struct dl_list *list,
			       struct wpa_dbus_object_desc *obj_dsc)
{
	extract_interfaces_methods(list, obj_dsc->methods);
	extract_interfaces_signals(list, obj_dsc->signals);
	extract_interfaces_properties(list, obj_dsc->properties);
}