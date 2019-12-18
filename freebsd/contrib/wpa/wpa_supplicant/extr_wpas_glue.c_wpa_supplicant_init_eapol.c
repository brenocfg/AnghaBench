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
struct wpa_supplicant {int /*<<< orphan*/ * eapol; TYPE_1__* conf; int /*<<< orphan*/  wps; } ;
struct eapol_ctx {struct wpa_supplicant* cb_ctx; int /*<<< orphan*/  set_anon_id; int /*<<< orphan*/  eap_error_cb; int /*<<< orphan*/  status_cb; int /*<<< orphan*/  cert_in_cb; int /*<<< orphan*/  cert_cb; int /*<<< orphan*/  cb; int /*<<< orphan*/  port_cb; int /*<<< orphan*/  eap_proxy_notify_sim_status; int /*<<< orphan*/  eap_proxy_cb; int /*<<< orphan*/  eap_param_needed; int /*<<< orphan*/  wps; int /*<<< orphan*/  openssl_ciphers; int /*<<< orphan*/  pkcs11_module_path; int /*<<< orphan*/  pkcs11_engine_path; int /*<<< orphan*/  opensc_engine_path; int /*<<< orphan*/  aborted_cached; int /*<<< orphan*/  get_config_blob; int /*<<< orphan*/  set_config_blob; int /*<<< orphan*/  set_wep_key; int /*<<< orphan*/  eapol_send; int /*<<< orphan*/  eapol_done_cb; scalar_t__ preauth; struct wpa_supplicant* eapol_send_ctx; struct wpa_supplicant* msg_ctx; struct wpa_supplicant* ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  cert_in_cb; int /*<<< orphan*/  openssl_ciphers; int /*<<< orphan*/  pkcs11_module_path; int /*<<< orphan*/  pkcs11_engine_path; int /*<<< orphan*/  opensc_engine_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/ * eapol_sm_init (struct eapol_ctx*) ; 
 int /*<<< orphan*/  os_free (struct eapol_ctx*) ; 
 struct eapol_ctx* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_eapol_set_wep_key ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_aborted_cached ; 
 int /*<<< orphan*/  wpa_supplicant_cert_cb ; 
 int /*<<< orphan*/  wpa_supplicant_eap_error_cb ; 
 int /*<<< orphan*/  wpa_supplicant_eap_param_needed ; 
 int /*<<< orphan*/  wpa_supplicant_eap_proxy_cb ; 
 int /*<<< orphan*/  wpa_supplicant_eap_proxy_notify_sim_status ; 
 int /*<<< orphan*/  wpa_supplicant_eapol_cb ; 
 int /*<<< orphan*/  wpa_supplicant_eapol_send ; 
 int /*<<< orphan*/  wpa_supplicant_get_config_blob ; 
 int /*<<< orphan*/  wpa_supplicant_notify_eapol_done ; 
 int /*<<< orphan*/  wpa_supplicant_port_cb ; 
 int /*<<< orphan*/  wpa_supplicant_set_anon_id ; 
 int /*<<< orphan*/  wpa_supplicant_set_config_blob ; 
 int /*<<< orphan*/  wpa_supplicant_status_cb ; 

int wpa_supplicant_init_eapol(struct wpa_supplicant *wpa_s)
{
#ifdef IEEE8021X_EAPOL
	struct eapol_ctx *ctx;
	ctx = os_zalloc(sizeof(*ctx));
	if (ctx == NULL) {
		wpa_printf(MSG_ERROR, "Failed to allocate EAPOL context.");
		return -1;
	}

	ctx->ctx = wpa_s;
	ctx->msg_ctx = wpa_s;
	ctx->eapol_send_ctx = wpa_s;
	ctx->preauth = 0;
	ctx->eapol_done_cb = wpa_supplicant_notify_eapol_done;
	ctx->eapol_send = wpa_supplicant_eapol_send;
	ctx->set_wep_key = wpa_eapol_set_wep_key;
#ifndef CONFIG_NO_CONFIG_BLOBS
	ctx->set_config_blob = wpa_supplicant_set_config_blob;
	ctx->get_config_blob = wpa_supplicant_get_config_blob;
#endif /* CONFIG_NO_CONFIG_BLOBS */
	ctx->aborted_cached = wpa_supplicant_aborted_cached;
	ctx->opensc_engine_path = wpa_s->conf->opensc_engine_path;
	ctx->pkcs11_engine_path = wpa_s->conf->pkcs11_engine_path;
	ctx->pkcs11_module_path = wpa_s->conf->pkcs11_module_path;
	ctx->openssl_ciphers = wpa_s->conf->openssl_ciphers;
	ctx->wps = wpa_s->wps;
	ctx->eap_param_needed = wpa_supplicant_eap_param_needed;
#ifdef CONFIG_EAP_PROXY
	ctx->eap_proxy_cb = wpa_supplicant_eap_proxy_cb;
	ctx->eap_proxy_notify_sim_status =
		wpa_supplicant_eap_proxy_notify_sim_status;
#endif /* CONFIG_EAP_PROXY */
	ctx->port_cb = wpa_supplicant_port_cb;
	ctx->cb = wpa_supplicant_eapol_cb;
	ctx->cert_cb = wpa_supplicant_cert_cb;
	ctx->cert_in_cb = wpa_s->conf->cert_in_cb;
	ctx->status_cb = wpa_supplicant_status_cb;
	ctx->eap_error_cb = wpa_supplicant_eap_error_cb;
	ctx->set_anon_id = wpa_supplicant_set_anon_id;
	ctx->cb_ctx = wpa_s;
	wpa_s->eapol = eapol_sm_init(ctx);
	if (wpa_s->eapol == NULL) {
		os_free(ctx);
		wpa_printf(MSG_ERROR, "Failed to initialize EAPOL state "
			   "machines.");
		return -1;
	}
#endif /* IEEE8021X_EAPOL */

	return 0;
}