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
struct eapol_state_machine {int radius_identifier; int flags; scalar_t__ reAuthPeriod; int /*<<< orphan*/  acct_multi_session_id; int /*<<< orphan*/  radius_cui; int /*<<< orphan*/  identity_len; int /*<<< orphan*/ * identity; int /*<<< orphan*/ * eap; int /*<<< orphan*/  eap_if; void* portValid; void* keyTxEnabled; int /*<<< orphan*/  portControl; int /*<<< orphan*/  ctrl_dir_state; int /*<<< orphan*/  key_rx_state; int /*<<< orphan*/  auth_key_tx_state; void* reAuthEnabled; int /*<<< orphan*/  reauth_timer_state; int /*<<< orphan*/  serverTimeout; int /*<<< orphan*/  be_auth_state; int /*<<< orphan*/  reAuthMax; int /*<<< orphan*/  quietPeriod; int /*<<< orphan*/  auth_pae_state; void* sta; struct eapol_authenticator* eapol; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {scalar_t__ eap_reauth_period; scalar_t__ individual_wep_key_len; int /*<<< orphan*/  tls_flags; int /*<<< orphan*/  tls_session_lifetime; int /*<<< orphan*/  erp; int /*<<< orphan*/  server_id_len; int /*<<< orphan*/  server_id; int /*<<< orphan*/  pbc_in_m1; int /*<<< orphan*/  pwd_group; int /*<<< orphan*/  fragment_size; int /*<<< orphan*/  wps; int /*<<< orphan*/  tnc; int /*<<< orphan*/  eap_sim_id; int /*<<< orphan*/  eap_sim_aka_result_ind; int /*<<< orphan*/  eap_teap_pac_no_inner; int /*<<< orphan*/  eap_teap_auth; int /*<<< orphan*/  pac_key_refresh_time; int /*<<< orphan*/  pac_key_lifetime; int /*<<< orphan*/  eap_fast_prov; int /*<<< orphan*/  eap_fast_a_id_info; int /*<<< orphan*/  eap_fast_a_id_len; int /*<<< orphan*/  eap_fast_a_id; int /*<<< orphan*/  pac_opaque_encr_key; int /*<<< orphan*/  eap_sim_db_priv; int /*<<< orphan*/  msg_ctx; int /*<<< orphan*/  ssl_ctx; int /*<<< orphan*/  eap_server; scalar_t__ wpa; } ;
struct eapol_authenticator {TYPE_1__ conf; scalar_t__ default_wep_key; } ;
struct eap_config {int /*<<< orphan*/  tls_flags; int /*<<< orphan*/  tls_session_lifetime; int /*<<< orphan*/  erp; int /*<<< orphan*/  server_id_len; int /*<<< orphan*/  server_id; int /*<<< orphan*/  pbc_in_m1; int /*<<< orphan*/  pwd_group; int /*<<< orphan*/  fragment_size; int /*<<< orphan*/  const* peer_addr; struct wpabuf const* assoc_p2p_ie; struct wpabuf const* assoc_wps_ie; int /*<<< orphan*/  wps; int /*<<< orphan*/  tnc; int /*<<< orphan*/  eap_sim_id; int /*<<< orphan*/  eap_sim_aka_result_ind; int /*<<< orphan*/  eap_teap_pac_no_inner; int /*<<< orphan*/  eap_teap_auth; int /*<<< orphan*/  pac_key_refresh_time; int /*<<< orphan*/  pac_key_lifetime; int /*<<< orphan*/  eap_fast_prov; int /*<<< orphan*/  eap_fast_a_id_info; int /*<<< orphan*/  eap_fast_a_id_len; int /*<<< orphan*/  eap_fast_a_id; int /*<<< orphan*/  pac_opaque_encr_key; int /*<<< orphan*/  eap_sim_db_priv; int /*<<< orphan*/  msg_ctx; int /*<<< orphan*/  ssl_ctx; int /*<<< orphan*/  eap_server; } ;
typedef  int /*<<< orphan*/  eap_conf ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_KEY_TX_NO_KEY_TRANSMIT ; 
 int /*<<< orphan*/  AUTH_PAE_DEFAULT_quietPeriod ; 
 int /*<<< orphan*/  AUTH_PAE_DEFAULT_reAuthMax ; 
 int /*<<< orphan*/  AUTH_PAE_INITIALIZE ; 
 int /*<<< orphan*/  Auto ; 
 int /*<<< orphan*/  BE_AUTH_DEFAULT_serverTimeout ; 
 int /*<<< orphan*/  BE_AUTH_INITIALIZE ; 
 int /*<<< orphan*/  CTRL_DIR_IN_OR_BOTH ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 void* FALSE ; 
 int /*<<< orphan*/  KEY_RX_NO_KEY_RECEIVE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  REAUTH_TIMER_INITIALIZE ; 
 void* TRUE ; 
 int /*<<< orphan*/  eap_get_interface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * eap_server_sm_init (struct eapol_state_machine*,int /*<<< orphan*/ *,struct eap_config*) ; 
 int /*<<< orphan*/  eapol_auth_free (struct eapol_state_machine*) ; 
 int /*<<< orphan*/  eapol_auth_initialize (struct eapol_state_machine*) ; 
 int /*<<< orphan*/  eapol_cb ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct eap_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_strdup (char const*) ; 
 int /*<<< orphan*/  os_strlen (char const*) ; 
 struct eapol_state_machine* os_zalloc (int) ; 
 scalar_t__ radius_gen_session_id (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_alloc_copy (char const*,int /*<<< orphan*/ ) ; 

struct eapol_state_machine *
eapol_auth_alloc(struct eapol_authenticator *eapol, const u8 *addr,
		 int flags, const struct wpabuf *assoc_wps_ie,
		 const struct wpabuf *assoc_p2p_ie, void *sta_ctx,
		 const char *identity, const char *radius_cui)
{
	struct eapol_state_machine *sm;
	struct eap_config eap_conf;

	if (eapol == NULL)
		return NULL;

	sm = os_zalloc(sizeof(*sm));
	if (sm == NULL) {
		wpa_printf(MSG_DEBUG, "IEEE 802.1X state machine allocation "
			   "failed");
		return NULL;
	}
	sm->radius_identifier = -1;
	os_memcpy(sm->addr, addr, ETH_ALEN);
	sm->flags = flags;

	sm->eapol = eapol;
	sm->sta = sta_ctx;

	/* Set default values for state machine constants */
	sm->auth_pae_state = AUTH_PAE_INITIALIZE;
	sm->quietPeriod = AUTH_PAE_DEFAULT_quietPeriod;
	sm->reAuthMax = AUTH_PAE_DEFAULT_reAuthMax;

	sm->be_auth_state = BE_AUTH_INITIALIZE;
	sm->serverTimeout = BE_AUTH_DEFAULT_serverTimeout;

	sm->reauth_timer_state = REAUTH_TIMER_INITIALIZE;
	sm->reAuthPeriod = eapol->conf.eap_reauth_period;
	sm->reAuthEnabled = eapol->conf.eap_reauth_period > 0 ? TRUE : FALSE;

	sm->auth_key_tx_state = AUTH_KEY_TX_NO_KEY_TRANSMIT;

	sm->key_rx_state = KEY_RX_NO_KEY_RECEIVE;

	sm->ctrl_dir_state = CTRL_DIR_IN_OR_BOTH;

	sm->portControl = Auto;

	if (!eapol->conf.wpa &&
	    (eapol->default_wep_key || eapol->conf.individual_wep_key_len > 0))
		sm->keyTxEnabled = TRUE;
	else
		sm->keyTxEnabled = FALSE;
	if (eapol->conf.wpa)
		sm->portValid = FALSE;
	else
		sm->portValid = TRUE;

	os_memset(&eap_conf, 0, sizeof(eap_conf));
	eap_conf.eap_server = eapol->conf.eap_server;
	eap_conf.ssl_ctx = eapol->conf.ssl_ctx;
	eap_conf.msg_ctx = eapol->conf.msg_ctx;
	eap_conf.eap_sim_db_priv = eapol->conf.eap_sim_db_priv;
	eap_conf.pac_opaque_encr_key = eapol->conf.pac_opaque_encr_key;
	eap_conf.eap_fast_a_id = eapol->conf.eap_fast_a_id;
	eap_conf.eap_fast_a_id_len = eapol->conf.eap_fast_a_id_len;
	eap_conf.eap_fast_a_id_info = eapol->conf.eap_fast_a_id_info;
	eap_conf.eap_fast_prov = eapol->conf.eap_fast_prov;
	eap_conf.pac_key_lifetime = eapol->conf.pac_key_lifetime;
	eap_conf.pac_key_refresh_time = eapol->conf.pac_key_refresh_time;
	eap_conf.eap_teap_auth = eapol->conf.eap_teap_auth;
	eap_conf.eap_teap_pac_no_inner = eapol->conf.eap_teap_pac_no_inner;
	eap_conf.eap_sim_aka_result_ind = eapol->conf.eap_sim_aka_result_ind;
	eap_conf.eap_sim_id = eapol->conf.eap_sim_id;
	eap_conf.tnc = eapol->conf.tnc;
	eap_conf.wps = eapol->conf.wps;
	eap_conf.assoc_wps_ie = assoc_wps_ie;
	eap_conf.assoc_p2p_ie = assoc_p2p_ie;
	eap_conf.peer_addr = addr;
	eap_conf.fragment_size = eapol->conf.fragment_size;
	eap_conf.pwd_group = eapol->conf.pwd_group;
	eap_conf.pbc_in_m1 = eapol->conf.pbc_in_m1;
	eap_conf.server_id = eapol->conf.server_id;
	eap_conf.server_id_len = eapol->conf.server_id_len;
	eap_conf.erp = eapol->conf.erp;
	eap_conf.tls_session_lifetime = eapol->conf.tls_session_lifetime;
	eap_conf.tls_flags = eapol->conf.tls_flags;
	sm->eap = eap_server_sm_init(sm, &eapol_cb, &eap_conf);
	if (sm->eap == NULL) {
		eapol_auth_free(sm);
		return NULL;
	}
	sm->eap_if = eap_get_interface(sm->eap);

	eapol_auth_initialize(sm);

	if (identity) {
		sm->identity = (u8 *) os_strdup(identity);
		if (sm->identity)
			sm->identity_len = os_strlen(identity);
	}
	if (radius_cui)
		sm->radius_cui = wpabuf_alloc_copy(radius_cui,
						   os_strlen(radius_cui));

#ifndef CONFIG_NO_RADIUS
	if (radius_gen_session_id((u8 *) &sm->acct_multi_session_id,
				  sizeof(sm->acct_multi_session_id)) < 0) {
		eapol_auth_free(sm);
		return NULL;
	}
#endif /* CONFIG_NO_RADIUS */

	return sm;
}