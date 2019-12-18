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
typedef  enum mb_band_id { ____Placeholder_mb_band_id } mb_band_id ;
typedef  enum hostapd_hw_mode { ____Placeholder_hostapd_hw_mode } hostapd_hw_mode ;

/* Variables and functions */
#define  HOSTAPD_MODE_IEEE80211A 131 
#define  HOSTAPD_MODE_IEEE80211AD 130 
#define  HOSTAPD_MODE_IEEE80211B 129 
#define  HOSTAPD_MODE_IEEE80211G 128 
 int MB_BAND_ID_WIFI_2_4GHZ ; 
 int MB_BAND_ID_WIFI_5GHZ ; 
 int MB_BAND_ID_WIFI_60GHZ ; 
 int /*<<< orphan*/  WPA_ASSERT (int /*<<< orphan*/ ) ; 

enum mb_band_id fst_hw_mode_to_band(enum hostapd_hw_mode mode)
{
	switch (mode) {
	case HOSTAPD_MODE_IEEE80211B:
	case HOSTAPD_MODE_IEEE80211G:
		return MB_BAND_ID_WIFI_2_4GHZ;
	case HOSTAPD_MODE_IEEE80211A:
		return MB_BAND_ID_WIFI_5GHZ;
	case HOSTAPD_MODE_IEEE80211AD:
		return MB_BAND_ID_WIFI_60GHZ;
	default:
		WPA_ASSERT(0);
		return MB_BAND_ID_WIFI_2_4GHZ;
	}
}