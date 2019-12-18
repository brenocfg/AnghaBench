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
struct tls_connection_params {int flags; int /*<<< orphan*/  openssl_ciphers; int /*<<< orphan*/  dh_blob_len; int /*<<< orphan*/  dh_blob; int /*<<< orphan*/  dh_file; int /*<<< orphan*/  private_key_blob_len; int /*<<< orphan*/  private_key_blob; int /*<<< orphan*/  private_key; int /*<<< orphan*/  client_cert_blob_len; int /*<<< orphan*/  client_cert_blob; int /*<<< orphan*/  client_cert; int /*<<< orphan*/  ca_cert_blob_len; int /*<<< orphan*/  ca_cert_blob; int /*<<< orphan*/  ca_cert; } ;
struct eap_ssl_data {scalar_t__ eap_type; } ;
struct eap_sm {int ext_cert_check; scalar_t__ workaround; } ;
struct eap_peer_config {int /*<<< orphan*/  openssl_ciphers; scalar_t__ teap_anon_dh; } ;

/* Variables and functions */
 scalar_t__ EAP_TYPE_FAST ; 
 scalar_t__ EAP_TYPE_PEAP ; 
 scalar_t__ EAP_TYPE_TEAP ; 
 scalar_t__ EAP_TYPE_TLS ; 
 scalar_t__ EAP_TYPE_TTLS ; 
 scalar_t__ EAP_UNAUTH_TLS_TYPE ; 
 scalar_t__ EAP_WFA_UNAUTH_TLS_TYPE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int TLS_CONN_DISABLE_SESSION_TICKET ; 
 int TLS_CONN_DISABLE_TLSv1_0 ; 
 int TLS_CONN_DISABLE_TLSv1_1 ; 
 int TLS_CONN_DISABLE_TLSv1_3 ; 
 int TLS_CONN_EAP_FAST ; 
 int TLS_CONN_EXT_CERT_CHECK ; 
 int TLS_CONN_TEAP_ANON_DH ; 
 scalar_t__ eap_tls_check_blob (struct eap_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eap_tls_params_from_conf1 (struct tls_connection_params*,struct eap_peer_config*) ; 
 int /*<<< orphan*/  eap_tls_params_from_conf2 (struct tls_connection_params*,struct eap_peer_config*) ; 
 int /*<<< orphan*/  os_memset (struct tls_connection_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_tls_params_from_conf(struct eap_sm *sm,
				    struct eap_ssl_data *data,
				    struct tls_connection_params *params,
				    struct eap_peer_config *config, int phase2)
{
	os_memset(params, 0, sizeof(*params));
	if (sm->workaround && data->eap_type != EAP_TYPE_FAST &&
	    data->eap_type != EAP_TYPE_TEAP) {
		/*
		 * Some deployed authentication servers seem to be unable to
		 * handle the TLS Session Ticket extension (they are supposed
		 * to ignore unrecognized TLS extensions, but end up rejecting
		 * the ClientHello instead). As a workaround, disable use of
		 * TLS Sesson Ticket extension for EAP-TLS, EAP-PEAP, and
		 * EAP-TTLS (EAP-FAST uses session ticket, so any server that
		 * supports EAP-FAST does not need this workaround).
		 */
		params->flags |= TLS_CONN_DISABLE_SESSION_TICKET;
	}
	if (data->eap_type == EAP_TYPE_TEAP) {
		/* RFC 7170 requires TLS v1.2 or newer to be used with TEAP */
		params->flags |= TLS_CONN_DISABLE_TLSv1_0 |
			TLS_CONN_DISABLE_TLSv1_1;
		if (config->teap_anon_dh)
			params->flags |= TLS_CONN_TEAP_ANON_DH;
	}
	if (data->eap_type == EAP_TYPE_FAST ||
	    data->eap_type == EAP_TYPE_TEAP ||
	    data->eap_type == EAP_TYPE_TTLS ||
	    data->eap_type == EAP_TYPE_PEAP) {
		/* The current EAP peer implementation is not yet ready for the
		 * TLS v1.3 changes, so disable this by default for now. */
		params->flags |= TLS_CONN_DISABLE_TLSv1_3;
	}
	if (data->eap_type == EAP_TYPE_TLS ||
	    data->eap_type == EAP_UNAUTH_TLS_TYPE ||
	    data->eap_type == EAP_WFA_UNAUTH_TLS_TYPE) {
		/* While the current EAP-TLS implementation is more or less
		 * complete for TLS v1.3, there has been no interoperability
		 * testing with other implementations, so disable for by default
		 * for now until there has been chance to confirm that no
		 * significant interoperability issues show up with TLS version
		 * update.
		 */
		params->flags |= TLS_CONN_DISABLE_TLSv1_3;
	}
	if (phase2) {
		wpa_printf(MSG_DEBUG, "TLS: using phase2 config options");
		eap_tls_params_from_conf2(params, config);
	} else {
		wpa_printf(MSG_DEBUG, "TLS: using phase1 config options");
		eap_tls_params_from_conf1(params, config);
		if (data->eap_type == EAP_TYPE_FAST)
			params->flags |= TLS_CONN_EAP_FAST;
	}

	/*
	 * Use blob data, if available. Otherwise, leave reference to external
	 * file as-is.
	 */
	if (eap_tls_check_blob(sm, &params->ca_cert, &params->ca_cert_blob,
			       &params->ca_cert_blob_len) ||
	    eap_tls_check_blob(sm, &params->client_cert,
			       &params->client_cert_blob,
			       &params->client_cert_blob_len) ||
	    eap_tls_check_blob(sm, &params->private_key,
			       &params->private_key_blob,
			       &params->private_key_blob_len) ||
	    eap_tls_check_blob(sm, &params->dh_file, &params->dh_blob,
			       &params->dh_blob_len)) {
		wpa_printf(MSG_INFO, "SSL: Failed to get configuration blobs");
		return -1;
	}

	params->openssl_ciphers = config->openssl_ciphers;

	sm->ext_cert_check = !!(params->flags & TLS_CONN_EXT_CERT_CHECK);

	return 0;
}