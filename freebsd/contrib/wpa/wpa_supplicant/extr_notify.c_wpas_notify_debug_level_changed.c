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
struct wpa_global {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_dbus_signal_debug_level_changed (struct wpa_global*) ; 

void wpas_notify_debug_level_changed(struct wpa_global *global)
{
	wpas_dbus_signal_debug_level_changed(global);
}