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
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wpas_dbus_signal_bss (struct wpa_supplicant*,char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpas_dbus_signal_bss_added(struct wpa_supplicant *wpa_s,
				       const char *bss_obj_path)
{
	wpas_dbus_signal_bss(wpa_s, bss_obj_path, "BSSAdded", TRUE);
}