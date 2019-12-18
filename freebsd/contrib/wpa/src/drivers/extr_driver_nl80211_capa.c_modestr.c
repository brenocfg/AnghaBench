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
typedef  enum hostapd_hw_mode { ____Placeholder_hostapd_hw_mode } hostapd_hw_mode ;

/* Variables and functions */
#define  HOSTAPD_MODE_IEEE80211A 131 
#define  HOSTAPD_MODE_IEEE80211AD 130 
#define  HOSTAPD_MODE_IEEE80211B 129 
#define  HOSTAPD_MODE_IEEE80211G 128 

__attribute__((used)) static const char * modestr(enum hostapd_hw_mode mode)
{
	switch (mode) {
	case HOSTAPD_MODE_IEEE80211B:
		return "802.11b";
	case HOSTAPD_MODE_IEEE80211G:
		return "802.11g";
	case HOSTAPD_MODE_IEEE80211A:
		return "802.11a";
	case HOSTAPD_MODE_IEEE80211AD:
		return "802.11ad";
	default:
		return "?";
	}
}