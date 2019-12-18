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
struct wpa_supplicant {int assoc_freq; int /*<<< orphan*/  current_ssid; } ;

/* Variables and functions */
 int WPS_RF_24GHZ ; 
 int WPS_RF_50GHZ ; 
 int WPS_RF_60GHZ ; 

__attribute__((used)) static int wpa_supplicant_wps_rf_band(void *ctx)
{
	struct wpa_supplicant *wpa_s = ctx;

	if (!wpa_s->current_ssid || !wpa_s->assoc_freq)
		return 0;

	return (wpa_s->assoc_freq > 50000) ? WPS_RF_60GHZ :
		(wpa_s->assoc_freq > 2484) ? WPS_RF_50GHZ : WPS_RF_24GHZ;
}