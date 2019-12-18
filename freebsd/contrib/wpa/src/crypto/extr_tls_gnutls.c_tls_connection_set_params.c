#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tls_connection_params {int flags; char const* ca_cert; char const* private_key; int /*<<< orphan*/  private_key_passwd; int /*<<< orphan*/  private_key_blob_len; scalar_t__ private_key_blob; int /*<<< orphan*/  client_cert_blob_len; scalar_t__ client_cert_blob; int /*<<< orphan*/  client_cert; scalar_t__ ca_cert_blob; scalar_t__ ca_path; int /*<<< orphan*/  ca_cert_blob_len; scalar_t__ openssl_ecdh_curves; scalar_t__ openssl_ciphers; scalar_t__ domain_match; scalar_t__ suffix_match; scalar_t__ altsubject_match; scalar_t__ subject_match; } ;
struct tls_connection {int flags; int disable_time_checks; int verify_peer; int params_set; int /*<<< orphan*/  xcred; int /*<<< orphan*/  session; int /*<<< orphan*/ * domain_match; int /*<<< orphan*/ * suffix_match; } ;
typedef  int /*<<< orphan*/  prio_buf ;
struct TYPE_8__ {unsigned char* data; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ gnutls_datum_t ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTLS_CRD_CERTIFICATE ; 
 int GNUTLS_E_SUCCESS ; 
 int /*<<< orphan*/  GNUTLS_VERIFY_ALLOW_SIGN_RSA_MD5 ; 
 int /*<<< orphan*/  GNUTLS_VERIFY_DISABLE_TIME_CHECKS ; 
 int /*<<< orphan*/  GNUTLS_X509_FMT_DER ; 
 int /*<<< orphan*/  GNUTLS_X509_FMT_PEM ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int TLS_CONN_ALLOW_SIGN_RSA_MD5 ; 
 int TLS_CONN_DISABLE_TIME_CHECKS ; 
 int TLS_CONN_DISABLE_TLSv1_0 ; 
 int TLS_CONN_DISABLE_TLSv1_1 ; 
 int TLS_CONN_DISABLE_TLSv1_2 ; 
 int TLS_CONN_EXT_CERT_CHECK ; 
 int TLS_CONN_REQUEST_OCSP ; 
 int TLS_CONN_REQUIRE_OCSP ; 
 int TLS_CONN_REQUIRE_OCSP_ALL ; 
 int TLS_CONN_SUITEB ; 
 int /*<<< orphan*/  gnutls_certificate_set_verify_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_certificate_set_verify_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gnutls_certificate_set_x509_key_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int gnutls_certificate_set_x509_key_file2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gnutls_certificate_set_x509_key_mem (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int gnutls_certificate_set_x509_key_mem2 (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gnutls_certificate_set_x509_simple_pkcs12_file (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gnutls_certificate_set_x509_simple_pkcs12_mem (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gnutls_certificate_set_x509_trust_file (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int gnutls_certificate_set_x509_trust_mem (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int gnutls_credentials_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gnutls_ocsp_status_request_enable_client (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gnutls_priority_set_direct (int /*<<< orphan*/ ,char const*,char const**) ; 
 char const* gnutls_strerror (int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,char*,char*,char*) ; 
 scalar_t__ os_strcmp (scalar_t__,char*) ; 
 void* os_strdup (scalar_t__) ; 
 int /*<<< orphan*/  tls_connection_verify_peer ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int tls_connection_set_params(void *tls_ctx, struct tls_connection *conn,
			      const struct tls_connection_params *params)
{
	int ret;
	const char *err;
	char prio_buf[100];
	const char *prio = NULL;

	if (conn == NULL || params == NULL)
		return -1;

	if (params->flags & TLS_CONN_REQUIRE_OCSP_ALL) {
		wpa_printf(MSG_INFO,
			   "GnuTLS: ocsp=3 not supported");
		return -1;
	}

	if (params->flags & TLS_CONN_EXT_CERT_CHECK) {
		wpa_printf(MSG_INFO,
			   "GnuTLS: tls_ext_cert_check=1 not supported");
		return -1;
	}

	if (params->subject_match) {
		wpa_printf(MSG_INFO, "GnuTLS: subject_match not supported");
		return -1;
	}

	if (params->altsubject_match) {
		wpa_printf(MSG_INFO, "GnuTLS: altsubject_match not supported");
		return -1;
	}

	os_free(conn->suffix_match);
	conn->suffix_match = NULL;
	if (params->suffix_match) {
		conn->suffix_match = os_strdup(params->suffix_match);
		if (conn->suffix_match == NULL)
			return -1;
	}

#if GNUTLS_VERSION_NUMBER >= 0x030300
	os_free(conn->domain_match);
	conn->domain_match = NULL;
	if (params->domain_match) {
		conn->domain_match = os_strdup(params->domain_match);
		if (conn->domain_match == NULL)
			return -1;
	}
#else /* < 3.3.0 */
	if (params->domain_match) {
		wpa_printf(MSG_INFO, "GnuTLS: domain_match not supported");
		return -1;
	}
#endif /* >= 3.3.0 */

	conn->flags = params->flags;

	if (params->flags & (TLS_CONN_DISABLE_TLSv1_0 |
			     TLS_CONN_DISABLE_TLSv1_1 |
			     TLS_CONN_DISABLE_TLSv1_2)) {
		os_snprintf(prio_buf, sizeof(prio_buf),
			    "NORMAL:-VERS-SSL3.0%s%s%s",
			    params->flags & TLS_CONN_DISABLE_TLSv1_0 ?
			    ":-VERS-TLS1.0" : "",
			    params->flags & TLS_CONN_DISABLE_TLSv1_1 ?
			    ":-VERS-TLS1.1" : "",
			    params->flags & TLS_CONN_DISABLE_TLSv1_2 ?
			    ":-VERS-TLS1.2" : "");
		prio = prio_buf;
	}

	if (params->openssl_ciphers) {
		if (os_strcmp(params->openssl_ciphers, "SUITEB128") == 0) {
			prio = "SUITEB128";
		} else if (os_strcmp(params->openssl_ciphers,
				     "SUITEB192") == 0) {
			prio = "SUITEB192";
		} else if ((params->flags & TLS_CONN_SUITEB) &&
			   os_strcmp(params->openssl_ciphers,
				     "ECDHE-RSA-AES256-GCM-SHA384") == 0) {
			prio = "NONE:+VERS-TLS1.2:+AEAD:+ECDHE-RSA:+AES-256-GCM:+SIGN-RSA-SHA384:+CURVE-SECP384R1:+COMP-NULL";
		} else if (os_strcmp(params->openssl_ciphers,
				     "ECDHE-RSA-AES256-GCM-SHA384") == 0) {
			prio = "NONE:+VERS-TLS1.2:+AEAD:+ECDHE-RSA:+AES-256-GCM:+SIGN-RSA-SHA384:+CURVE-SECP384R1:+COMP-NULL";
		} else if (os_strcmp(params->openssl_ciphers,
				     "DHE-RSA-AES256-GCM-SHA384") == 0) {
			prio = "NONE:+VERS-TLS1.2:+AEAD:+DHE-RSA:+AES-256-GCM:+SIGN-RSA-SHA384:+CURVE-SECP384R1:+COMP-NULL:%PROFILE_HIGH";
		} else if (os_strcmp(params->openssl_ciphers,
				     "ECDHE-ECDSA-AES256-GCM-SHA384") == 0) {
			prio = "NONE:+VERS-TLS1.2:+AEAD:+ECDHE-ECDSA:+AES-256-GCM:+SIGN-RSA-SHA384:+CURVE-SECP384R1:+COMP-NULL";
		} else {
			wpa_printf(MSG_INFO,
				   "GnuTLS: openssl_ciphers not supported");
			return -1;
		}
	} else if (params->flags & TLS_CONN_SUITEB) {
		prio = "NONE:+VERS-TLS1.2:+AEAD:+ECDHE-ECDSA:+ECDHE-RSA:+DHE-RSA:+AES-256-GCM:+SIGN-RSA-SHA384:+CURVE-SECP384R1:+COMP-NULL:%PROFILE_HIGH";
	}

	if (prio) {
		wpa_printf(MSG_DEBUG, "GnuTLS: Set priority string: %s", prio);
		ret = gnutls_priority_set_direct(conn->session, prio, &err);
		if (ret < 0) {
			wpa_printf(MSG_ERROR,
				   "GnuTLS: Priority string failure at '%s'",
				   err);
			return -1;
		}
	}

	if (params->openssl_ecdh_curves) {
		wpa_printf(MSG_INFO,
			   "GnuTLS: openssl_ecdh_curves not supported");
		return -1;
	}

	/* TODO: gnutls_certificate_set_verify_flags(xcred, flags);
	 * to force peer validation(?) */

	if (params->ca_cert) {
		wpa_printf(MSG_DEBUG, "GnuTLS: Try to parse %s in DER format",
			   params->ca_cert);
		ret = gnutls_certificate_set_x509_trust_file(
			conn->xcred, params->ca_cert, GNUTLS_X509_FMT_DER);
		if (ret < 0) {
			wpa_printf(MSG_DEBUG,
				   "GnuTLS: Failed to read CA cert '%s' in DER format (%s) - try in PEM format",
				   params->ca_cert,
				   gnutls_strerror(ret));
			ret = gnutls_certificate_set_x509_trust_file(
				conn->xcred, params->ca_cert,
				GNUTLS_X509_FMT_PEM);
			if (ret < 0) {
				wpa_printf(MSG_DEBUG,
					   "Failed to read CA cert '%s' in PEM format: %s",
					   params->ca_cert,
					   gnutls_strerror(ret));
				return -1;
			}
			wpa_printf(MSG_DEBUG,
				   "GnuTLS: Successfully read CA cert '%s' in PEM format",
				   params->ca_cert);
		} else {
			wpa_printf(MSG_DEBUG,
				   "GnuTLS: Successfully read CA cert '%s' in DER format",
				   params->ca_cert);
		}
	} else if (params->ca_cert_blob) {
		gnutls_datum_t ca;

		ca.data = (unsigned char *) params->ca_cert_blob;
		ca.size = params->ca_cert_blob_len;

		ret = gnutls_certificate_set_x509_trust_mem(
			conn->xcred, &ca, GNUTLS_X509_FMT_DER);
		if (ret < 0) {
			wpa_printf(MSG_DEBUG,
				   "Failed to parse CA cert in DER format: %s",
				   gnutls_strerror(ret));
			ret = gnutls_certificate_set_x509_trust_mem(
				conn->xcred, &ca, GNUTLS_X509_FMT_PEM);
			if (ret < 0) {
				wpa_printf(MSG_DEBUG,
					   "Failed to parse CA cert in PEM format: %s",
					   gnutls_strerror(ret));
				return -1;
			}
		}
	} else if (params->ca_path) {
		wpa_printf(MSG_INFO, "GnuTLS: ca_path not supported");
		return -1;
	}

	conn->disable_time_checks = 0;
	if (params->ca_cert || params->ca_cert_blob) {
		conn->verify_peer = 1;
		gnutls_certificate_set_verify_function(
			conn->xcred, tls_connection_verify_peer);

		if (params->flags & TLS_CONN_ALLOW_SIGN_RSA_MD5) {
			gnutls_certificate_set_verify_flags(
				conn->xcred, GNUTLS_VERIFY_ALLOW_SIGN_RSA_MD5);
		}

		if (params->flags & TLS_CONN_DISABLE_TIME_CHECKS) {
			conn->disable_time_checks = 1;
			gnutls_certificate_set_verify_flags(
				conn->xcred,
				GNUTLS_VERIFY_DISABLE_TIME_CHECKS);
		}
	}

	if (params->client_cert && params->private_key) {
		wpa_printf(MSG_DEBUG,
			   "GnuTLS: Try to parse client cert '%s' and key '%s' in DER format",
			   params->client_cert, params->private_key);
#if GNUTLS_VERSION_NUMBER >= 0x03010b
		ret = gnutls_certificate_set_x509_key_file2(
			conn->xcred, params->client_cert, params->private_key,
			GNUTLS_X509_FMT_DER, params->private_key_passwd, 0);
#else
		/* private_key_passwd not (easily) supported here */
		ret = gnutls_certificate_set_x509_key_file(
			conn->xcred, params->client_cert, params->private_key,
			GNUTLS_X509_FMT_DER);
#endif
		if (ret < 0) {
			wpa_printf(MSG_DEBUG,
				   "GnuTLS: Failed to read client cert/key in DER format (%s) - try in PEM format",
				   gnutls_strerror(ret));
#if GNUTLS_VERSION_NUMBER >= 0x03010b
			ret = gnutls_certificate_set_x509_key_file2(
				conn->xcred, params->client_cert,
				params->private_key, GNUTLS_X509_FMT_PEM,
				params->private_key_passwd, 0);
#else
			ret = gnutls_certificate_set_x509_key_file(
				conn->xcred, params->client_cert,
				params->private_key, GNUTLS_X509_FMT_PEM);
#endif
			if (ret < 0) {
				wpa_printf(MSG_DEBUG, "Failed to read client "
					   "cert/key in PEM format: %s",
					   gnutls_strerror(ret));
				return ret;
			}
			wpa_printf(MSG_DEBUG,
				   "GnuTLS: Successfully read client cert/key in PEM format");
		} else {
			wpa_printf(MSG_DEBUG,
				   "GnuTLS: Successfully read client cert/key in DER format");
		}
	} else if (params->private_key) {
		int pkcs12_ok = 0;
#ifdef PKCS12_FUNCS
		/* Try to load in PKCS#12 format */
		wpa_printf(MSG_DEBUG,
			   "GnuTLS: Try to parse client cert/key '%s'in PKCS#12 DER format",
			   params->private_key);
		ret = gnutls_certificate_set_x509_simple_pkcs12_file(
			conn->xcred, params->private_key, GNUTLS_X509_FMT_DER,
			params->private_key_passwd);
		if (ret != 0) {
			wpa_printf(MSG_DEBUG, "Failed to load private_key in "
				   "PKCS#12 format: %s", gnutls_strerror(ret));
			return -1;
		} else
			pkcs12_ok = 1;
#endif /* PKCS12_FUNCS */

		if (!pkcs12_ok) {
			wpa_printf(MSG_DEBUG, "GnuTLS: PKCS#12 support not "
				   "included");
			return -1;
		}
	} else if (params->client_cert_blob && params->private_key_blob) {
		gnutls_datum_t cert, key;

		cert.data = (unsigned char *) params->client_cert_blob;
		cert.size = params->client_cert_blob_len;
		key.data = (unsigned char *) params->private_key_blob;
		key.size = params->private_key_blob_len;

#if GNUTLS_VERSION_NUMBER >= 0x03010b
		ret = gnutls_certificate_set_x509_key_mem2(
			conn->xcred, &cert, &key, GNUTLS_X509_FMT_DER,
			params->private_key_passwd, 0);
#else
		/* private_key_passwd not (easily) supported here */
		ret = gnutls_certificate_set_x509_key_mem(
			conn->xcred, &cert, &key, GNUTLS_X509_FMT_DER);
#endif
		if (ret < 0) {
			wpa_printf(MSG_DEBUG, "Failed to read client cert/key "
				   "in DER format: %s", gnutls_strerror(ret));
#if GNUTLS_VERSION_NUMBER >= 0x03010b
			ret = gnutls_certificate_set_x509_key_mem2(
				conn->xcred, &cert, &key, GNUTLS_X509_FMT_PEM,
				params->private_key_passwd, 0);
#else
			/* private_key_passwd not (easily) supported here */
			ret = gnutls_certificate_set_x509_key_mem(
				conn->xcred, &cert, &key, GNUTLS_X509_FMT_PEM);
#endif
			if (ret < 0) {
				wpa_printf(MSG_DEBUG, "Failed to read client "
					   "cert/key in PEM format: %s",
					   gnutls_strerror(ret));
				return ret;
			}
		}
	} else if (params->private_key_blob) {
#ifdef PKCS12_FUNCS
		gnutls_datum_t key;

		key.data = (unsigned char *) params->private_key_blob;
		key.size = params->private_key_blob_len;

		/* Try to load in PKCS#12 format */
		ret = gnutls_certificate_set_x509_simple_pkcs12_mem(
			conn->xcred, &key, GNUTLS_X509_FMT_DER,
			params->private_key_passwd);
		if (ret != 0) {
			wpa_printf(MSG_DEBUG, "Failed to load private_key in "
				   "PKCS#12 format: %s", gnutls_strerror(ret));
			return -1;
		}
#else /* PKCS12_FUNCS */
		wpa_printf(MSG_DEBUG, "GnuTLS: PKCS#12 support not included");
		return -1;
#endif /* PKCS12_FUNCS */
	}

#if GNUTLS_VERSION_NUMBER >= 0x030103
	if (params->flags & (TLS_CONN_REQUEST_OCSP | TLS_CONN_REQUIRE_OCSP)) {
		ret = gnutls_ocsp_status_request_enable_client(conn->session,
							       NULL, 0, NULL);
		if (ret != GNUTLS_E_SUCCESS) {
			wpa_printf(MSG_INFO,
				   "GnuTLS: Failed to enable OCSP client");
			return -1;
		}
	}
#else /* 3.1.3 */
	if (params->flags & TLS_CONN_REQUIRE_OCSP) {
		wpa_printf(MSG_INFO,
			   "GnuTLS: OCSP not supported by this version of GnuTLS");
		return -1;
	}
#endif /* 3.1.3 */

	conn->params_set = 1;

	ret = gnutls_credentials_set(conn->session, GNUTLS_CRD_CERTIFICATE,
				     conn->xcred);
	if (ret < 0) {
		wpa_printf(MSG_INFO, "Failed to configure credentials: %s",
			   gnutls_strerror(ret));
	}

	return ret;
}