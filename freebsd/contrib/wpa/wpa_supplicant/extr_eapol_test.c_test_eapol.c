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
struct wpa_supplicant {int /*<<< orphan*/ * eapol; int /*<<< orphan*/  scard; TYPE_1__* conf; struct wpa_ssid* current_ssid; int /*<<< orphan*/  wpa; int /*<<< orphan*/  key_mgmt; } ;
struct wpa_ssid {int /*<<< orphan*/  eap; int /*<<< orphan*/  eap_workaround; } ;
struct wpa_sm_ctx {int cert_in_cb; int /*<<< orphan*/  get_state; struct wpa_supplicant* msg_ctx; struct eapol_test_data* ctx; int /*<<< orphan*/  set_anon_id; int /*<<< orphan*/  cert_cb; int /*<<< orphan*/  eap_param_needed; int /*<<< orphan*/  openssl_ciphers; int /*<<< orphan*/  pkcs11_module_path; int /*<<< orphan*/  pkcs11_engine_path; int /*<<< orphan*/  opensc_engine_path; int /*<<< orphan*/  get_config_blob; int /*<<< orphan*/  set_config_blob; int /*<<< orphan*/  eapol_send; int /*<<< orphan*/  eapol_done_cb; scalar_t__ preauth; struct wpa_supplicant* eapol_send_ctx; struct eapol_test_data* cb_ctx; int /*<<< orphan*/  cb; int /*<<< orphan*/  scard_ctx; } ;
struct eapol_test_data {int dummy; } ;
struct eapol_ctx {int cert_in_cb; int /*<<< orphan*/  get_state; struct wpa_supplicant* msg_ctx; struct eapol_test_data* ctx; int /*<<< orphan*/  set_anon_id; int /*<<< orphan*/  cert_cb; int /*<<< orphan*/  eap_param_needed; int /*<<< orphan*/  openssl_ciphers; int /*<<< orphan*/  pkcs11_module_path; int /*<<< orphan*/  pkcs11_engine_path; int /*<<< orphan*/  opensc_engine_path; int /*<<< orphan*/  get_config_blob; int /*<<< orphan*/  set_config_blob; int /*<<< orphan*/  eapol_send; int /*<<< orphan*/  eapol_done_cb; scalar_t__ preauth; struct wpa_supplicant* eapol_send_ctx; struct eapol_test_data* cb_ctx; int /*<<< orphan*/  cb; int /*<<< orphan*/  scard_ctx; } ;
struct eapol_config {int accept_802_1x_keys; int /*<<< orphan*/  external_sim; int /*<<< orphan*/  workaround; int /*<<< orphan*/  fast_reauth; scalar_t__ required_keys; } ;
typedef  int /*<<< orphan*/  eapol_conf ;
struct TYPE_2__ {int /*<<< orphan*/  external_sim; int /*<<< orphan*/  fast_reauth; int /*<<< orphan*/  openssl_ciphers; int /*<<< orphan*/  pkcs11_module_path; int /*<<< orphan*/  pkcs11_engine_path; int /*<<< orphan*/  opensc_engine_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WPA_KEY_MGMT_IEEE8021X_NO_WPA ; 
 int /*<<< orphan*/  eapol_sm_cb ; 
 int /*<<< orphan*/ * eapol_sm_init (struct wpa_sm_ctx*) ; 
 int /*<<< orphan*/  eapol_sm_notify_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct eapol_config*) ; 
 int /*<<< orphan*/  eapol_sm_notify_portEnabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_sm_notify_portValid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_sm_register_scard_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_test_cert_cb ; 
 int /*<<< orphan*/  eapol_test_eap_param_needed ; 
 int /*<<< orphan*/  eapol_test_eapol_done_cb ; 
 int /*<<< orphan*/  eapol_test_eapol_send ; 
 int /*<<< orphan*/  eapol_test_get_config_blob ; 
 int /*<<< orphan*/  eapol_test_get_state ; 
 int /*<<< orphan*/  eapol_test_set_anon_id ; 
 int /*<<< orphan*/  eapol_test_set_config_blob ; 
 int /*<<< orphan*/  os_free (struct wpa_sm_ctx*) ; 
 int /*<<< orphan*/  os_memset (struct eapol_config*,int /*<<< orphan*/ ,int) ; 
 struct wpa_sm_ctx* os_zalloc (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  wpa_sm_init (struct wpa_sm_ctx*) ; 

__attribute__((used)) static int test_eapol(struct eapol_test_data *e, struct wpa_supplicant *wpa_s,
		      struct wpa_ssid *ssid)
{
	struct eapol_config eapol_conf;
	struct eapol_ctx *ctx;
	struct wpa_sm_ctx *wctx;

	ctx = os_zalloc(sizeof(*ctx));
	if (ctx == NULL) {
		printf("Failed to allocate EAPOL context.\n");
		return -1;
	}
	ctx->ctx = e;
	ctx->msg_ctx = wpa_s;
	ctx->scard_ctx = wpa_s->scard;
	ctx->cb = eapol_sm_cb;
	ctx->cb_ctx = e;
	ctx->eapol_send_ctx = wpa_s;
	ctx->preauth = 0;
	ctx->eapol_done_cb = eapol_test_eapol_done_cb;
	ctx->eapol_send = eapol_test_eapol_send;
	ctx->set_config_blob = eapol_test_set_config_blob;
	ctx->get_config_blob = eapol_test_get_config_blob;
	ctx->opensc_engine_path = wpa_s->conf->opensc_engine_path;
	ctx->pkcs11_engine_path = wpa_s->conf->pkcs11_engine_path;
	ctx->pkcs11_module_path = wpa_s->conf->pkcs11_module_path;
	ctx->openssl_ciphers = wpa_s->conf->openssl_ciphers;
	ctx->eap_param_needed = eapol_test_eap_param_needed;
	ctx->cert_cb = eapol_test_cert_cb;
	ctx->cert_in_cb = 1;
	ctx->set_anon_id = eapol_test_set_anon_id;

	wpa_s->eapol = eapol_sm_init(ctx);
	if (wpa_s->eapol == NULL) {
		os_free(ctx);
		printf("Failed to initialize EAPOL state machines.\n");
		return -1;
	}

	wpa_s->key_mgmt = WPA_KEY_MGMT_IEEE8021X_NO_WPA;
	wctx = os_zalloc(sizeof(*wctx));
	if (wctx == NULL) {
		os_free(ctx);
		return -1;
	}
	wctx->ctx = e;
	wctx->msg_ctx = wpa_s;
	wctx->get_state = eapol_test_get_state;
	wpa_s->wpa = wpa_sm_init(wctx);
	if (!wpa_s->wpa) {
		os_free(ctx);
		os_free(wctx);
		return -1;
	}

	if (!ssid)
		return 0;

	wpa_s->current_ssid = ssid;
	os_memset(&eapol_conf, 0, sizeof(eapol_conf));
	eapol_conf.accept_802_1x_keys = 1;
	eapol_conf.required_keys = 0;
	eapol_conf.fast_reauth = wpa_s->conf->fast_reauth;
	eapol_conf.workaround = ssid->eap_workaround;
	eapol_conf.external_sim = wpa_s->conf->external_sim;
	eapol_sm_notify_config(wpa_s->eapol, &ssid->eap, &eapol_conf);
	eapol_sm_register_scard_ctx(wpa_s->eapol, wpa_s->scard);


	eapol_sm_notify_portValid(wpa_s->eapol, FALSE);
	/* 802.1X::portControl = Auto */
	eapol_sm_notify_portEnabled(wpa_s->eapol, TRUE);

	return 0;
}