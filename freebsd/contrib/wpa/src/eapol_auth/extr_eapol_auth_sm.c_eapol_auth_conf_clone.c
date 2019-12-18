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
struct eapol_auth_config {int eap_req_id_text_len; int eap_fast_a_id_len; int /*<<< orphan*/  tls_flags; int /*<<< orphan*/  tls_session_lifetime; int /*<<< orphan*/  erp; int /*<<< orphan*/  erp_send_reauth_start; int /*<<< orphan*/ * erp_domain; int /*<<< orphan*/  fragment_size; int /*<<< orphan*/  wps; int /*<<< orphan*/  tnc; int /*<<< orphan*/  eap_sim_id; int /*<<< orphan*/  eap_sim_aka_result_ind; int /*<<< orphan*/  eap_teap_pac_no_inner; int /*<<< orphan*/  eap_teap_auth; int /*<<< orphan*/  pac_key_refresh_time; int /*<<< orphan*/  pac_key_lifetime; int /*<<< orphan*/  eap_fast_prov; int /*<<< orphan*/ * eap_fast_a_id_info; int /*<<< orphan*/ * eap_fast_a_id; int /*<<< orphan*/ * pac_opaque_encr_key; int /*<<< orphan*/ * eap_req_id_text; int /*<<< orphan*/  server_id_len; int /*<<< orphan*/  server_id; int /*<<< orphan*/  pbc_in_m1; int /*<<< orphan*/  pwd_group; int /*<<< orphan*/  eap_sim_db_priv; int /*<<< orphan*/  msg_ctx; int /*<<< orphan*/  ssl_ctx; int /*<<< orphan*/  eap_server; int /*<<< orphan*/  individual_wep_key_len; int /*<<< orphan*/  wpa; int /*<<< orphan*/  eap_reauth_period; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  eapol_auth_conf_free (struct eapol_auth_config*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 void* os_memdup (int /*<<< orphan*/ *,int) ; 
 void* os_strdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eapol_auth_conf_clone(struct eapol_auth_config *dst,
				 struct eapol_auth_config *src)
{
	dst->ctx = src->ctx;
	dst->eap_reauth_period = src->eap_reauth_period;
	dst->wpa = src->wpa;
	dst->individual_wep_key_len = src->individual_wep_key_len;
	dst->eap_server = src->eap_server;
	dst->ssl_ctx = src->ssl_ctx;
	dst->msg_ctx = src->msg_ctx;
	dst->eap_sim_db_priv = src->eap_sim_db_priv;
	os_free(dst->eap_req_id_text);
	dst->pwd_group = src->pwd_group;
	dst->pbc_in_m1 = src->pbc_in_m1;
	dst->server_id = src->server_id;
	dst->server_id_len = src->server_id_len;
	if (src->eap_req_id_text) {
		dst->eap_req_id_text = os_memdup(src->eap_req_id_text,
						 src->eap_req_id_text_len);
		if (dst->eap_req_id_text == NULL)
			return -1;
		dst->eap_req_id_text_len = src->eap_req_id_text_len;
	} else {
		dst->eap_req_id_text = NULL;
		dst->eap_req_id_text_len = 0;
	}
	if (src->pac_opaque_encr_key) {
		dst->pac_opaque_encr_key = os_memdup(src->pac_opaque_encr_key,
						     16);
		if (dst->pac_opaque_encr_key == NULL)
			goto fail;
	} else
		dst->pac_opaque_encr_key = NULL;
	if (src->eap_fast_a_id) {
		dst->eap_fast_a_id = os_memdup(src->eap_fast_a_id,
					       src->eap_fast_a_id_len);
		if (dst->eap_fast_a_id == NULL)
			goto fail;
		dst->eap_fast_a_id_len = src->eap_fast_a_id_len;
	} else
		dst->eap_fast_a_id = NULL;
	if (src->eap_fast_a_id_info) {
		dst->eap_fast_a_id_info = os_strdup(src->eap_fast_a_id_info);
		if (dst->eap_fast_a_id_info == NULL)
			goto fail;
	} else
		dst->eap_fast_a_id_info = NULL;
	dst->eap_fast_prov = src->eap_fast_prov;
	dst->pac_key_lifetime = src->pac_key_lifetime;
	dst->pac_key_refresh_time = src->pac_key_refresh_time;
	dst->eap_teap_auth = src->eap_teap_auth;
	dst->eap_teap_pac_no_inner = src->eap_teap_pac_no_inner;
	dst->eap_sim_aka_result_ind = src->eap_sim_aka_result_ind;
	dst->eap_sim_id = src->eap_sim_id;
	dst->tnc = src->tnc;
	dst->wps = src->wps;
	dst->fragment_size = src->fragment_size;

	os_free(dst->erp_domain);
	if (src->erp_domain) {
		dst->erp_domain = os_strdup(src->erp_domain);
		if (dst->erp_domain == NULL)
			goto fail;
	} else {
		dst->erp_domain = NULL;
	}
	dst->erp_send_reauth_start = src->erp_send_reauth_start;
	dst->erp = src->erp;
	dst->tls_session_lifetime = src->tls_session_lifetime;
	dst->tls_flags = src->tls_flags;

	return 0;

fail:
	eapol_auth_conf_free(dst);
	return -1;
}