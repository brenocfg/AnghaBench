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

/* Variables and functions */
#define  HOSTAPD_MODE_IEEE80211A 131 
#define  HOSTAPD_MODE_IEEE80211AD 130 
#define  HOSTAPD_MODE_IEEE80211B 129 
#define  HOSTAPD_MODE_IEEE80211G 128 

const char * hostapd_hw_mode_txt(int mode)
{
	switch (mode) {
	case HOSTAPD_MODE_IEEE80211A:
		return "IEEE 802.11a";
	case HOSTAPD_MODE_IEEE80211B:
		return "IEEE 802.11b";
	case HOSTAPD_MODE_IEEE80211G:
		return "IEEE 802.11g";
	case HOSTAPD_MODE_IEEE80211AD:
		return "IEEE 802.11ad";
	default:
		return "UNKNOWN";
	}
}