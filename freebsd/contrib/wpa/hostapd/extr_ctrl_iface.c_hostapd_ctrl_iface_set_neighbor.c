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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct wpa_ssid_value {int dummy; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {int* radio_measurements; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int WLAN_RRM_CAPS_NEIGHBOR_REPORT ; 
 int hostapd_neighbor_set (struct hostapd_data*,int /*<<< orphan*/ *,struct wpa_ssid_value*,struct wpabuf*,struct wpabuf*,struct wpabuf*,int) ; 
 scalar_t__ hwaddr_aton (char*,int /*<<< orphan*/ *) ; 
 char* os_strchr (char*,char) ; 
 char* os_strstr (char*,char*) ; 
 scalar_t__ ssid_parse (char*,struct wpa_ssid_value*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 struct wpabuf* wpabuf_parse_bin (char*) ; 

__attribute__((used)) static int hostapd_ctrl_iface_set_neighbor(struct hostapd_data *hapd, char *buf)
{
	struct wpa_ssid_value ssid;
	u8 bssid[ETH_ALEN];
	struct wpabuf *nr, *lci = NULL, *civic = NULL;
	int stationary = 0;
	char *tmp;
	int ret;

	if (!(hapd->conf->radio_measurements[0] &
	      WLAN_RRM_CAPS_NEIGHBOR_REPORT)) {
		wpa_printf(MSG_ERROR,
			   "CTRL: SET_NEIGHBOR: Neighbor report is not enabled");
		return -1;
	}

	if (hwaddr_aton(buf, bssid)) {
		wpa_printf(MSG_ERROR, "CTRL: SET_NEIGHBOR: Bad BSSID");
		return -1;
	}

	tmp = os_strstr(buf, "ssid=");
	if (!tmp || ssid_parse(tmp + 5, &ssid)) {
		wpa_printf(MSG_ERROR,
			   "CTRL: SET_NEIGHBOR: Bad or missing SSID");
		return -1;
	}
	buf = os_strchr(tmp + 6, tmp[5] == '"' ? '"' : ' ');
	if (!buf)
		return -1;

	tmp = os_strstr(buf, "nr=");
	if (!tmp) {
		wpa_printf(MSG_ERROR,
			   "CTRL: SET_NEIGHBOR: Missing Neighbor Report element");
		return -1;
	}

	buf = os_strchr(tmp, ' ');
	if (buf)
		*buf++ = '\0';

	nr = wpabuf_parse_bin(tmp + 3);
	if (!nr) {
		wpa_printf(MSG_ERROR,
			   "CTRL: SET_NEIGHBOR: Bad Neighbor Report element");
		return -1;
	}

	if (!buf)
		goto set;

	tmp = os_strstr(buf, "lci=");
	if (tmp) {
		buf = os_strchr(tmp, ' ');
		if (buf)
			*buf++ = '\0';
		lci = wpabuf_parse_bin(tmp + 4);
		if (!lci) {
			wpa_printf(MSG_ERROR,
				   "CTRL: SET_NEIGHBOR: Bad LCI subelement");
			wpabuf_free(nr);
			return -1;
		}
	}

	if (!buf)
		goto set;

	tmp = os_strstr(buf, "civic=");
	if (tmp) {
		buf = os_strchr(tmp, ' ');
		if (buf)
			*buf++ = '\0';
		civic = wpabuf_parse_bin(tmp + 6);
		if (!civic) {
			wpa_printf(MSG_ERROR,
				   "CTRL: SET_NEIGHBOR: Bad civic subelement");
			wpabuf_free(nr);
			wpabuf_free(lci);
			return -1;
		}
	}

	if (!buf)
		goto set;

	if (os_strstr(buf, "stat"))
		stationary = 1;

set:
	ret = hostapd_neighbor_set(hapd, bssid, &ssid, nr, lci, civic,
				   stationary);

	wpabuf_free(nr);
	wpabuf_free(lci);
	wpabuf_free(civic);

	return ret;
}