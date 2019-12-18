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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  wpas_dbus_signal_network (struct wpa_supplicant*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpas_dbus_signal_network_removed(struct wpa_supplicant *wpa_s,
					     int id)
{
	wpas_dbus_signal_network(wpa_s, id, "NetworkRemoved", FALSE);
}