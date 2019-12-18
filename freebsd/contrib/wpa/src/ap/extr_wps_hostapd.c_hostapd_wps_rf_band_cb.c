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
struct hostapd_data {TYPE_1__* iconf; } ;
struct TYPE_2__ {scalar_t__ hw_mode; } ;

/* Variables and functions */
 scalar_t__ HOSTAPD_MODE_IEEE80211A ; 
 scalar_t__ HOSTAPD_MODE_IEEE80211AD ; 
 int WPS_RF_24GHZ ; 
 int WPS_RF_50GHZ ; 
 int WPS_RF_60GHZ ; 

__attribute__((used)) static int hostapd_wps_rf_band_cb(void *ctx)
{
	struct hostapd_data *hapd = ctx;

	return hapd->iconf->hw_mode == HOSTAPD_MODE_IEEE80211A ?
		WPS_RF_50GHZ :
		hapd->iconf->hw_mode == HOSTAPD_MODE_IEEE80211AD ?
		WPS_RF_60GHZ : WPS_RF_24GHZ; /* FIX: dualband AP */
}