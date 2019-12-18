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
struct tls_global {int server; int params_set; int /*<<< orphan*/  xcred; int /*<<< orphan*/ * ocsp_stapling_response; } ;
struct tls_connection_params {int flags; scalar_t__ ocsp_stapling_response; int /*<<< orphan*/  private_key_passwd; int /*<<< orphan*/  private_key; int /*<<< orphan*/  client_cert; int /*<<< orphan*/  ca_cert; scalar_t__ check_cert_subject; } ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTLS_VERIFY_ALLOW_SIGN_RSA_MD5 ; 
 int /*<<< orphan*/  GNUTLS_VERIFY_DISABLE_TIME_CHECKS ; 
 int /*<<< orphan*/  GNUTLS_X509_FMT_DER ; 
 int /*<<< orphan*/  GNUTLS_X509_FMT_PEM ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int TLS_CONN_ALLOW_SIGN_RSA_MD5 ; 
 int TLS_CONN_DISABLE_TIME_CHECKS ; 
 int gnutls_certificate_allocate_credentials (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnutls_certificate_free_credentials (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_certificate_set_ocsp_status_request_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tls_global*) ; 
 int /*<<< orphan*/  gnutls_certificate_set_verify_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gnutls_certificate_set_x509_key_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gnutls_certificate_set_x509_simple_pkcs12_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gnutls_certificate_set_x509_trust_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_strerror (int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_strdup (scalar_t__) ; 
 int /*<<< orphan*/  server_ocsp_status_req ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int tls_global_set_params(void *tls_ctx,
			  const struct tls_connection_params *params)
{
	struct tls_global *global = tls_ctx;
	int ret;

	if (params->check_cert_subject)
		return -1; /* not yet supported */

	/* Currently, global parameters are only set when running in server
	 * mode. */
	global->server = 1;

	if (global->params_set) {
		gnutls_certificate_free_credentials(global->xcred);
		global->params_set = 0;
	}

	ret = gnutls_certificate_allocate_credentials(&global->xcred);
	if (ret) {
		wpa_printf(MSG_DEBUG, "Failed to allocate global credentials "
			   "%s", gnutls_strerror(ret));
		return -1;
	}

	if (params->ca_cert) {
		ret = gnutls_certificate_set_x509_trust_file(
			global->xcred, params->ca_cert, GNUTLS_X509_FMT_DER);
		if (ret < 0) {
			wpa_printf(MSG_DEBUG, "Failed to read CA cert '%s' "
				   "in DER format: %s", params->ca_cert,
				   gnutls_strerror(ret));
			ret = gnutls_certificate_set_x509_trust_file(
				global->xcred, params->ca_cert,
				GNUTLS_X509_FMT_PEM);
			if (ret < 0) {
				wpa_printf(MSG_DEBUG, "Failed to read CA cert "
					   "'%s' in PEM format: %s",
					   params->ca_cert,
					   gnutls_strerror(ret));
				goto fail;
			}
		}

		if (params->flags & TLS_CONN_ALLOW_SIGN_RSA_MD5) {
			gnutls_certificate_set_verify_flags(
				global->xcred,
				GNUTLS_VERIFY_ALLOW_SIGN_RSA_MD5);
		}

		if (params->flags & TLS_CONN_DISABLE_TIME_CHECKS) {
			gnutls_certificate_set_verify_flags(
				global->xcred,
				GNUTLS_VERIFY_DISABLE_TIME_CHECKS);
		}
	}

	if (params->client_cert && params->private_key) {
		/* TODO: private_key_passwd? */
		ret = gnutls_certificate_set_x509_key_file(
			global->xcred, params->client_cert,
			params->private_key, GNUTLS_X509_FMT_DER);
		if (ret < 0) {
			wpa_printf(MSG_DEBUG, "Failed to read client cert/key "
				   "in DER format: %s", gnutls_strerror(ret));
			ret = gnutls_certificate_set_x509_key_file(
				global->xcred, params->client_cert,
				params->private_key, GNUTLS_X509_FMT_PEM);
			if (ret < 0) {
				wpa_printf(MSG_DEBUG, "Failed to read client "
					   "cert/key in PEM format: %s",
					   gnutls_strerror(ret));
				goto fail;
			}
		}
	} else if (params->private_key) {
		int pkcs12_ok = 0;
#ifdef PKCS12_FUNCS
		/* Try to load in PKCS#12 format */
		ret = gnutls_certificate_set_x509_simple_pkcs12_file(
			global->xcred, params->private_key,
			GNUTLS_X509_FMT_DER, params->private_key_passwd);
		if (ret != 0) {
			wpa_printf(MSG_DEBUG, "Failed to load private_key in "
				   "PKCS#12 format: %s", gnutls_strerror(ret));
			goto fail;
		} else
			pkcs12_ok = 1;
#endif /* PKCS12_FUNCS */

		if (!pkcs12_ok) {
			wpa_printf(MSG_DEBUG, "GnuTLS: PKCS#12 support not "
				   "included");
			goto fail;
		}
	}

#if GNUTLS_VERSION_NUMBER >= 0x030103
	os_free(global->ocsp_stapling_response);
	if (params->ocsp_stapling_response)
		global->ocsp_stapling_response =
			os_strdup(params->ocsp_stapling_response);
	else
		global->ocsp_stapling_response = NULL;
	gnutls_certificate_set_ocsp_status_request_function(
		global->xcred, server_ocsp_status_req, global);
#endif /* 3.1.3 */

	global->params_set = 1;

	return 0;

fail:
	gnutls_certificate_free_credentials(global->xcred);
	return -1;
}