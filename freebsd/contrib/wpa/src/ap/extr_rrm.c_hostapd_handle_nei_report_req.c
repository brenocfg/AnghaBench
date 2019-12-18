#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wpa_ssid_value {int ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_7__ {int dialog_token; int* variable; } ;
struct TYPE_8__ {TYPE_1__ rrm; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
struct TYPE_10__ {TYPE_3__ action; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  sa; TYPE_4__ u; } ;
struct hostapd_data {TYPE_6__* conf; } ;
struct TYPE_11__ {int ssid_len; int const* ssid; } ;
struct TYPE_12__ {int* radio_measurements; TYPE_5__ ssid; } ;

/* Variables and functions */
#define  MEASURE_TYPE_LCI 129 
#define  MEASURE_TYPE_LOCATION_CIVIC 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int const SSID_MAX_LEN ; 
 int /*<<< orphan*/  WLAN_EID_MEASURE_REQUEST ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 int WLAN_RRM_CAPS_NEIGHBOR_REPORT ; 
 int* get_ie (int const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_parse_location_lci_req_age (int const*,int const) ; 
 int /*<<< orphan*/  hostapd_send_nei_report_resp (struct hostapd_data*,int /*<<< orphan*/ ,int,struct wpa_ssid_value*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int const) ; 

__attribute__((used)) static void hostapd_handle_nei_report_req(struct hostapd_data *hapd,
					  const u8 *buf, size_t len)
{
	const struct ieee80211_mgmt *mgmt = (const struct ieee80211_mgmt *) buf;
	const u8 *pos, *ie, *end;
	struct wpa_ssid_value ssid = {
		.ssid_len = 0
	};
	u8 token;
	u8 lci = 0, civic = 0; /* Measurement tokens */
	u16 lci_max_age = 0;

	if (!(hapd->conf->radio_measurements[0] &
	      WLAN_RRM_CAPS_NEIGHBOR_REPORT))
		return;

	end = buf + len;

	token = mgmt->u.action.u.rrm.dialog_token;
	pos = mgmt->u.action.u.rrm.variable;
	len = end - pos;

	ie = get_ie(pos, len, WLAN_EID_SSID);
	if (ie && ie[1] && ie[1] <= SSID_MAX_LEN) {
		ssid.ssid_len = ie[1];
		os_memcpy(ssid.ssid, ie + 2, ssid.ssid_len);
	} else {
		ssid.ssid_len = hapd->conf->ssid.ssid_len;
		os_memcpy(ssid.ssid, hapd->conf->ssid.ssid, ssid.ssid_len);
	}

	while ((ie = get_ie(pos, len, WLAN_EID_MEASURE_REQUEST))) {
		if (ie[1] < 3)
			break;

		wpa_printf(MSG_DEBUG,
			   "Neighbor report request, measure type %u",
			   ie[4]);

		switch (ie[4]) { /* Measurement Type */
		case MEASURE_TYPE_LCI:
			lci = ie[2]; /* Measurement Token */
			lci_max_age = hostapd_parse_location_lci_req_age(ie + 2,
									 ie[1]);
			break;
		case MEASURE_TYPE_LOCATION_CIVIC:
			civic = ie[2]; /* Measurement token */
			break;
		}

		pos = ie + ie[1] + 2;
		len = end - pos;
	}

	hostapd_send_nei_report_resp(hapd, mgmt->sa, token, &ssid, lci, civic,
				     lci_max_age);
}