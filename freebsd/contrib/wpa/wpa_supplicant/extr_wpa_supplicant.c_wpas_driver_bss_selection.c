#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {int drv_flags; TYPE_1__* conf; } ;
struct TYPE_2__ {int ap_scan; } ;

/* Variables and functions */
 int WPA_DRIVER_FLAGS_BSS_SELECTION ; 

int wpas_driver_bss_selection(struct wpa_supplicant *wpa_s)
{
	return wpa_s->conf->ap_scan == 2 ||
		(wpa_s->drv_flags & WPA_DRIVER_FLAGS_BSS_SELECTION);
}