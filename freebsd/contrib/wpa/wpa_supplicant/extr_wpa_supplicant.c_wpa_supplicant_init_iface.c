#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct TYPE_6__ {size_t num_modes; TYPE_2__* modes; int /*<<< orphan*/  flags; } ;
struct wpa_supplicant {scalar_t__ hw_capab; int drv_capa_known; int drv_flags; int max_remain_on_chan; int* extended_capa; int extended_capa_len; int num_multichan_concurrent; int mac_addr_rand_supported; int multi_bss_support; char* imsi; int enable_oce; TYPE_3__* conf; int /*<<< orphan*/  mnc_len; int /*<<< orphan*/  eapol; int /*<<< orphan*/  mesh_external_pmksa_cache; int /*<<< orphan*/  global; scalar_t__ p2p_mgmt; int /*<<< orphan*/ * gas; int /*<<< orphan*/ * ctrl_iface; int /*<<< orphan*/  wpa; int /*<<< orphan*/  gas_server; scalar_t__* ifname; int /*<<< orphan*/  fst; int /*<<< orphan*/  own_addr; scalar_t__ sched_scan_supported; int /*<<< orphan*/  wmm_ac_supported; int /*<<< orphan*/  extended_capa_mask; int /*<<< orphan*/  max_stations; int /*<<< orphan*/  max_match_sets; int /*<<< orphan*/  max_sched_scan_plan_iterations; int /*<<< orphan*/  max_sched_scan_plan_interval; int /*<<< orphan*/  max_sched_scan_plans; int /*<<< orphan*/  max_sched_scan_ssids; int /*<<< orphan*/  max_scan_ssids; int /*<<< orphan*/  probe_resp_offloads; int /*<<< orphan*/  drv_rrm_flags; int /*<<< orphan*/  drv_smps_modes; int /*<<< orphan*/  drv_enc; TYPE_1__ hw; scalar_t__* bridge_ifname; int /*<<< orphan*/ * confanother; int /*<<< orphan*/ * confname; } ;
struct wpa_interface {char* ifname; char* confname; char* driver; char* ctrl_interface; char* bridge_ifname; char* confanother; char* driver_param; scalar_t__ p2p_mgmt; } ;
struct wpa_driver_capa {int flags; int max_remain_on_chan; int* extended_capa; int extended_capa_len; int num_multichan_concurrent; scalar_t__ mac_addr_rand_sched_scan_supported; scalar_t__ mac_addr_rand_scan_supported; int /*<<< orphan*/  wmm_ac_supported; int /*<<< orphan*/  extended_capa_mask; int /*<<< orphan*/  max_stations; int /*<<< orphan*/  max_match_sets; scalar_t__ sched_scan_supported; int /*<<< orphan*/  max_sched_scan_plan_iterations; int /*<<< orphan*/  max_sched_scan_plan_interval; int /*<<< orphan*/  max_sched_scan_plans; int /*<<< orphan*/  max_sched_scan_ssids; int /*<<< orphan*/  max_scan_ssids; int /*<<< orphan*/  probe_resp_offloads; int /*<<< orphan*/  rrm_flags; int /*<<< orphan*/  smps_modes; int /*<<< orphan*/  enc; } ;
struct fst_wpa_obj {int dummy; } ;
struct fst_iface_cfg {scalar_t__* group_id; int /*<<< orphan*/  llt; int /*<<< orphan*/  priority; } ;
struct TYPE_8__ {char* fst_group_id; int oce; int /*<<< orphan*/  non_pref_chan; int /*<<< orphan*/  sched_scan_plans; int /*<<< orphan*/ * ctrl_interface; int /*<<< orphan*/  fst_llt; int /*<<< orphan*/  fst_priority; scalar_t__* country; scalar_t__ dot11RSNAConfigSATimeout; scalar_t__ dot11RSNAConfigPMKReauthThreshold; scalar_t__ dot11RSNAConfigPMKLifetime; int /*<<< orphan*/  fast_reauth; int /*<<< orphan*/ * driver_param; } ;
struct TYPE_7__ {int ht_capab; scalar_t__ vht_capab; } ;

/* Variables and functions */
 scalar_t__ CAPAB_HT ; 
 scalar_t__ CAPAB_HT40 ; 
 scalar_t__ CAPAB_NO_HT_VHT ; 
 scalar_t__ CAPAB_VHT ; 
 int /*<<< orphan*/  FALSE ; 
 int HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET ; 
 int MAC_ADDR_RAND_PNO ; 
 int MAC_ADDR_RAND_SCAN ; 
 int MAC_ADDR_RAND_SCHED_SCAN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int OCE_STA ; 
 int OCE_STA_CFON ; 
 int /*<<< orphan*/  RSNA_PMK_LIFETIME ; 
 int /*<<< orphan*/  RSNA_PMK_REAUTH_THRESHOLD ; 
 int /*<<< orphan*/  RSNA_SA_TIMEOUT ; 
 int WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE ; 
 int WPA_DRIVER_FLAGS_OCE_STA ; 
 int WPA_DRIVER_FLAGS_OCE_STA_CFON ; 
 int /*<<< orphan*/  WPA_IF_STATION ; 
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eapol_sm_get_eap_proxy_imsi (int /*<<< orphan*/ ,int,char*,size_t*) ; 
 int /*<<< orphan*/  eapol_sm_notify_portEnabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_sm_notify_portValid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fst_attach (scalar_t__*,int /*<<< orphan*/ ,struct fst_wpa_obj*,struct fst_iface_cfg*) ; 
 int /*<<< orphan*/  fst_wpa_supplicant_fill_iface_obj (struct wpa_supplicant*,struct fst_wpa_obj*) ; 
 int /*<<< orphan*/ * gas_query_init (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  gas_server_init (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hs20_init (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 void* os_rel2abs_path (char*) ; 
 void* os_strdup (char*) ; 
 int /*<<< orphan*/  os_strlcpy (scalar_t__*,char*,int) ; 
 int os_strlen (char*) ; 
 scalar_t__ pcsc_reader_init (struct wpa_supplicant*) ; 
 scalar_t__ wpa_bss_init (struct wpa_supplicant*) ; 
 TYPE_3__* wpa_config_alloc_empty (char*,char*) ; 
 TYPE_3__* wpa_config_read (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int wpa_drv_get_capa (struct wpa_supplicant*,struct wpa_driver_capa*) ; 
 int /*<<< orphan*/  wpa_drv_get_ext_capa (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 TYPE_2__* wpa_drv_get_hw_feature_data (struct wpa_supplicant*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ wpa_drv_set_country (struct wpa_supplicant*,scalar_t__*) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_sm_set_eapol (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_sm_set_fast_reauth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_sm_set_ifname (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 scalar_t__ wpa_sm_set_param (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * wpa_supplicant_ctrl_iface_init (struct wpa_supplicant*) ; 
 scalar_t__ wpa_supplicant_driver_init (struct wpa_supplicant*) ; 
 scalar_t__ wpa_supplicant_init_eapol (struct wpa_supplicant*) ; 
 scalar_t__ wpa_supplicant_init_wpa (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_set_default_scan_ies (struct wpa_supplicant*) ; 
 scalar_t__ wpa_tdls_init (int /*<<< orphan*/ ) ; 
 scalar_t__ wpas_dpp_init (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_gas_server_tx ; 
 scalar_t__ wpas_init_driver (struct wpa_supplicant*,struct wpa_interface const*) ; 
 scalar_t__ wpas_init_ext_pw (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_mbo_update_non_pref_chan (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpas_p2p_init (int /*<<< orphan*/ ,struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_rrm_reset (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_sched_scan_plans_set (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpas_set_wowlan_triggers (struct wpa_supplicant*,struct wpa_driver_capa*) ; 
 scalar_t__ wpas_wps_init (struct wpa_supplicant*) ; 

__attribute__((used)) static int wpa_supplicant_init_iface(struct wpa_supplicant *wpa_s,
				     const struct wpa_interface *iface)
{
	struct wpa_driver_capa capa;
	int capa_res;
	u8 dfs_domain;

	wpa_printf(MSG_DEBUG, "Initializing interface '%s' conf '%s' driver "
		   "'%s' ctrl_interface '%s' bridge '%s'", iface->ifname,
		   iface->confname ? iface->confname : "N/A",
		   iface->driver ? iface->driver : "default",
		   iface->ctrl_interface ? iface->ctrl_interface : "N/A",
		   iface->bridge_ifname ? iface->bridge_ifname : "N/A");

	if (iface->confname) {
#ifdef CONFIG_BACKEND_FILE
		wpa_s->confname = os_rel2abs_path(iface->confname);
		if (wpa_s->confname == NULL) {
			wpa_printf(MSG_ERROR, "Failed to get absolute path "
				   "for configuration file '%s'.",
				   iface->confname);
			return -1;
		}
		wpa_printf(MSG_DEBUG, "Configuration file '%s' -> '%s'",
			   iface->confname, wpa_s->confname);
#else /* CONFIG_BACKEND_FILE */
		wpa_s->confname = os_strdup(iface->confname);
#endif /* CONFIG_BACKEND_FILE */
		wpa_s->conf = wpa_config_read(wpa_s->confname, NULL);
		if (wpa_s->conf == NULL) {
			wpa_printf(MSG_ERROR, "Failed to read or parse "
				   "configuration '%s'.", wpa_s->confname);
			return -1;
		}
		wpa_s->confanother = os_rel2abs_path(iface->confanother);
		if (wpa_s->confanother &&
		    !wpa_config_read(wpa_s->confanother, wpa_s->conf)) {
			wpa_printf(MSG_ERROR,
				   "Failed to read or parse configuration '%s'.",
				   wpa_s->confanother);
			return -1;
		}

		/*
		 * Override ctrl_interface and driver_param if set on command
		 * line.
		 */
		if (iface->ctrl_interface) {
			os_free(wpa_s->conf->ctrl_interface);
			wpa_s->conf->ctrl_interface =
				os_strdup(iface->ctrl_interface);
		}

		if (iface->driver_param) {
			os_free(wpa_s->conf->driver_param);
			wpa_s->conf->driver_param =
				os_strdup(iface->driver_param);
		}

		if (iface->p2p_mgmt && !iface->ctrl_interface) {
			os_free(wpa_s->conf->ctrl_interface);
			wpa_s->conf->ctrl_interface = NULL;
		}
	} else
		wpa_s->conf = wpa_config_alloc_empty(iface->ctrl_interface,
						     iface->driver_param);

	if (wpa_s->conf == NULL) {
		wpa_printf(MSG_ERROR, "\nNo configuration found.");
		return -1;
	}

	if (iface->ifname == NULL) {
		wpa_printf(MSG_ERROR, "\nInterface name is required.");
		return -1;
	}
	if (os_strlen(iface->ifname) >= sizeof(wpa_s->ifname)) {
		wpa_printf(MSG_ERROR, "\nToo long interface name '%s'.",
			   iface->ifname);
		return -1;
	}
	os_strlcpy(wpa_s->ifname, iface->ifname, sizeof(wpa_s->ifname));

	if (iface->bridge_ifname) {
		if (os_strlen(iface->bridge_ifname) >=
		    sizeof(wpa_s->bridge_ifname)) {
			wpa_printf(MSG_ERROR, "\nToo long bridge interface "
				   "name '%s'.", iface->bridge_ifname);
			return -1;
		}
		os_strlcpy(wpa_s->bridge_ifname, iface->bridge_ifname,
			   sizeof(wpa_s->bridge_ifname));
	}

	/* RSNA Supplicant Key Management - INITIALIZE */
	eapol_sm_notify_portEnabled(wpa_s->eapol, FALSE);
	eapol_sm_notify_portValid(wpa_s->eapol, FALSE);

	/* Initialize driver interface and register driver event handler before
	 * L2 receive handler so that association events are processed before
	 * EAPOL-Key packets if both become available for the same select()
	 * call. */
	if (wpas_init_driver(wpa_s, iface) < 0)
		return -1;

	if (wpa_supplicant_init_wpa(wpa_s) < 0)
		return -1;

	wpa_sm_set_ifname(wpa_s->wpa, wpa_s->ifname,
			  wpa_s->bridge_ifname[0] ? wpa_s->bridge_ifname :
			  NULL);
	wpa_sm_set_fast_reauth(wpa_s->wpa, wpa_s->conf->fast_reauth);

	if (wpa_s->conf->dot11RSNAConfigPMKLifetime &&
	    wpa_sm_set_param(wpa_s->wpa, RSNA_PMK_LIFETIME,
			     wpa_s->conf->dot11RSNAConfigPMKLifetime)) {
		wpa_msg(wpa_s, MSG_ERROR, "Invalid WPA parameter value for "
			"dot11RSNAConfigPMKLifetime");
		return -1;
	}

	if (wpa_s->conf->dot11RSNAConfigPMKReauthThreshold &&
	    wpa_sm_set_param(wpa_s->wpa, RSNA_PMK_REAUTH_THRESHOLD,
			     wpa_s->conf->dot11RSNAConfigPMKReauthThreshold)) {
		wpa_msg(wpa_s, MSG_ERROR, "Invalid WPA parameter value for "
			"dot11RSNAConfigPMKReauthThreshold");
		return -1;
	}

	if (wpa_s->conf->dot11RSNAConfigSATimeout &&
	    wpa_sm_set_param(wpa_s->wpa, RSNA_SA_TIMEOUT,
			     wpa_s->conf->dot11RSNAConfigSATimeout)) {
		wpa_msg(wpa_s, MSG_ERROR, "Invalid WPA parameter value for "
			"dot11RSNAConfigSATimeout");
		return -1;
	}

	wpa_s->hw.modes = wpa_drv_get_hw_feature_data(wpa_s,
						      &wpa_s->hw.num_modes,
						      &wpa_s->hw.flags,
						      &dfs_domain);
	if (wpa_s->hw.modes) {
		u16 i;

		for (i = 0; i < wpa_s->hw.num_modes; i++) {
			if (wpa_s->hw.modes[i].vht_capab) {
				wpa_s->hw_capab = CAPAB_VHT;
				break;
			}

			if (wpa_s->hw.modes[i].ht_capab &
			    HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET)
				wpa_s->hw_capab = CAPAB_HT40;
			else if (wpa_s->hw.modes[i].ht_capab &&
				 wpa_s->hw_capab == CAPAB_NO_HT_VHT)
				wpa_s->hw_capab = CAPAB_HT;
		}
	}

	capa_res = wpa_drv_get_capa(wpa_s, &capa);
	if (capa_res == 0) {
		wpa_s->drv_capa_known = 1;
		wpa_s->drv_flags = capa.flags;
		wpa_s->drv_enc = capa.enc;
		wpa_s->drv_smps_modes = capa.smps_modes;
		wpa_s->drv_rrm_flags = capa.rrm_flags;
		wpa_s->probe_resp_offloads = capa.probe_resp_offloads;
		wpa_s->max_scan_ssids = capa.max_scan_ssids;
		wpa_s->max_sched_scan_ssids = capa.max_sched_scan_ssids;
		wpa_s->max_sched_scan_plans = capa.max_sched_scan_plans;
		wpa_s->max_sched_scan_plan_interval =
			capa.max_sched_scan_plan_interval;
		wpa_s->max_sched_scan_plan_iterations =
			capa.max_sched_scan_plan_iterations;
		wpa_s->sched_scan_supported = capa.sched_scan_supported;
		wpa_s->max_match_sets = capa.max_match_sets;
		wpa_s->max_remain_on_chan = capa.max_remain_on_chan;
		wpa_s->max_stations = capa.max_stations;
		wpa_s->extended_capa = capa.extended_capa;
		wpa_s->extended_capa_mask = capa.extended_capa_mask;
		wpa_s->extended_capa_len = capa.extended_capa_len;
		wpa_s->num_multichan_concurrent =
			capa.num_multichan_concurrent;
		wpa_s->wmm_ac_supported = capa.wmm_ac_supported;

		if (capa.mac_addr_rand_scan_supported)
			wpa_s->mac_addr_rand_supported |= MAC_ADDR_RAND_SCAN;
		if (wpa_s->sched_scan_supported &&
		    capa.mac_addr_rand_sched_scan_supported)
			wpa_s->mac_addr_rand_supported |=
				(MAC_ADDR_RAND_SCHED_SCAN | MAC_ADDR_RAND_PNO);

		wpa_drv_get_ext_capa(wpa_s, WPA_IF_STATION);
		if (wpa_s->extended_capa &&
		    wpa_s->extended_capa_len >= 3 &&
		    wpa_s->extended_capa[2] & 0x40)
			wpa_s->multi_bss_support = 1;
	}
	if (wpa_s->max_remain_on_chan == 0)
		wpa_s->max_remain_on_chan = 1000;

	/*
	 * Only take p2p_mgmt parameters when P2P Device is supported.
	 * Doing it here as it determines whether l2_packet_init() will be done
	 * during wpa_supplicant_driver_init().
	 */
	if (wpa_s->drv_flags & WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE)
		wpa_s->p2p_mgmt = iface->p2p_mgmt;

	if (wpa_s->num_multichan_concurrent == 0)
		wpa_s->num_multichan_concurrent = 1;

	if (wpa_supplicant_driver_init(wpa_s) < 0)
		return -1;

#ifdef CONFIG_TDLS
	if (!iface->p2p_mgmt && wpa_tdls_init(wpa_s->wpa))
		return -1;
#endif /* CONFIG_TDLS */

	if (wpa_s->conf->country[0] && wpa_s->conf->country[1] &&
	    wpa_drv_set_country(wpa_s, wpa_s->conf->country)) {
		wpa_dbg(wpa_s, MSG_DEBUG, "Failed to set country");
		return -1;
	}

#ifdef CONFIG_FST
	if (wpa_s->conf->fst_group_id) {
		struct fst_iface_cfg cfg;
		struct fst_wpa_obj iface_obj;

		fst_wpa_supplicant_fill_iface_obj(wpa_s, &iface_obj);
		os_strlcpy(cfg.group_id, wpa_s->conf->fst_group_id,
			   sizeof(cfg.group_id));
		cfg.priority = wpa_s->conf->fst_priority;
		cfg.llt = wpa_s->conf->fst_llt;

		wpa_s->fst = fst_attach(wpa_s->ifname, wpa_s->own_addr,
					&iface_obj, &cfg);
		if (!wpa_s->fst) {
			wpa_msg(wpa_s, MSG_ERROR,
				"FST: Cannot attach iface %s to group %s",
				wpa_s->ifname, cfg.group_id);
			return -1;
		}
	}
#endif /* CONFIG_FST */

	if (wpas_wps_init(wpa_s))
		return -1;

#ifdef CONFIG_GAS_SERVER
	wpa_s->gas_server = gas_server_init(wpa_s, wpas_gas_server_tx);
	if (!wpa_s->gas_server) {
		wpa_printf(MSG_ERROR, "Failed to initialize GAS server");
		return -1;
	}
#endif /* CONFIG_GAS_SERVER */

#ifdef CONFIG_DPP
	if (wpas_dpp_init(wpa_s) < 0)
		return -1;
#endif /* CONFIG_DPP */

	if (wpa_supplicant_init_eapol(wpa_s) < 0)
		return -1;
	wpa_sm_set_eapol(wpa_s->wpa, wpa_s->eapol);

	wpa_s->ctrl_iface = wpa_supplicant_ctrl_iface_init(wpa_s);
	if (wpa_s->ctrl_iface == NULL) {
		wpa_printf(MSG_ERROR,
			   "Failed to initialize control interface '%s'.\n"
			   "You may have another wpa_supplicant process "
			   "already running or the file was\n"
			   "left by an unclean termination of wpa_supplicant "
			   "in which case you will need\n"
			   "to manually remove this file before starting "
			   "wpa_supplicant again.\n",
			   wpa_s->conf->ctrl_interface);
		return -1;
	}

	wpa_s->gas = gas_query_init(wpa_s);
	if (wpa_s->gas == NULL) {
		wpa_printf(MSG_ERROR, "Failed to initialize GAS query");
		return -1;
	}

	if ((!(wpa_s->drv_flags & WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE) ||
	     wpa_s->p2p_mgmt) &&
	    wpas_p2p_init(wpa_s->global, wpa_s) < 0) {
		wpa_msg(wpa_s, MSG_ERROR, "Failed to init P2P");
		return -1;
	}

	if (wpa_bss_init(wpa_s) < 0)
		return -1;

#ifdef CONFIG_PMKSA_CACHE_EXTERNAL
#ifdef CONFIG_MESH
	dl_list_init(&wpa_s->mesh_external_pmksa_cache);
#endif /* CONFIG_MESH */
#endif /* CONFIG_PMKSA_CACHE_EXTERNAL */

	/*
	 * Set Wake-on-WLAN triggers, if configured.
	 * Note: We don't restore/remove the triggers on shutdown (it doesn't
	 * have effect anyway when the interface is down).
	 */
	if (capa_res == 0 && wpas_set_wowlan_triggers(wpa_s, &capa) < 0)
		return -1;

#ifdef CONFIG_EAP_PROXY
{
	size_t len;
	wpa_s->mnc_len = eapol_sm_get_eap_proxy_imsi(wpa_s->eapol, -1,
						     wpa_s->imsi, &len);
	if (wpa_s->mnc_len > 0) {
		wpa_s->imsi[len] = '\0';
		wpa_printf(MSG_DEBUG, "eap_proxy: IMSI %s (MNC length %d)",
			   wpa_s->imsi, wpa_s->mnc_len);
	} else {
		wpa_printf(MSG_DEBUG, "eap_proxy: IMSI not available");
	}
}
#endif /* CONFIG_EAP_PROXY */

	if (pcsc_reader_init(wpa_s) < 0)
		return -1;

	if (wpas_init_ext_pw(wpa_s) < 0)
		return -1;

	wpas_rrm_reset(wpa_s);

	wpas_sched_scan_plans_set(wpa_s, wpa_s->conf->sched_scan_plans);

#ifdef CONFIG_HS20
	hs20_init(wpa_s);
#endif /* CONFIG_HS20 */
#ifdef CONFIG_MBO
	if (wpa_s->conf->oce) {
		if ((wpa_s->conf->oce & OCE_STA) &&
		    (wpa_s->drv_flags & WPA_DRIVER_FLAGS_OCE_STA))
			wpa_s->enable_oce = OCE_STA;
		if ((wpa_s->conf->oce & OCE_STA_CFON) &&
		    (wpa_s->drv_flags & WPA_DRIVER_FLAGS_OCE_STA_CFON)) {
			/* TODO: Need to add STA-CFON support */
			wpa_printf(MSG_ERROR,
				   "OCE STA-CFON feature is not yet supported");
		}
	}
	wpas_mbo_update_non_pref_chan(wpa_s, wpa_s->conf->non_pref_chan);
#endif /* CONFIG_MBO */

	wpa_supplicant_set_default_scan_ies(wpa_s);

	return 0;
}