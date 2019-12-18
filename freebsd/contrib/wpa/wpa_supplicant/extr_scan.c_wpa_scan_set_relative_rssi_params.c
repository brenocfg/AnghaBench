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
struct TYPE_2__ {scalar_t__ relative_rssi_set; scalar_t__ relative_adjust_rssi; int /*<<< orphan*/  relative_adjust_band; int /*<<< orphan*/  relative_rssi; } ;
struct wpa_supplicant {scalar_t__ wpa_state; int drv_flags; TYPE_1__ srp; } ;
struct wpa_driver_scan_params {int relative_rssi_set; scalar_t__ relative_adjust_rssi; int /*<<< orphan*/  relative_adjust_band; int /*<<< orphan*/  relative_rssi; } ;

/* Variables and functions */
 scalar_t__ WPA_COMPLETED ; 
 int WPA_DRIVER_FLAGS_SCHED_SCAN_RELATIVE_RSSI ; 

__attribute__((used)) static void
wpa_scan_set_relative_rssi_params(struct wpa_supplicant *wpa_s,
				  struct wpa_driver_scan_params *params)
{
	if (wpa_s->wpa_state != WPA_COMPLETED ||
	    !(wpa_s->drv_flags & WPA_DRIVER_FLAGS_SCHED_SCAN_RELATIVE_RSSI) ||
	    wpa_s->srp.relative_rssi_set == 0)
		return;

	params->relative_rssi_set = 1;
	params->relative_rssi = wpa_s->srp.relative_rssi;

	if (wpa_s->srp.relative_adjust_rssi == 0)
		return;

	params->relative_adjust_band = wpa_s->srp.relative_adjust_band;
	params->relative_adjust_rssi = wpa_s->srp.relative_adjust_rssi;
}