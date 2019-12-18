#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct wpa_driver_ap_params* variable; void* capab_info; void* beacon_int; } ;
struct TYPE_11__ {TYPE_1__ beacon; } ;
struct wpa_driver_ap_params {size_t head_len; size_t tail_len; size_t proberesp_len; int ssid_len; int pairwise_ciphers; int wpa_version; int privacy; int smps_mode; int cts_protect; int preamble; int short_slot_time; int ht_opmode; int osen; int ftm_responder; int /*<<< orphan*/  civic; int /*<<< orphan*/  lci; int /*<<< orphan*/  pbss; int /*<<< orphan*/  multicast_to_unicast; int /*<<< orphan*/  disable_dgaf; int /*<<< orphan*/  p2p_go_ctwindow; int /*<<< orphan*/  ap_max_inactivity; int /*<<< orphan*/  access_network_type; int /*<<< orphan*/  hessid; scalar_t__ interworking; int /*<<< orphan*/  isolate; int /*<<< orphan*/  hide_ssid; int /*<<< orphan*/  auth_algs; int /*<<< orphan*/  key_mgmt_suites; int /*<<< orphan*/  group_cipher; int /*<<< orphan*/  ssid; int /*<<< orphan*/  rate_type; int /*<<< orphan*/  beacon_rate; int /*<<< orphan*/  basic_rates; scalar_t__ beacon_int; int /*<<< orphan*/  dtim_period; struct wpa_driver_ap_params* proberesp; struct wpa_driver_ap_params* tail; struct wpa_driver_ap_params* head; TYPE_2__ u; struct wpa_driver_ap_params* bssid; struct wpa_driver_ap_params* sa; struct wpa_driver_ap_params* da; void* duration; int /*<<< orphan*/  frame_control; } ;
typedef  struct wpa_driver_ap_params u8 ;
typedef  scalar_t__ u16 ;
struct ieee80211_vht_operation {int dummy; } ;
struct ieee80211_vht_capabilities {int dummy; } ;
struct ieee80211_spatial_reuse {int dummy; } ;
struct ieee80211_mgmt {size_t head_len; size_t tail_len; size_t proberesp_len; int ssid_len; int pairwise_ciphers; int wpa_version; int privacy; int smps_mode; int cts_protect; int preamble; int short_slot_time; int ht_opmode; int osen; int ftm_responder; int /*<<< orphan*/  civic; int /*<<< orphan*/  lci; int /*<<< orphan*/  pbss; int /*<<< orphan*/  multicast_to_unicast; int /*<<< orphan*/  disable_dgaf; int /*<<< orphan*/  p2p_go_ctwindow; int /*<<< orphan*/  ap_max_inactivity; int /*<<< orphan*/  access_network_type; int /*<<< orphan*/  hessid; scalar_t__ interworking; int /*<<< orphan*/  isolate; int /*<<< orphan*/  hide_ssid; int /*<<< orphan*/  auth_algs; int /*<<< orphan*/  key_mgmt_suites; int /*<<< orphan*/  group_cipher; int /*<<< orphan*/  ssid; int /*<<< orphan*/  rate_type; int /*<<< orphan*/  beacon_rate; int /*<<< orphan*/  basic_rates; scalar_t__ beacon_int; int /*<<< orphan*/  dtim_period; struct ieee80211_mgmt* proberesp; struct ieee80211_mgmt* tail; struct ieee80211_mgmt* head; TYPE_2__ u; struct ieee80211_mgmt* bssid; struct ieee80211_mgmt* sa; struct ieee80211_mgmt* da; void* duration; int /*<<< orphan*/  frame_control; } ;
struct ieee80211_he_operation {int dummy; } ;
struct ieee80211_he_mu_edca_parameter_set {int dummy; } ;
struct ieee80211_he_capabilities {int dummy; } ;
struct hostapd_data {int cs_c_off_beacon; int cs_c_off_ecsa_beacon; TYPE_9__* iface; TYPE_7__* conf; TYPE_6__* iconf; scalar_t__ p2p_beacon_ie; scalar_t__ wps_beacon_ie; int /*<<< orphan*/  own_addr; } ;
struct TYPE_18__ {scalar_t__ num_sta_no_short_preamble; scalar_t__ num_sta_no_short_slot_time; int ht_op_mode; int drv_flags; TYPE_8__* conf; TYPE_5__* current_mode; int /*<<< orphan*/  basic_rates; scalar_t__ fst_ies; } ;
struct TYPE_17__ {int /*<<< orphan*/  civic; int /*<<< orphan*/  lci; } ;
struct TYPE_12__ {scalar_t__ keys_set; } ;
struct TYPE_13__ {int ssid_len; TYPE_3__ wep; int /*<<< orphan*/  ssid; } ;
struct TYPE_16__ {int ignore_broadcast_ssid; int wpa; int p2p; int wpa_pairwise; int rsn_pairwise; scalar_t__ ftm_responder; int /*<<< orphan*/  pbss; int /*<<< orphan*/  multicast_to_unicast; scalar_t__ osen; int /*<<< orphan*/  disable_dgaf; int /*<<< orphan*/  ap_max_inactivity; int /*<<< orphan*/  access_network_type; int /*<<< orphan*/  hessid; scalar_t__ interworking; scalar_t__ disable_11n; int /*<<< orphan*/  isolate; scalar_t__ individual_wep_key_len; scalar_t__ default_wep_key_len; scalar_t__ ieee802_1x; TYPE_4__ ssid; int /*<<< orphan*/  auth_algs; int /*<<< orphan*/  wpa_key_mgmt; int /*<<< orphan*/  wpa_group; int /*<<< orphan*/  dtim_period; scalar_t__ vendor_elements; scalar_t__ wps_state; scalar_t__ vendor_vht; int /*<<< orphan*/  disable_11ac; } ;
struct TYPE_15__ {int ht_capab; scalar_t__ preamble; int /*<<< orphan*/  p2p_go_ctwindow; int /*<<< orphan*/  ieee80211n; int /*<<< orphan*/  rate_type; int /*<<< orphan*/  beacon_rate; scalar_t__ beacon_int; scalar_t__ ieee80211ax; scalar_t__ ieee80211ac; } ;
struct TYPE_14__ {scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEACON_HEAD_BUF_SIZE ; 
 size_t BEACON_TAIL_BUF_SIZE ; 
 int ERP_INFO_USE_PROTECTION ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  HIDDEN_SSID_ZERO_CONTENTS ; 
 int /*<<< orphan*/  HIDDEN_SSID_ZERO_LEN ; 
 scalar_t__ HOSTAPD_MODE_IEEE80211G ; 
 int HT_CAP_INFO_SMPS_MASK ; 
 int /*<<< orphan*/  IEEE80211_FC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_MODE_AP ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  NO_SSID_HIDING ; 
 int P2P_ENABLED ; 
 int P2P_GROUP_OWNER ; 
 int P2P_MANAGE ; 
 scalar_t__ SHORT_PREAMBLE ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 int /*<<< orphan*/  WLAN_FC_STYPE_BEACON ; 
 int /*<<< orphan*/  WLAN_FC_TYPE_MGMT ; 
 int WPA_DRIVER_FLAGS_FTM_RESPONDER ; 
 int WPA_PROTO_RSN ; 
 int WPA_PROTO_WPA ; 
 void* host_to_le16 (scalar_t__) ; 
 struct wpa_driver_ap_params* hostapd_eid_adv_proto (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_bss_load (struct hostapd_data*,struct wpa_driver_ap_params*,int) ; 
 struct wpa_driver_ap_params* hostapd_eid_country (struct hostapd_data*,struct wpa_driver_ap_params*,int) ; 
 struct wpa_driver_ap_params* hostapd_eid_csa (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_ds_params (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_ecsa (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_erp_info (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_ext_capab (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_ext_supp_rates (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_fils_indic (struct hostapd_data*,struct wpa_driver_ap_params*,int /*<<< orphan*/ ) ; 
 struct wpa_driver_ap_params* hostapd_eid_he_capab (struct hostapd_data*,struct wpa_driver_ap_params*,int /*<<< orphan*/ ) ; 
 struct wpa_driver_ap_params* hostapd_eid_he_mu_edca_parameter_set (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_he_operation (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_hs20_indication (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_ht_capabilities (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_ht_operation (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_interworking (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_mbo (struct hostapd_data*,struct wpa_driver_ap_params*,int) ; 
 struct wpa_driver_ap_params* hostapd_eid_osen (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_owe_trans (struct hostapd_data*,struct wpa_driver_ap_params*,int) ; 
 scalar_t__ hostapd_eid_owe_trans_len (struct hostapd_data*) ; 
 struct wpa_driver_ap_params* hostapd_eid_p2p_manage (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_pwr_constraint (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_rm_enabled_capab (struct hostapd_data*,struct wpa_driver_ap_params*,int) ; 
 struct wpa_driver_ap_params* hostapd_eid_roaming_consortium (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_secondary_channel (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_spatial_reuse (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_supp_rates (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_supported_op_classes (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_time_adv (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_txpower_envelope (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_vendor_vht (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_vht_capabilities (struct hostapd_data*,struct wpa_driver_ap_params*,int /*<<< orphan*/ ) ; 
 struct wpa_driver_ap_params* hostapd_eid_vht_operation (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_wb_chsw_wrapper (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_wmm (struct hostapd_data*,struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* hostapd_eid_wpa (struct hostapd_data*,struct wpa_driver_ap_params*,int) ; 
 scalar_t__ hostapd_mbo_ie_len (struct hostapd_data*) ; 
 scalar_t__ hostapd_own_capab_info (struct hostapd_data*) ; 
 struct wpa_driver_ap_params* hostapd_probe_resp_offloads (struct hostapd_data*,size_t*) ; 
 int ieee802_11_erp_info (struct hostapd_data*) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct wpa_driver_ap_params*) ; 
 struct wpa_driver_ap_params* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (struct wpa_driver_ap_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_memset (struct wpa_driver_ap_params*,int,int) ; 
 struct wpa_driver_ap_params* os_zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_head (scalar_t__) ; 
 int wpabuf_len (scalar_t__) ; 

int ieee802_11_build_ap_params(struct hostapd_data *hapd,
			       struct wpa_driver_ap_params *params)
{
	struct ieee80211_mgmt *head = NULL;
	u8 *tail = NULL;
	size_t head_len = 0, tail_len = 0;
	u8 *resp = NULL;
	size_t resp_len = 0;
#ifdef NEED_AP_MLME
	u16 capab_info;
	u8 *pos, *tailpos, *csa_pos;

#define BEACON_HEAD_BUF_SIZE 256
#define BEACON_TAIL_BUF_SIZE 512
	head = os_zalloc(BEACON_HEAD_BUF_SIZE);
	tail_len = BEACON_TAIL_BUF_SIZE;
#ifdef CONFIG_WPS
	if (hapd->conf->wps_state && hapd->wps_beacon_ie)
		tail_len += wpabuf_len(hapd->wps_beacon_ie);
#endif /* CONFIG_WPS */
#ifdef CONFIG_P2P
	if (hapd->p2p_beacon_ie)
		tail_len += wpabuf_len(hapd->p2p_beacon_ie);
#endif /* CONFIG_P2P */
#ifdef CONFIG_FST
	if (hapd->iface->fst_ies)
		tail_len += wpabuf_len(hapd->iface->fst_ies);
#endif /* CONFIG_FST */
	if (hapd->conf->vendor_elements)
		tail_len += wpabuf_len(hapd->conf->vendor_elements);

#ifdef CONFIG_IEEE80211AC
	if (hapd->conf->vendor_vht) {
		tail_len += 5 + 2 + sizeof(struct ieee80211_vht_capabilities) +
			2 + sizeof(struct ieee80211_vht_operation);
	}
#endif /* CONFIG_IEEE80211AC */

#ifdef CONFIG_IEEE80211AX
	if (hapd->iconf->ieee80211ax) {
		tail_len += 3 + sizeof(struct ieee80211_he_capabilities) +
			3 + sizeof(struct ieee80211_he_operation) +
			3 + sizeof(struct ieee80211_he_mu_edca_parameter_set) +
			3 + sizeof(struct ieee80211_spatial_reuse);
	}
#endif /* CONFIG_IEEE80211AX */

	tail_len += hostapd_mbo_ie_len(hapd);
	tail_len += hostapd_eid_owe_trans_len(hapd);

	tailpos = tail = os_malloc(tail_len);
	if (head == NULL || tail == NULL) {
		wpa_printf(MSG_ERROR, "Failed to set beacon data");
		os_free(head);
		os_free(tail);
		return -1;
	}

	head->frame_control = IEEE80211_FC(WLAN_FC_TYPE_MGMT,
					   WLAN_FC_STYPE_BEACON);
	head->duration = host_to_le16(0);
	os_memset(head->da, 0xff, ETH_ALEN);

	os_memcpy(head->sa, hapd->own_addr, ETH_ALEN);
	os_memcpy(head->bssid, hapd->own_addr, ETH_ALEN);
	head->u.beacon.beacon_int =
		host_to_le16(hapd->iconf->beacon_int);

	/* hardware or low-level driver will setup seq_ctrl and timestamp */
	capab_info = hostapd_own_capab_info(hapd);
	head->u.beacon.capab_info = host_to_le16(capab_info);
	pos = &head->u.beacon.variable[0];

	/* SSID */
	*pos++ = WLAN_EID_SSID;
	if (hapd->conf->ignore_broadcast_ssid == 2) {
		/* clear the data, but keep the correct length of the SSID */
		*pos++ = hapd->conf->ssid.ssid_len;
		os_memset(pos, 0, hapd->conf->ssid.ssid_len);
		pos += hapd->conf->ssid.ssid_len;
	} else if (hapd->conf->ignore_broadcast_ssid) {
		*pos++ = 0; /* empty SSID */
	} else {
		*pos++ = hapd->conf->ssid.ssid_len;
		os_memcpy(pos, hapd->conf->ssid.ssid,
			  hapd->conf->ssid.ssid_len);
		pos += hapd->conf->ssid.ssid_len;
	}

	/* Supported rates */
	pos = hostapd_eid_supp_rates(hapd, pos);

	/* DS Params */
	pos = hostapd_eid_ds_params(hapd, pos);

	head_len = pos - (u8 *) head;

	tailpos = hostapd_eid_country(hapd, tailpos,
				      tail + BEACON_TAIL_BUF_SIZE - tailpos);

	/* Power Constraint element */
	tailpos = hostapd_eid_pwr_constraint(hapd, tailpos);

	/* CSA IE */
	csa_pos = hostapd_eid_csa(hapd, tailpos);
	if (csa_pos != tailpos)
		hapd->cs_c_off_beacon = csa_pos - tail - 1;
	tailpos = csa_pos;

	/* ERP Information element */
	tailpos = hostapd_eid_erp_info(hapd, tailpos);

	/* Extended supported rates */
	tailpos = hostapd_eid_ext_supp_rates(hapd, tailpos);

	/* RSN, MDIE */
	if (hapd->conf->wpa != WPA_PROTO_WPA)
		tailpos = hostapd_eid_wpa(hapd, tailpos,
					  tail + BEACON_TAIL_BUF_SIZE -
					  tailpos);

	tailpos = hostapd_eid_rm_enabled_capab(hapd, tailpos,
					       tail + BEACON_TAIL_BUF_SIZE -
					       tailpos);

	tailpos = hostapd_eid_bss_load(hapd, tailpos,
				       tail + BEACON_TAIL_BUF_SIZE - tailpos);

	/* eCSA IE */
	csa_pos = hostapd_eid_ecsa(hapd, tailpos);
	if (csa_pos != tailpos)
		hapd->cs_c_off_ecsa_beacon = csa_pos - tail - 1;
	tailpos = csa_pos;

	tailpos = hostapd_eid_supported_op_classes(hapd, tailpos);

#ifdef CONFIG_IEEE80211N
	/* Secondary Channel Offset element */
	/* TODO: The standard doesn't specify a position for this element. */
	tailpos = hostapd_eid_secondary_channel(hapd, tailpos);

	tailpos = hostapd_eid_ht_capabilities(hapd, tailpos);
	tailpos = hostapd_eid_ht_operation(hapd, tailpos);
#endif /* CONFIG_IEEE80211N */

	tailpos = hostapd_eid_ext_capab(hapd, tailpos);

	/*
	 * TODO: Time Advertisement element should only be included in some
	 * DTIM Beacon frames.
	 */
	tailpos = hostapd_eid_time_adv(hapd, tailpos);

	tailpos = hostapd_eid_interworking(hapd, tailpos);
	tailpos = hostapd_eid_adv_proto(hapd, tailpos);
	tailpos = hostapd_eid_roaming_consortium(hapd, tailpos);

#ifdef CONFIG_FST
	if (hapd->iface->fst_ies) {
		os_memcpy(tailpos, wpabuf_head(hapd->iface->fst_ies),
			  wpabuf_len(hapd->iface->fst_ies));
		tailpos += wpabuf_len(hapd->iface->fst_ies);
	}
#endif /* CONFIG_FST */

#ifdef CONFIG_IEEE80211AC
	if (hapd->iconf->ieee80211ac && !hapd->conf->disable_11ac) {
		tailpos = hostapd_eid_vht_capabilities(hapd, tailpos, 0);
		tailpos = hostapd_eid_vht_operation(hapd, tailpos);
		tailpos = hostapd_eid_txpower_envelope(hapd, tailpos);
		tailpos = hostapd_eid_wb_chsw_wrapper(hapd, tailpos);
	}
#endif /* CONFIG_IEEE80211AC */

	tailpos = hostapd_eid_fils_indic(hapd, tailpos, 0);

#ifdef CONFIG_IEEE80211AX
	if (hapd->iconf->ieee80211ax) {
		tailpos = hostapd_eid_he_capab(hapd, tailpos,
					       IEEE80211_MODE_AP);
		tailpos = hostapd_eid_he_operation(hapd, tailpos);
		tailpos = hostapd_eid_he_mu_edca_parameter_set(hapd, tailpos);
		tailpos = hostapd_eid_spatial_reuse(hapd, tailpos);
	}
#endif /* CONFIG_IEEE80211AX */

#ifdef CONFIG_IEEE80211AC
	if (hapd->conf->vendor_vht)
		tailpos = hostapd_eid_vendor_vht(hapd, tailpos);
#endif /* CONFIG_IEEE80211AC */

	/* WPA */
	if (hapd->conf->wpa == WPA_PROTO_WPA)
		tailpos = hostapd_eid_wpa(hapd, tailpos,
					  tail + BEACON_TAIL_BUF_SIZE -
					  tailpos);

	/* Wi-Fi Alliance WMM */
	tailpos = hostapd_eid_wmm(hapd, tailpos);

#ifdef CONFIG_WPS
	if (hapd->conf->wps_state && hapd->wps_beacon_ie) {
		os_memcpy(tailpos, wpabuf_head(hapd->wps_beacon_ie),
			  wpabuf_len(hapd->wps_beacon_ie));
		tailpos += wpabuf_len(hapd->wps_beacon_ie);
	}
#endif /* CONFIG_WPS */

#ifdef CONFIG_P2P
	if ((hapd->conf->p2p & P2P_ENABLED) && hapd->p2p_beacon_ie) {
		os_memcpy(tailpos, wpabuf_head(hapd->p2p_beacon_ie),
			  wpabuf_len(hapd->p2p_beacon_ie));
		tailpos += wpabuf_len(hapd->p2p_beacon_ie);
	}
#endif /* CONFIG_P2P */
#ifdef CONFIG_P2P_MANAGER
	if ((hapd->conf->p2p & (P2P_MANAGE | P2P_ENABLED | P2P_GROUP_OWNER)) ==
	    P2P_MANAGE)
		tailpos = hostapd_eid_p2p_manage(hapd, tailpos);
#endif /* CONFIG_P2P_MANAGER */

#ifdef CONFIG_HS20
	tailpos = hostapd_eid_hs20_indication(hapd, tailpos);
	tailpos = hostapd_eid_osen(hapd, tailpos);
#endif /* CONFIG_HS20 */

	tailpos = hostapd_eid_mbo(hapd, tailpos, tail + tail_len - tailpos);
	tailpos = hostapd_eid_owe_trans(hapd, tailpos,
					tail + tail_len - tailpos);

	if (hapd->conf->vendor_elements) {
		os_memcpy(tailpos, wpabuf_head(hapd->conf->vendor_elements),
			  wpabuf_len(hapd->conf->vendor_elements));
		tailpos += wpabuf_len(hapd->conf->vendor_elements);
	}

	tail_len = tailpos > tail ? tailpos - tail : 0;

	resp = hostapd_probe_resp_offloads(hapd, &resp_len);
#endif /* NEED_AP_MLME */

	os_memset(params, 0, sizeof(*params));
	params->head = (u8 *) head;
	params->head_len = head_len;
	params->tail = tail;
	params->tail_len = tail_len;
	params->proberesp = resp;
	params->proberesp_len = resp_len;
	params->dtim_period = hapd->conf->dtim_period;
	params->beacon_int = hapd->iconf->beacon_int;
	params->basic_rates = hapd->iface->basic_rates;
	params->beacon_rate = hapd->iconf->beacon_rate;
	params->rate_type = hapd->iconf->rate_type;
	params->ssid = hapd->conf->ssid.ssid;
	params->ssid_len = hapd->conf->ssid.ssid_len;
	if ((hapd->conf->wpa & (WPA_PROTO_WPA | WPA_PROTO_RSN)) ==
	    (WPA_PROTO_WPA | WPA_PROTO_RSN))
		params->pairwise_ciphers = hapd->conf->wpa_pairwise |
			hapd->conf->rsn_pairwise;
	else if (hapd->conf->wpa & WPA_PROTO_RSN)
		params->pairwise_ciphers = hapd->conf->rsn_pairwise;
	else if (hapd->conf->wpa & WPA_PROTO_WPA)
		params->pairwise_ciphers = hapd->conf->wpa_pairwise;
	params->group_cipher = hapd->conf->wpa_group;
	params->key_mgmt_suites = hapd->conf->wpa_key_mgmt;
	params->auth_algs = hapd->conf->auth_algs;
	params->wpa_version = hapd->conf->wpa;
	params->privacy = hapd->conf->ssid.wep.keys_set || hapd->conf->wpa ||
		(hapd->conf->ieee802_1x &&
		 (hapd->conf->default_wep_key_len ||
		  hapd->conf->individual_wep_key_len));
	switch (hapd->conf->ignore_broadcast_ssid) {
	case 0:
		params->hide_ssid = NO_SSID_HIDING;
		break;
	case 1:
		params->hide_ssid = HIDDEN_SSID_ZERO_LEN;
		break;
	case 2:
		params->hide_ssid = HIDDEN_SSID_ZERO_CONTENTS;
		break;
	}
	params->isolate = hapd->conf->isolate;
	params->smps_mode = hapd->iconf->ht_capab & HT_CAP_INFO_SMPS_MASK;
#ifdef NEED_AP_MLME
	params->cts_protect = !!(ieee802_11_erp_info(hapd) &
				ERP_INFO_USE_PROTECTION);
	params->preamble = hapd->iface->num_sta_no_short_preamble == 0 &&
		hapd->iconf->preamble == SHORT_PREAMBLE;
	if (hapd->iface->current_mode &&
	    hapd->iface->current_mode->mode == HOSTAPD_MODE_IEEE80211G)
		params->short_slot_time =
			hapd->iface->num_sta_no_short_slot_time > 0 ? 0 : 1;
	else
		params->short_slot_time = -1;
	if (!hapd->iconf->ieee80211n || hapd->conf->disable_11n)
		params->ht_opmode = -1;
	else
		params->ht_opmode = hapd->iface->ht_op_mode;
#endif /* NEED_AP_MLME */
	params->interworking = hapd->conf->interworking;
	if (hapd->conf->interworking &&
	    !is_zero_ether_addr(hapd->conf->hessid))
		params->hessid = hapd->conf->hessid;
	params->access_network_type = hapd->conf->access_network_type;
	params->ap_max_inactivity = hapd->conf->ap_max_inactivity;
#ifdef CONFIG_P2P
	params->p2p_go_ctwindow = hapd->iconf->p2p_go_ctwindow;
#endif /* CONFIG_P2P */
#ifdef CONFIG_HS20
	params->disable_dgaf = hapd->conf->disable_dgaf;
	if (hapd->conf->osen) {
		params->privacy = 1;
		params->osen = 1;
	}
#endif /* CONFIG_HS20 */
	params->multicast_to_unicast = hapd->conf->multicast_to_unicast;
	params->pbss = hapd->conf->pbss;

	if (hapd->conf->ftm_responder) {
		if (hapd->iface->drv_flags & WPA_DRIVER_FLAGS_FTM_RESPONDER) {
			params->ftm_responder = 1;
			params->lci = hapd->iface->conf->lci;
			params->civic = hapd->iface->conf->civic;
		} else {
			wpa_printf(MSG_WARNING,
				   "Not configuring FTM responder as the driver doesn't advertise support for it");
		}
	}

	return 0;
}