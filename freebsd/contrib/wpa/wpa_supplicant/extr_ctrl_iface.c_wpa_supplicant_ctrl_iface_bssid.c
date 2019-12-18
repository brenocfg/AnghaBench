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
struct wpa_supplicant {int /*<<< orphan*/  conf; } ;
struct wpa_ssid {int bssid_set; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int atoi (char*) ; 
 scalar_t__ hwaddr_aton (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 char* os_strchr (char*,char) ; 
 struct wpa_ssid* wpa_config_get_network (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wpa_supplicant_ctrl_iface_bssid(struct wpa_supplicant *wpa_s,
					   char *cmd)
{
	char *pos;
	int id;
	struct wpa_ssid *ssid;
	u8 bssid[ETH_ALEN];

	/* cmd: "<network id> <BSSID>" */
	pos = os_strchr(cmd, ' ');
	if (pos == NULL)
		return -1;
	*pos++ = '\0';
	id = atoi(cmd);
	wpa_printf(MSG_DEBUG, "CTRL_IFACE: id=%d bssid='%s'", id, pos);
	if (hwaddr_aton(pos, bssid)) {
		wpa_printf(MSG_DEBUG ,"CTRL_IFACE: invalid BSSID '%s'", pos);
		return -1;
	}

	ssid = wpa_config_get_network(wpa_s->conf, id);
	if (ssid == NULL) {
		wpa_printf(MSG_DEBUG, "CTRL_IFACE: Could not find SSID id=%d "
			   "to update", id);
		return -1;
	}

	os_memcpy(ssid->bssid, bssid, ETH_ALEN);
	ssid->bssid_set = !is_zero_ether_addr(bssid);

	return 0;
}