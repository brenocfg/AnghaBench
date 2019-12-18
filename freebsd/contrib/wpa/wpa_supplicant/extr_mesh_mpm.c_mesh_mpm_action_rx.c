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
typedef  int u16 ;
struct wpa_supplicant {TYPE_1__* ifmsh; } ;
struct wpa_state_machine {int dummy; } ;
struct wpa_ie_data {int capabilities; } ;
struct wpa_channel_info {int /*<<< orphan*/  seg1_idx; int /*<<< orphan*/  chanwidth; } ;
struct sta_info {int my_lid; scalar_t__ plink_state; int peer_lid; int peer_aid; struct wpa_state_machine* wpa_sm; TYPE_4__* sae; } ;
struct mesh_peer_mgmt_ie {int const* llid; int const* plid; int const* reason; int /*<<< orphan*/  chosen_pmk; } ;
struct mesh_conf {int security; scalar_t__ ocv; } ;
struct ieee802_11_elems {int /*<<< orphan*/  oci_len; int /*<<< orphan*/  oci; scalar_t__ rsn_ie_len; scalar_t__ rsn_ie; int /*<<< orphan*/  peer_mgmt_len; int /*<<< orphan*/  peer_mgmt; int /*<<< orphan*/  mesh_config; int /*<<< orphan*/  mesh_id; } ;
struct TYPE_8__ {int action; int* variable; } ;
struct TYPE_9__ {TYPE_2__ slf_prot_action; } ;
struct TYPE_11__ {int /*<<< orphan*/  category; TYPE_3__ u; } ;
struct TYPE_12__ {TYPE_5__ action; } ;
struct ieee80211_mgmt {TYPE_6__ u; int /*<<< orphan*/  sa; } ;
struct hostapd_data {int /*<<< orphan*/  max_plinks; int /*<<< orphan*/  wpa_auth; } ;
typedef  enum plink_event { ____Placeholder_plink_event } plink_event ;
struct TYPE_10__ {scalar_t__ state; } ;
struct TYPE_7__ {struct mesh_conf* mconf; struct hostapd_data** bss; } ;

/* Variables and functions */
 int CLS_ACPT ; 
 int CNF_ACPT ; 
 int MESH_CONF_SEC_AMPE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int OPN_ACPT ; 
 int OPN_RJCT ; 
 scalar_t__ PLINK_BLOCKED ; 
#define  PLINK_CLOSE 130 
#define  PLINK_CONFIRM 129 
 scalar_t__ PLINK_ESTAB ; 
#define  PLINK_OPEN 128 
 scalar_t__ ParseFailed ; 
 int REQ_RJCT ; 
 scalar_t__ SAE_ACCEPTED ; 
 int /*<<< orphan*/  WLAN_ACTION_SELF_PROTECTED ; 
 int WLAN_REASON_MESH_INVALID_GTK ; 
 int WLAN_REASON_MESH_MAX_PEERS ; 
 int WPA_CAPABILITY_OCVC ; 
 int WPA_GET_LE16 (int const*) ; 
 struct sta_info* ap_get_sta (struct hostapd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_width_to_int (int /*<<< orphan*/ ) ; 
 scalar_t__ get_tx_parameters (struct sta_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ ieee802_11_parse_elems (int const*,size_t,struct ieee802_11_elems*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matches_local (struct wpa_supplicant*,struct ieee802_11_elems*) ; 
 struct sta_info* mesh_mpm_add_peer (struct wpa_supplicant*,int /*<<< orphan*/ ,struct ieee802_11_elems*) ; 
 int /*<<< orphan*/  mesh_mpm_fsm (struct wpa_supplicant*,struct sta_info*,int,int) ; 
 int /*<<< orphan*/  mesh_mpm_init_link (struct wpa_supplicant*,struct sta_info*) ; 
 int mesh_mpm_parse_peer_mgmt (struct wpa_supplicant*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mesh_peer_mgmt_ie*) ; 
 int mesh_rsn_process_ampe (struct wpa_supplicant*,struct sta_info*,struct ieee802_11_elems*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const*,size_t) ; 
 int /*<<< orphan*/  ocv_errorstr ; 
 scalar_t__ ocv_verify_tx_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_channel_info*,int,int) ; 
 int /*<<< orphan*/  plink_free_count (struct hostapd_data*) ; 
 scalar_t__ wpa_auth_pmksa_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_auth_set_ocv (struct wpa_state_machine*,int) ; 
 scalar_t__ wpa_auth_uses_ocv (struct wpa_state_machine*) ; 
 scalar_t__ wpa_drv_channel_info (struct wpa_supplicant*,struct wpa_channel_info*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int wpa_parse_wpa_ie_rsn (scalar_t__,scalar_t__,struct wpa_ie_data*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

void mesh_mpm_action_rx(struct wpa_supplicant *wpa_s,
			const struct ieee80211_mgmt *mgmt, size_t len)
{
	u8 action_field;
	struct hostapd_data *hapd = wpa_s->ifmsh->bss[0];
	struct mesh_conf *mconf = wpa_s->ifmsh->mconf;
	struct sta_info *sta;
	u16 plid = 0, llid = 0, aid = 0;
	enum plink_event event;
	struct ieee802_11_elems elems;
	struct mesh_peer_mgmt_ie peer_mgmt_ie;
	const u8 *ies;
	size_t ie_len;
	int ret;
	u16 reason = 0;

	if (mgmt->u.action.category != WLAN_ACTION_SELF_PROTECTED)
		return;

	action_field = mgmt->u.action.u.slf_prot_action.action;
	if (action_field != PLINK_OPEN &&
	    action_field != PLINK_CONFIRM &&
	    action_field != PLINK_CLOSE)
		return;

	ies = mgmt->u.action.u.slf_prot_action.variable;
	ie_len = (const u8 *) mgmt + len -
		mgmt->u.action.u.slf_prot_action.variable;

	/* at least expect mesh id and peering mgmt */
	if (ie_len < 2 + 2) {
		wpa_printf(MSG_DEBUG,
			   "MPM: Ignore too short action frame %u ie_len %u",
			   action_field, (unsigned int) ie_len);
		return;
	}
	wpa_printf(MSG_DEBUG, "MPM: Received PLINK action %u", action_field);

	if (action_field == PLINK_OPEN || action_field == PLINK_CONFIRM) {
		wpa_printf(MSG_DEBUG, "MPM: Capability 0x%x",
			   WPA_GET_LE16(ies));
		ies += 2;	/* capability */
		ie_len -= 2;
	}
	if (action_field == PLINK_CONFIRM) {
		aid = WPA_GET_LE16(ies);
		wpa_printf(MSG_DEBUG, "MPM: AID 0x%x", aid);
		ies += 2;	/* aid */
		ie_len -= 2;
	}

	/* check for mesh peering, mesh id and mesh config IEs */
	if (ieee802_11_parse_elems(ies, ie_len, &elems, 0) == ParseFailed) {
		wpa_printf(MSG_DEBUG, "MPM: Failed to parse PLINK IEs");
		return;
	}
	if (!elems.peer_mgmt) {
		wpa_printf(MSG_DEBUG,
			   "MPM: No Mesh Peering Management element");
		return;
	}
	if (action_field != PLINK_CLOSE) {
		if (!elems.mesh_id || !elems.mesh_config) {
			wpa_printf(MSG_DEBUG,
				   "MPM: No Mesh ID or Mesh Configuration element");
			return;
		}

		if (!matches_local(wpa_s, &elems)) {
			wpa_printf(MSG_DEBUG,
				   "MPM: Mesh ID or Mesh Configuration element do not match local MBSS");
			return;
		}
	}

	ret = mesh_mpm_parse_peer_mgmt(wpa_s, action_field,
				       elems.peer_mgmt,
				       elems.peer_mgmt_len,
				       &peer_mgmt_ie);
	if (ret) {
		wpa_printf(MSG_DEBUG, "MPM: Mesh parsing rejected frame");
		return;
	}

	/* the sender's llid is our plid and vice-versa */
	plid = WPA_GET_LE16(peer_mgmt_ie.llid);
	if (peer_mgmt_ie.plid)
		llid = WPA_GET_LE16(peer_mgmt_ie.plid);
	wpa_printf(MSG_DEBUG, "MPM: plid=0x%x llid=0x%x", plid, llid);

	if (action_field == PLINK_CLOSE)
		wpa_printf(MSG_DEBUG, "MPM: close reason=%u",
			   WPA_GET_LE16(peer_mgmt_ie.reason));

	sta = ap_get_sta(hapd, mgmt->sa);

	/*
	 * If this is an open frame from an unknown STA, and this is an
	 * open mesh, then go ahead and add the peer before proceeding.
	 */
	if (!sta && action_field == PLINK_OPEN &&
	    (!(mconf->security & MESH_CONF_SEC_AMPE) ||
	     wpa_auth_pmksa_get(hapd->wpa_auth, mgmt->sa, NULL)))
		sta = mesh_mpm_add_peer(wpa_s, mgmt->sa, &elems);

	if (!sta) {
		wpa_printf(MSG_DEBUG, "MPM: No STA entry for peer");
		return;
	}

#ifdef CONFIG_SAE
	/* peer is in sae_accepted? */
	if (sta->sae && sta->sae->state != SAE_ACCEPTED) {
		wpa_printf(MSG_DEBUG, "MPM: SAE not yet accepted for peer");
		return;
	}
#endif /* CONFIG_SAE */

	if (!sta->my_lid)
		mesh_mpm_init_link(wpa_s, sta);

	if (mconf->security & MESH_CONF_SEC_AMPE) {
		int res;

		res = mesh_rsn_process_ampe(wpa_s, sta, &elems,
					    &mgmt->u.action.category,
					    peer_mgmt_ie.chosen_pmk,
					    ies, ie_len);
		if (res) {
			wpa_printf(MSG_DEBUG,
				   "MPM: RSN process rejected frame (res=%d)",
				   res);
			if (action_field == PLINK_OPEN && res == -2) {
				/* AES-SIV decryption failed */
				mesh_mpm_fsm(wpa_s, sta, OPN_RJCT,
					     WLAN_REASON_MESH_INVALID_GTK);
			}
			return;
		}

#ifdef CONFIG_OCV
		if (action_field == PLINK_OPEN && elems.rsn_ie) {
			struct wpa_state_machine *sm = sta->wpa_sm;
			struct wpa_ie_data data;

			res = wpa_parse_wpa_ie_rsn(elems.rsn_ie - 2,
						   elems.rsn_ie_len + 2,
						   &data);
			if (res) {
				wpa_printf(MSG_DEBUG,
					   "Failed to parse RSN IE (res=%d)",
					   res);
				wpa_hexdump(MSG_DEBUG, "RSN IE", elems.rsn_ie,
					    elems.rsn_ie_len);
				return;
			}

			wpa_auth_set_ocv(sm, mconf->ocv &&
					 (data.capabilities &
					  WPA_CAPABILITY_OCVC));
		}

		if (action_field != PLINK_CLOSE &&
		    wpa_auth_uses_ocv(sta->wpa_sm)) {
			struct wpa_channel_info ci;
			int tx_chanwidth;
			int tx_seg1_idx;

			if (wpa_drv_channel_info(wpa_s, &ci) != 0) {
				wpa_printf(MSG_WARNING,
					   "MPM: Failed to get channel info to validate received OCI in MPM Confirm");
				return;
			}

			if (get_tx_parameters(
				    sta, channel_width_to_int(ci.chanwidth),
				    ci.seg1_idx, &tx_chanwidth,
				    &tx_seg1_idx) < 0)
				return;

			if (ocv_verify_tx_params(elems.oci, elems.oci_len, &ci,
						 tx_chanwidth, tx_seg1_idx) !=
			    0) {
				wpa_printf(MSG_WARNING, "MPM: %s",
					   ocv_errorstr);
				return;
			}
		}
#endif /* CONFIG_OCV */
	}

	if (sta->plink_state == PLINK_BLOCKED) {
		wpa_printf(MSG_DEBUG, "MPM: PLINK_BLOCKED");
		return;
	}

	/* Now we will figure out the appropriate event... */
	switch (action_field) {
	case PLINK_OPEN:
		if (plink_free_count(hapd) == 0) {
			event = REQ_RJCT;
			reason = WLAN_REASON_MESH_MAX_PEERS;
			wpa_printf(MSG_INFO,
				   "MPM: Peer link num over quota(%d)",
				   hapd->max_plinks);
		} else if (sta->peer_lid && sta->peer_lid != plid) {
			wpa_printf(MSG_DEBUG,
				   "MPM: peer_lid mismatch: 0x%x != 0x%x",
				   sta->peer_lid, plid);
			return; /* no FSM event */
		} else {
			sta->peer_lid = plid;
			event = OPN_ACPT;
		}
		break;
	case PLINK_CONFIRM:
		if (plink_free_count(hapd) == 0) {
			event = REQ_RJCT;
			reason = WLAN_REASON_MESH_MAX_PEERS;
			wpa_printf(MSG_INFO,
				   "MPM: Peer link num over quota(%d)",
				   hapd->max_plinks);
		} else if (sta->my_lid != llid ||
			   (sta->peer_lid && sta->peer_lid != plid)) {
			wpa_printf(MSG_DEBUG,
				   "MPM: lid mismatch: my_lid: 0x%x != 0x%x or peer_lid: 0x%x != 0x%x",
				   sta->my_lid, llid, sta->peer_lid, plid);
			return; /* no FSM event */
		} else {
			if (!sta->peer_lid)
				sta->peer_lid = plid;
			sta->peer_aid = aid;
			event = CNF_ACPT;
		}
		break;
	case PLINK_CLOSE:
		if (sta->plink_state == PLINK_ESTAB)
			/* Do not check for llid or plid. This does not
			 * follow the standard but since multiple plinks
			 * per cand are not supported, it is necessary in
			 * order to avoid a livelock when MP A sees an
			 * establish peer link to MP B but MP B does not
			 * see it. This can be caused by a timeout in
			 * B's peer link establishment or B being
			 * restarted.
			 */
			event = CLS_ACPT;
		else if (sta->peer_lid != plid) {
			wpa_printf(MSG_DEBUG,
				   "MPM: peer_lid mismatch: 0x%x != 0x%x",
				   sta->peer_lid, plid);
			return; /* no FSM event */
		} else if (peer_mgmt_ie.plid && sta->my_lid != llid) {
			wpa_printf(MSG_DEBUG,
				   "MPM: my_lid mismatch: 0x%x != 0x%x",
				   sta->my_lid, llid);
			return; /* no FSM event */
		} else {
			event = CLS_ACPT;
		}
		break;
	default:
		/*
		 * This cannot be hit due to the action_field check above, but
		 * compilers may not be able to figure that out and can warn
		 * about uninitialized event below.
		 */
		return;
	}
	mesh_mpm_fsm(wpa_s, sta, event, reason);
}