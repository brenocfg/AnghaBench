#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hostapd_data {TYPE_2__* iface; } ;
struct TYPE_4__ {TYPE_1__* conf; } ;
struct TYPE_3__ {int hw_mode; } ;

/* Variables and functions */
#define  HOSTAPD_MODE_IEEE80211A 131 
#define  HOSTAPD_MODE_IEEE80211AD 130 
#define  HOSTAPD_MODE_IEEE80211B 129 
#define  HOSTAPD_MODE_IEEE80211G 128 

const char *radius_mode_txt(struct hostapd_data *hapd)
{
	switch (hapd->iface->conf->hw_mode) {
	case HOSTAPD_MODE_IEEE80211AD:
		return "802.11ad";
	case HOSTAPD_MODE_IEEE80211A:
		return "802.11a";
	case HOSTAPD_MODE_IEEE80211G:
		return "802.11g";
	case HOSTAPD_MODE_IEEE80211B:
	default:
		return "802.11b";
	}
}