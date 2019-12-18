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
struct wlan_iface {int reg_domain; char* country_code; } ;

/* Variables and functions */
#define  LEAF_wlanIfaceCountryCode 132 
#define  LEAF_wlanIfaceDesiredBssid 131 
#define  LEAF_wlanIfaceDesiredChannel 130 
#define  LEAF_wlanIfaceDesiredSsid 129 
#define  LEAF_wlanIfaceRegDomain 128 
 int wlan_config_set_bssid (struct wlan_iface*,char*) ; 
 int wlan_config_set_country (struct wlan_iface*,char*,int) ; 
 int wlan_config_set_dchannel (struct wlan_iface*,int) ; 
 int wlan_config_set_dssid (struct wlan_iface*,char*,int) ; 
 int wlan_config_set_intval (struct wlan_iface*,int,int) ; 
 int wlan_config_snmp2ioctl (int) ; 

int
wlan_config_set_ioctl(struct wlan_iface *wif, int which, int val,
    char *strval, int len)
{
	int op;

	switch (which) {
		case LEAF_wlanIfaceCountryCode:
			return (wlan_config_set_country(wif, strval,
			    wif->reg_domain));
		case LEAF_wlanIfaceRegDomain:
			return (wlan_config_set_country(wif, wif->country_code,
			    val));
		case LEAF_wlanIfaceDesiredSsid:
			return (wlan_config_set_dssid(wif, strval, len));
		case LEAF_wlanIfaceDesiredChannel:
			return (wlan_config_set_dchannel(wif, val));
		case LEAF_wlanIfaceDesiredBssid:
			return (wlan_config_set_bssid(wif, strval));
		default:
			op = wlan_config_snmp2ioctl(which);
			return (wlan_config_set_intval(wif, op, val));
	}

	return (-1);
}