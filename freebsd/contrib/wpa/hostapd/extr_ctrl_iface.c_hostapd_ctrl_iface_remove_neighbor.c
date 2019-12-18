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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_ssid_value {int dummy; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int hostapd_neighbor_remove (struct hostapd_data*,int /*<<< orphan*/ *,struct wpa_ssid_value*) ; 
 scalar_t__ hwaddr_aton (char*,int /*<<< orphan*/ *) ; 
 char* os_strstr (char*,char*) ; 
 scalar_t__ ssid_parse (char*,struct wpa_ssid_value*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hostapd_ctrl_iface_remove_neighbor(struct hostapd_data *hapd,
					      char *buf)
{
	struct wpa_ssid_value ssid;
	u8 bssid[ETH_ALEN];
	char *tmp;

	if (hwaddr_aton(buf, bssid)) {
		wpa_printf(MSG_ERROR, "CTRL: REMOVE_NEIGHBOR: Bad BSSID");
		return -1;
	}

	tmp = os_strstr(buf, "ssid=");
	if (!tmp || ssid_parse(tmp + 5, &ssid)) {
		wpa_printf(MSG_ERROR,
			   "CTRL: REMOVE_NEIGHBORr: Bad or missing SSID");
		return -1;
	}

	return hostapd_neighbor_remove(hapd, bssid, &ssid);
}