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
struct TYPE_2__ {int /*<<< orphan*/ * modes; } ;
struct wpa_supplicant {scalar_t__ setband; TYPE_1__ hw; } ;
struct wpa_driver_scan_params {scalar_t__ freqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_MODE_IEEE80211A ; 
 int /*<<< orphan*/  HOSTAPD_MODE_IEEE80211G ; 
 scalar_t__ WPA_SETBAND_2G ; 
 scalar_t__ WPA_SETBAND_5G ; 
 int /*<<< orphan*/  wpa_setband_scan_freqs_list (struct wpa_supplicant*,int /*<<< orphan*/ ,struct wpa_driver_scan_params*) ; 

__attribute__((used)) static void wpa_setband_scan_freqs(struct wpa_supplicant *wpa_s,
				   struct wpa_driver_scan_params *params)
{
	if (wpa_s->hw.modes == NULL)
		return; /* unknown what channels the driver supports */
	if (params->freqs)
		return; /* already using a limited channel set */
	if (wpa_s->setband == WPA_SETBAND_5G)
		wpa_setband_scan_freqs_list(wpa_s, HOSTAPD_MODE_IEEE80211A,
					    params);
	else if (wpa_s->setband == WPA_SETBAND_2G)
		wpa_setband_scan_freqs_list(wpa_s, HOSTAPD_MODE_IEEE80211G,
					    params);
}