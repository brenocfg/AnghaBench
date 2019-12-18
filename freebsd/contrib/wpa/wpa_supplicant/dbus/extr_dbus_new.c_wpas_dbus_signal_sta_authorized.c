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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_dbus_signal_sta (struct wpa_supplicant*,int /*<<< orphan*/  const*,char*) ; 

void wpas_dbus_signal_sta_authorized(struct wpa_supplicant *wpa_s,
				     const u8 *sta)
{
	wpas_dbus_signal_sta(wpa_s, sta, "StaAuthorized");
}