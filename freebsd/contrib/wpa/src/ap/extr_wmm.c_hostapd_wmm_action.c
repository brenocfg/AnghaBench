#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wmm_tspec_element {int dummy; } ;
struct sta_info {int flags; } ;
struct ieee802_11_elems {int wmm_tspec_len; scalar_t__ wmm_tspec; } ;
struct TYPE_5__ {int action_code; } ;
struct TYPE_6__ {TYPE_1__ wmm_action; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ action; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  sa; TYPE_4__ u; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_LEVEL_DEBUG ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_IEEE80211 ; 
 size_t IEEE80211_HDRLEN ; 
 scalar_t__ ParseFailed ; 
 int WLAN_STA_ASSOC ; 
 int WLAN_STA_WMM ; 
#define  WMM_ACTION_CODE_ADDTS_REQ 130 
#define  WMM_ACTION_CODE_ADDTS_RESP 129 
#define  WMM_ACTION_CODE_DELTS 128 
 struct sta_info* ap_get_sta (struct hostapd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_logger (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ieee802_11_parse_elems (int /*<<< orphan*/  const*,int,struct ieee802_11_elems*,int) ; 
 int /*<<< orphan*/  wmm_addts_req (struct hostapd_data*,struct ieee80211_mgmt const*,struct wmm_tspec_element*,size_t) ; 
 int /*<<< orphan*/  wmm_setup_request (struct hostapd_data*,struct ieee80211_mgmt const*,size_t) ; 
 int /*<<< orphan*/  wmm_teardown (struct hostapd_data*,struct ieee80211_mgmt const*,size_t) ; 

void hostapd_wmm_action(struct hostapd_data *hapd,
			const struct ieee80211_mgmt *mgmt, size_t len)
{
	int action_code;
	int left = len - IEEE80211_HDRLEN - 4;
	const u8 *pos = ((const u8 *) mgmt) + IEEE80211_HDRLEN + 4;
	struct ieee802_11_elems elems;
	struct sta_info *sta = ap_get_sta(hapd, mgmt->sa);

	/* check that the request comes from a valid station */
	if (!sta ||
	    (sta->flags & (WLAN_STA_ASSOC | WLAN_STA_WMM)) !=
	    (WLAN_STA_ASSOC | WLAN_STA_WMM)) {
		hostapd_logger(hapd, mgmt->sa, HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_DEBUG,
			       "wmm action received is not from associated wmm"
			       " station");
		/* TODO: respond with action frame refused status code */
		return;
	}

	if (left < 0)
		return; /* not a valid WMM Action frame */

	/* extract the tspec info element */
	if (ieee802_11_parse_elems(pos, left, &elems, 1) == ParseFailed) {
		hostapd_logger(hapd, mgmt->sa, HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_DEBUG,
			       "hostapd_wmm_action - could not parse wmm "
			       "action");
		/* TODO: respond with action frame invalid parameters status
		 * code */
		return;
	}

	if (!elems.wmm_tspec ||
	    elems.wmm_tspec_len != (sizeof(struct wmm_tspec_element) - 2)) {
		hostapd_logger(hapd, mgmt->sa, HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_DEBUG,
			       "hostapd_wmm_action - missing or wrong length "
			       "tspec");
		/* TODO: respond with action frame invalid parameters status
		 * code */
		return;
	}

	/* TODO: check the request is for an AC with ACM set, if not, refuse
	 * request */

	action_code = mgmt->u.action.u.wmm_action.action_code;
	switch (action_code) {
	case WMM_ACTION_CODE_ADDTS_REQ:
		wmm_addts_req(hapd, mgmt, (struct wmm_tspec_element *)
			      (elems.wmm_tspec - 2), len);
		return;
#if 0
	/* TODO: needed for client implementation */
	case WMM_ACTION_CODE_ADDTS_RESP:
		wmm_setup_request(hapd, mgmt, len);
		return;
	/* TODO: handle station teardown requests */
	case WMM_ACTION_CODE_DELTS:
		wmm_teardown(hapd, mgmt, len);
		return;
#endif
	}

	hostapd_logger(hapd, mgmt->sa, HOSTAPD_MODULE_IEEE80211,
		       HOSTAPD_LEVEL_DEBUG,
		       "hostapd_wmm_action - unknown action code %d",
		       action_code);
}