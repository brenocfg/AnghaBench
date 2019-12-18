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
struct wlan_iface {int dummy; } ;

/* Variables and functions */
#define  LEAF_wlanIfaceCountryCode 132 
#define  LEAF_wlanIfaceDesiredBssid 131 
#define  LEAF_wlanIfaceDesiredChannel 130 
#define  LEAF_wlanIfaceDesiredSsid 129 
#define  LEAF_wlanIfaceRegDomain 128 
 int wlan_config_get_bssid (struct wlan_iface*) ; 
 int wlan_config_get_country (struct wlan_iface*) ; 
 int wlan_config_get_dchannel (struct wlan_iface*) ; 
 int wlan_config_get_dssid (struct wlan_iface*) ; 
 int wlan_config_get_intval (struct wlan_iface*,int) ; 
 int wlan_config_snmp2ioctl (int) ; 

int
wlan_config_get_ioctl(struct wlan_iface *wif, int which)
{
	int op;

	switch (which) {
		case LEAF_wlanIfaceCountryCode:
			/* FALLTHROUGH */
		case LEAF_wlanIfaceRegDomain:
			return (wlan_config_get_country(wif));
		case LEAF_wlanIfaceDesiredSsid:
			return (wlan_config_get_dssid(wif));
		case LEAF_wlanIfaceDesiredChannel:
			return (wlan_config_get_dchannel(wif));
		case LEAF_wlanIfaceDesiredBssid:
			return (wlan_config_get_bssid(wif));
		default:
			op = wlan_config_snmp2ioctl(which);
			return (wlan_config_get_intval(wif, op));
	}

	return (-1);
}