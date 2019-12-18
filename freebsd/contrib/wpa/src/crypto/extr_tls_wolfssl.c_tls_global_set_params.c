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
struct tls_connection_params {int flags; scalar_t__ ocsp_stapling_response; scalar_t__ openssl_ecdh_curves; scalar_t__ openssl_ciphers; int /*<<< orphan*/  dh_file; int /*<<< orphan*/  dh_blob_len; int /*<<< orphan*/  dh_blob; int /*<<< orphan*/  private_key; int /*<<< orphan*/  private_key_passwd; int /*<<< orphan*/  client_cert; int /*<<< orphan*/  ca_cert; scalar_t__ check_cert_subject; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int TLS_CONN_DISABLE_SESSION_TICKET ; 
 int /*<<< orphan*/  ocsp_resp_free_cb ; 
 int /*<<< orphan*/  ocsp_status_cb ; 
 scalar_t__ tls_global_ca_cert (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ tls_global_client_cert (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ tls_global_dh (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tls_global_private_key (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_CTX_SetOCSP_Cb (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wolfSSL_CTX_SetOCSP_OverrideURL (void*,scalar_t__) ; 
 int /*<<< orphan*/  wolfSSL_CTX_UseSessionTicket (void*) ; 
 int wolfSSL_CTX_set_cipher_list (void*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int tls_global_set_params(void *tls_ctx,
			  const struct tls_connection_params *params)
{
	wpa_printf(MSG_DEBUG, "SSL: global set params");

	if (params->check_cert_subject)
		return -1; /* not yet supported */

	if (tls_global_ca_cert(tls_ctx, params->ca_cert) < 0) {
		wpa_printf(MSG_INFO, "SSL: Failed to load ca cert file '%s'",
			   params->ca_cert);
		return -1;
	}

	if (tls_global_client_cert(tls_ctx, params->client_cert) < 0) {
		wpa_printf(MSG_INFO,
			   "SSL: Failed to load client cert file '%s'",
			   params->client_cert);
		return -1;
	}

	if (tls_global_private_key(tls_ctx, params->private_key,
				   params->private_key_passwd) < 0) {
		wpa_printf(MSG_INFO,
			   "SSL: Failed to load private key file '%s'",
			   params->private_key);
		return -1;
	}

	if (tls_global_dh(tls_ctx, params->dh_file, params->dh_blob,
			  params->dh_blob_len) < 0) {
		wpa_printf(MSG_INFO, "SSL: Failed to load DH file '%s'",
			   params->dh_file);
		return -1;
	}

	if (params->openssl_ciphers &&
	    wolfSSL_CTX_set_cipher_list(tls_ctx,
					params->openssl_ciphers) != 1) {
		wpa_printf(MSG_INFO,
			   "wolfSSL: Failed to set cipher string '%s'",
			   params->openssl_ciphers);
		return -1;
	}

	if (params->openssl_ecdh_curves) {
		wpa_printf(MSG_INFO,
			   "wolfSSL: openssl_ecdh_curves not supported");
		return -1;
	}

#ifdef HAVE_SESSION_TICKET
	/* Session ticket is off by default - can't disable once on. */
	if (!(params->flags & TLS_CONN_DISABLE_SESSION_TICKET))
		wolfSSL_CTX_UseSessionTicket(tls_ctx);
#endif /* HAVE_SESSION_TICKET */

#ifdef HAVE_OCSP
	if (params->ocsp_stapling_response) {
		wolfSSL_CTX_SetOCSP_OverrideURL(tls_ctx,
						params->ocsp_stapling_response);
		wolfSSL_CTX_SetOCSP_Cb(tls_ctx, ocsp_status_cb,
				       ocsp_resp_free_cb, NULL);
	}
#endif /* HAVE_OCSP */

	return 0;
}