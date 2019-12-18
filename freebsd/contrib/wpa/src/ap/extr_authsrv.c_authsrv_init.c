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
struct tls_connection_params {scalar_t__ crl_reload_interval; int /*<<< orphan*/  check_cert_subject; int /*<<< orphan*/  ocsp_stapling_response_multi; int /*<<< orphan*/  ocsp_stapling_response; int /*<<< orphan*/  openssl_ecdh_curves; int /*<<< orphan*/  openssl_ciphers; scalar_t__ dh_file; int /*<<< orphan*/  private_key_passwd2; int /*<<< orphan*/  private_key_passwd; scalar_t__ private_key2; scalar_t__ private_key; scalar_t__ client_cert2; scalar_t__ client_cert; scalar_t__ ca_cert; struct hostapd_data* cb_ctx; int /*<<< orphan*/  event_cb; int /*<<< orphan*/  tls_flags; int /*<<< orphan*/  tls_session_lifetime; } ;
struct tls_config {scalar_t__ crl_reload_interval; int /*<<< orphan*/  check_cert_subject; int /*<<< orphan*/  ocsp_stapling_response_multi; int /*<<< orphan*/  ocsp_stapling_response; int /*<<< orphan*/  openssl_ecdh_curves; int /*<<< orphan*/  openssl_ciphers; scalar_t__ dh_file; int /*<<< orphan*/  private_key_passwd2; int /*<<< orphan*/  private_key_passwd; scalar_t__ private_key2; scalar_t__ private_key; scalar_t__ client_cert2; scalar_t__ client_cert; scalar_t__ ca_cert; struct hostapd_data* cb_ctx; int /*<<< orphan*/  event_cb; int /*<<< orphan*/  tls_flags; int /*<<< orphan*/  tls_session_lifetime; } ;
struct hostapd_data {TYPE_1__* conf; int /*<<< orphan*/ * eap_sim_db_priv; int /*<<< orphan*/ * ssl_ctx; } ;
typedef  int /*<<< orphan*/  params ;
typedef  int /*<<< orphan*/  conf ;
struct TYPE_2__ {scalar_t__ crl_reload_interval; scalar_t__ check_crl; scalar_t__ radius_server_clients; int /*<<< orphan*/  eap_sim_db_timeout; scalar_t__ eap_sim_db; int /*<<< orphan*/  check_crl_strict; int /*<<< orphan*/  check_cert_subject; int /*<<< orphan*/  ocsp_stapling_response_multi; int /*<<< orphan*/  ocsp_stapling_response; int /*<<< orphan*/  openssl_ecdh_curves; int /*<<< orphan*/  openssl_ciphers; scalar_t__ dh_file; int /*<<< orphan*/  private_key_passwd2; int /*<<< orphan*/  private_key_passwd; scalar_t__ private_key2; scalar_t__ private_key; scalar_t__ server_cert2; scalar_t__ server_cert; scalar_t__ ca_cert; int /*<<< orphan*/  tls_flags; int /*<<< orphan*/  tls_session_lifetime; scalar_t__ eap_server; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  authsrv_deinit (struct hostapd_data*) ; 
 int /*<<< orphan*/  authsrv_tls_event ; 
 int /*<<< orphan*/ * eap_sim_db_init (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hostapd_data*) ; 
 scalar_t__ hostapd_setup_radius_srv (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_sim_db_cb ; 
 int /*<<< orphan*/  os_memset (struct tls_connection_params*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tls_global_set_params (int /*<<< orphan*/ *,struct tls_connection_params*) ; 
 scalar_t__ tls_global_set_verify (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tls_init (struct tls_connection_params*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int authsrv_init(struct hostapd_data *hapd)
{
#ifdef EAP_TLS_FUNCS
	if (hapd->conf->eap_server &&
	    (hapd->conf->ca_cert || hapd->conf->server_cert ||
	     hapd->conf->private_key || hapd->conf->dh_file ||
	     hapd->conf->server_cert2 || hapd->conf->private_key2)) {
		struct tls_config conf;
		struct tls_connection_params params;

		os_memset(&conf, 0, sizeof(conf));
		conf.tls_session_lifetime = hapd->conf->tls_session_lifetime;
		if (hapd->conf->crl_reload_interval > 0 &&
		    hapd->conf->check_crl <= 0) {
			wpa_printf(MSG_INFO,
				   "Cannot enable CRL reload functionality - it depends on check_crl being set");
		} else if (hapd->conf->crl_reload_interval > 0) {
			conf.crl_reload_interval =
				hapd->conf->crl_reload_interval;
			wpa_printf(MSG_INFO,
				   "Enabled CRL reload functionality");
		}
		conf.tls_flags = hapd->conf->tls_flags;
		conf.event_cb = authsrv_tls_event;
		conf.cb_ctx = hapd;
		hapd->ssl_ctx = tls_init(&conf);
		if (hapd->ssl_ctx == NULL) {
			wpa_printf(MSG_ERROR, "Failed to initialize TLS");
			authsrv_deinit(hapd);
			return -1;
		}

		os_memset(&params, 0, sizeof(params));
		params.ca_cert = hapd->conf->ca_cert;
		params.client_cert = hapd->conf->server_cert;
		params.client_cert2 = hapd->conf->server_cert2;
		params.private_key = hapd->conf->private_key;
		params.private_key2 = hapd->conf->private_key2;
		params.private_key_passwd = hapd->conf->private_key_passwd;
		params.private_key_passwd2 = hapd->conf->private_key_passwd2;
		params.dh_file = hapd->conf->dh_file;
		params.openssl_ciphers = hapd->conf->openssl_ciphers;
		params.openssl_ecdh_curves = hapd->conf->openssl_ecdh_curves;
		params.ocsp_stapling_response =
			hapd->conf->ocsp_stapling_response;
		params.ocsp_stapling_response_multi =
			hapd->conf->ocsp_stapling_response_multi;
		params.check_cert_subject = hapd->conf->check_cert_subject;

		if (tls_global_set_params(hapd->ssl_ctx, &params)) {
			wpa_printf(MSG_ERROR, "Failed to set TLS parameters");
			authsrv_deinit(hapd);
			return -1;
		}

		if (tls_global_set_verify(hapd->ssl_ctx,
					  hapd->conf->check_crl,
					  hapd->conf->check_crl_strict)) {
			wpa_printf(MSG_ERROR, "Failed to enable check_crl");
			authsrv_deinit(hapd);
			return -1;
		}
	}
#endif /* EAP_TLS_FUNCS */

#ifdef EAP_SIM_DB
	if (hapd->conf->eap_sim_db) {
		hapd->eap_sim_db_priv =
			eap_sim_db_init(hapd->conf->eap_sim_db,
					hapd->conf->eap_sim_db_timeout,
					hostapd_sim_db_cb, hapd);
		if (hapd->eap_sim_db_priv == NULL) {
			wpa_printf(MSG_ERROR, "Failed to initialize EAP-SIM "
				   "database interface");
			authsrv_deinit(hapd);
			return -1;
		}
	}
#endif /* EAP_SIM_DB */

#ifdef RADIUS_SERVER
	if (hapd->conf->radius_server_clients &&
	    hostapd_setup_radius_srv(hapd))
		return -1;
#endif /* RADIUS_SERVER */

	return 0;
}