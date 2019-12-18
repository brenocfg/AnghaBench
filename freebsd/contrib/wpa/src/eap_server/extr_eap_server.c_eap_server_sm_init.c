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
struct eapol_callbacks {int dummy; } ;
struct eap_sm {int MaxRetrans; int eap_fast_a_id_len; int /*<<< orphan*/  tls_test_flags; int /*<<< orphan*/  tls_flags; int /*<<< orphan*/  tls_session_lifetime; int /*<<< orphan*/  erp; int /*<<< orphan*/  server_id_len; int /*<<< orphan*/  server_id; int /*<<< orphan*/  pbc_in_m1; int /*<<< orphan*/  pwd_group; int /*<<< orphan*/  fragment_size; void* peer_addr; void* assoc_p2p_ie; void* assoc_wps_ie; int /*<<< orphan*/  wps; int /*<<< orphan*/  tnc; int /*<<< orphan*/  eap_sim_id; int /*<<< orphan*/  eap_sim_aka_result_ind; int /*<<< orphan*/  eap_teap_pac_no_inner; int /*<<< orphan*/  eap_teap_auth; int /*<<< orphan*/  pac_key_refresh_time; int /*<<< orphan*/  pac_key_lifetime; int /*<<< orphan*/  eap_fast_prov; int /*<<< orphan*/  eap_fast_a_id_info; void* eap_fast_a_id; void* pac_opaque_encr_key; int /*<<< orphan*/  eap_server; int /*<<< orphan*/  backend_auth; int /*<<< orphan*/  eap_sim_db_priv; int /*<<< orphan*/  msg_ctx; int /*<<< orphan*/  ssl_ctx; struct eapol_callbacks const* eapol_cb; void* eapol_ctx; } ;
struct eap_config {int eap_fast_a_id_len; int /*<<< orphan*/  tls_test_flags; int /*<<< orphan*/  tls_flags; int /*<<< orphan*/  tls_session_lifetime; int /*<<< orphan*/  erp; int /*<<< orphan*/  server_id_len; int /*<<< orphan*/  server_id; int /*<<< orphan*/  pbc_in_m1; int /*<<< orphan*/  pwd_group; int /*<<< orphan*/  fragment_size; int /*<<< orphan*/  peer_addr; scalar_t__ assoc_p2p_ie; scalar_t__ assoc_wps_ie; int /*<<< orphan*/  wps; int /*<<< orphan*/  tnc; int /*<<< orphan*/  eap_sim_id; int /*<<< orphan*/  eap_sim_aka_result_ind; int /*<<< orphan*/  eap_teap_pac_no_inner; int /*<<< orphan*/  eap_teap_auth; int /*<<< orphan*/  pac_key_refresh_time; int /*<<< orphan*/  pac_key_lifetime; int /*<<< orphan*/  eap_fast_prov; scalar_t__ eap_fast_a_id_info; int /*<<< orphan*/  eap_fast_a_id; int /*<<< orphan*/  pac_opaque_encr_key; int /*<<< orphan*/  eap_server; int /*<<< orphan*/  backend_auth; int /*<<< orphan*/  eap_sim_db_priv; int /*<<< orphan*/  msg_ctx; int /*<<< orphan*/  ssl_ctx; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 void* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_strdup (scalar_t__) ; 
 struct eap_sm* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 void* wpabuf_dup (scalar_t__) ; 

struct eap_sm * eap_server_sm_init(void *eapol_ctx,
				   const struct eapol_callbacks *eapol_cb,
				   struct eap_config *conf)
{
	struct eap_sm *sm;

	sm = os_zalloc(sizeof(*sm));
	if (sm == NULL)
		return NULL;
	sm->eapol_ctx = eapol_ctx;
	sm->eapol_cb = eapol_cb;
	sm->MaxRetrans = 5; /* RFC 3748: max 3-5 retransmissions suggested */
	sm->ssl_ctx = conf->ssl_ctx;
	sm->msg_ctx = conf->msg_ctx;
	sm->eap_sim_db_priv = conf->eap_sim_db_priv;
	sm->backend_auth = conf->backend_auth;
	sm->eap_server = conf->eap_server;
	if (conf->pac_opaque_encr_key) {
		sm->pac_opaque_encr_key = os_malloc(16);
		if (sm->pac_opaque_encr_key) {
			os_memcpy(sm->pac_opaque_encr_key,
				  conf->pac_opaque_encr_key, 16);
		}
	}
	if (conf->eap_fast_a_id) {
		sm->eap_fast_a_id = os_malloc(conf->eap_fast_a_id_len);
		if (sm->eap_fast_a_id) {
			os_memcpy(sm->eap_fast_a_id, conf->eap_fast_a_id,
				  conf->eap_fast_a_id_len);
			sm->eap_fast_a_id_len = conf->eap_fast_a_id_len;
		}
	}
	if (conf->eap_fast_a_id_info)
		sm->eap_fast_a_id_info = os_strdup(conf->eap_fast_a_id_info);
	sm->eap_fast_prov = conf->eap_fast_prov;
	sm->pac_key_lifetime = conf->pac_key_lifetime;
	sm->pac_key_refresh_time = conf->pac_key_refresh_time;
	sm->eap_teap_auth = conf->eap_teap_auth;
	sm->eap_teap_pac_no_inner = conf->eap_teap_pac_no_inner;
	sm->eap_sim_aka_result_ind = conf->eap_sim_aka_result_ind;
	sm->eap_sim_id = conf->eap_sim_id;
	sm->tnc = conf->tnc;
	sm->wps = conf->wps;
	if (conf->assoc_wps_ie)
		sm->assoc_wps_ie = wpabuf_dup(conf->assoc_wps_ie);
	if (conf->assoc_p2p_ie)
		sm->assoc_p2p_ie = wpabuf_dup(conf->assoc_p2p_ie);
	if (conf->peer_addr)
		os_memcpy(sm->peer_addr, conf->peer_addr, ETH_ALEN);
	sm->fragment_size = conf->fragment_size;
	sm->pwd_group = conf->pwd_group;
	sm->pbc_in_m1 = conf->pbc_in_m1;
	sm->server_id = conf->server_id;
	sm->server_id_len = conf->server_id_len;
	sm->erp = conf->erp;
	sm->tls_session_lifetime = conf->tls_session_lifetime;
	sm->tls_flags = conf->tls_flags;

#ifdef CONFIG_TESTING_OPTIONS
	sm->tls_test_flags = conf->tls_test_flags;
#endif /* CONFIG_TESTING_OPTIONS */

	wpa_printf(MSG_DEBUG, "EAP: Server state machine created");

	return sm;
}