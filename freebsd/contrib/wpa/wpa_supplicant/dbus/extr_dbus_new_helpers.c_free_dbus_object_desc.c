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
struct wpa_dbus_object_desc {struct wpa_dbus_object_desc* prop_changed_flags; struct wpa_dbus_object_desc* path; int /*<<< orphan*/  user_data; int /*<<< orphan*/  (* user_data_free_func ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct wpa_dbus_object_desc*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void free_dbus_object_desc(struct wpa_dbus_object_desc *obj_dsc)
{
	if (!obj_dsc)
		return;

	/* free handler's argument */
	if (obj_dsc->user_data_free_func)
		obj_dsc->user_data_free_func(obj_dsc->user_data);

	os_free(obj_dsc->path);
	os_free(obj_dsc->prop_changed_flags);
	os_free(obj_dsc);
}