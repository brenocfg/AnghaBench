#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int hash_len; unsigned int depth; char* subject; int /*<<< orphan*/ * hash; struct wpabuf* cert; } ;
union tls_event_data {TYPE_1__ peer_cert; void* data; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct tls_connection {int /*<<< orphan*/  failed; TYPE_2__* global; int /*<<< orphan*/  disable_time_checks; int /*<<< orphan*/  domain_match; int /*<<< orphan*/  suffix_match; scalar_t__ verify_peer; } ;
struct os_time {scalar_t__ sec; } ;
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  gnutls_x509_crt_t ;
typedef  union tls_event_data gnutls_typed_vdata_st ;
typedef  int /*<<< orphan*/  gnutls_session_t ;
struct TYPE_10__ {size_t size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ gnutls_datum_t ;
typedef  int /*<<< orphan*/  gnutls_alert_description_t ;
typedef  int /*<<< orphan*/  ev ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_9__ {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tls_event_data*) ;int /*<<< orphan*/  server; scalar_t__ cert_in_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTLS_AL_FATAL ; 
 int /*<<< orphan*/  GNUTLS_A_BAD_CERTIFICATE ; 
 int /*<<< orphan*/  GNUTLS_A_CERTIFICATE_EXPIRED ; 
 int /*<<< orphan*/  GNUTLS_A_CERTIFICATE_REVOKED ; 
 int /*<<< orphan*/  GNUTLS_A_INSUFFICIENT_SECURITY ; 
 int /*<<< orphan*/  GNUTLS_A_INTERNAL_ERROR ; 
 int /*<<< orphan*/  GNUTLS_A_UNKNOWN_CA ; 
 unsigned int GNUTLS_CERT_EXPIRED ; 
 unsigned int GNUTLS_CERT_INSECURE_ALGORITHM ; 
 unsigned int GNUTLS_CERT_INVALID ; 
 unsigned int GNUTLS_CERT_NOT_ACTIVATED ; 
 unsigned int GNUTLS_CERT_REVOKED ; 
 unsigned int GNUTLS_CERT_SIGNER_NOT_FOUND ; 
 int /*<<< orphan*/  GNUTLS_DT_KEY_PURPOSE_OID ; 
 int GNUTLS_E_CERTIFICATE_ERROR ; 
 scalar_t__ GNUTLS_KP_TLS_WWW_SERVER ; 
 int /*<<< orphan*/  GNUTLS_X509_FMT_DER ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  TLS_CERT_CHAIN_SUCCESS ; 
 int /*<<< orphan*/  TLS_FAIL_BAD_CERTIFICATE ; 
 int /*<<< orphan*/  TLS_FAIL_DOMAIN_MISMATCH ; 
 int /*<<< orphan*/  TLS_FAIL_DOMAIN_SUFFIX_MISMATCH ; 
 int /*<<< orphan*/  TLS_FAIL_EXPIRED ; 
 int /*<<< orphan*/  TLS_FAIL_NOT_YET_VALID ; 
 int /*<<< orphan*/  TLS_FAIL_REVOKED ; 
 int /*<<< orphan*/  TLS_FAIL_UNTRUSTED ; 
 int /*<<< orphan*/  TLS_PEER_CERTIFICATE ; 
 scalar_t__ check_ocsp (struct tls_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnutls_alert_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* gnutls_certificate_get_peers (int /*<<< orphan*/ ,unsigned int*) ; 
 int gnutls_certificate_type_get (int /*<<< orphan*/ ) ; 
 int gnutls_certificate_verification_status_print (unsigned int,int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int gnutls_certificate_verify_peers (int /*<<< orphan*/ ,union tls_event_data*,int,unsigned int*) ; 
 int gnutls_certificate_verify_peers2 (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  gnutls_free (int /*<<< orphan*/ *) ; 
 struct tls_connection* gnutls_session_get_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_tls_fail_event (struct tls_connection*,TYPE_3__ const*,unsigned int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_x509_crt_deinit (int /*<<< orphan*/ ) ; 
 scalar_t__ gnutls_x509_crt_get_activation_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_x509_crt_get_dn (int /*<<< orphan*/ ,char*,size_t*) ; 
 scalar_t__ gnutls_x509_crt_get_expiration_time (int /*<<< orphan*/ ) ; 
 scalar_t__ gnutls_x509_crt_import (int /*<<< orphan*/ ,TYPE_3__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ gnutls_x509_crt_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_get_time (struct os_time*) ; 
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memset (union tls_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  server_eku_purpose (int /*<<< orphan*/ ) ; 
 scalar_t__ sha256_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tls_event_data*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tls_event_data*) ; 
 int /*<<< orphan*/  tls_match_suffix (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf* wpabuf_alloc_copy (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static int tls_connection_verify_peer(gnutls_session_t session)
{
	struct tls_connection *conn;
	unsigned int status, num_certs, i;
	struct os_time now;
	const gnutls_datum_t *certs;
	gnutls_x509_crt_t cert;
	gnutls_alert_description_t err;
	int res;

	conn = gnutls_session_get_ptr(session);
	if (!conn->verify_peer) {
		wpa_printf(MSG_DEBUG,
			   "GnuTLS: No peer certificate verification enabled");
		return 0;
	}

	wpa_printf(MSG_DEBUG, "GnuTSL: Verifying peer certificate");

#if GNUTLS_VERSION_NUMBER >= 0x030300
	{
		gnutls_typed_vdata_st data[1];
		unsigned int elements = 0;

		os_memset(data, 0, sizeof(data));
		if (!conn->global->server) {
			data[elements].type = GNUTLS_DT_KEY_PURPOSE_OID;
			data[elements].data = (void *) GNUTLS_KP_TLS_WWW_SERVER;
			elements++;
		}
		res = gnutls_certificate_verify_peers(session, data, 1,
						      &status);
	}
#else /* < 3.3.0 */
	res = gnutls_certificate_verify_peers2(session, &status);
#endif
	if (res < 0) {
		wpa_printf(MSG_INFO, "TLS: Failed to verify peer "
			   "certificate chain");
		err = GNUTLS_A_INTERNAL_ERROR;
		goto out;
	}

#if GNUTLS_VERSION_NUMBER >= 0x030104
	{
		gnutls_datum_t info;
		int ret, type;

		type = gnutls_certificate_type_get(session);
		ret = gnutls_certificate_verification_status_print(status, type,
								   &info, 0);
		if (ret < 0) {
			wpa_printf(MSG_DEBUG,
				   "GnuTLS: Failed to print verification status");
			err = GNUTLS_A_INTERNAL_ERROR;
			goto out;
		}
		wpa_printf(MSG_DEBUG, "GnuTLS: %s", info.data);
		gnutls_free(info.data);
	}
#endif /* GnuTLS 3.1.4 or newer */

	certs = gnutls_certificate_get_peers(session, &num_certs);
	if (certs == NULL || num_certs == 0) {
		wpa_printf(MSG_INFO, "TLS: No peer certificate chain received");
		err = GNUTLS_A_UNKNOWN_CA;
		goto out;
	}

	if (conn->verify_peer && (status & GNUTLS_CERT_INVALID)) {
		wpa_printf(MSG_INFO, "TLS: Peer certificate not trusted");
		if (status & GNUTLS_CERT_INSECURE_ALGORITHM) {
			wpa_printf(MSG_INFO, "TLS: Certificate uses insecure "
				   "algorithm");
			gnutls_tls_fail_event(conn, NULL, 0, NULL,
					      "certificate uses insecure algorithm",
					      TLS_FAIL_BAD_CERTIFICATE);
			err = GNUTLS_A_INSUFFICIENT_SECURITY;
			goto out;
		}
		if (status & GNUTLS_CERT_NOT_ACTIVATED) {
			wpa_printf(MSG_INFO, "TLS: Certificate not yet "
				   "activated");
			gnutls_tls_fail_event(conn, NULL, 0, NULL,
					      "certificate not yet valid",
					      TLS_FAIL_NOT_YET_VALID);
			err = GNUTLS_A_CERTIFICATE_EXPIRED;
			goto out;
		}
		if (status & GNUTLS_CERT_EXPIRED) {
			wpa_printf(MSG_INFO, "TLS: Certificate expired");
			gnutls_tls_fail_event(conn, NULL, 0, NULL,
					      "certificate has expired",
					      TLS_FAIL_EXPIRED);
			err = GNUTLS_A_CERTIFICATE_EXPIRED;
			goto out;
		}
		gnutls_tls_fail_event(conn, NULL, 0, NULL,
				      "untrusted certificate",
				      TLS_FAIL_UNTRUSTED);
		err = GNUTLS_A_INTERNAL_ERROR;
		goto out;
	}

	if (status & GNUTLS_CERT_SIGNER_NOT_FOUND) {
		wpa_printf(MSG_INFO, "TLS: Peer certificate does not have a "
			   "known issuer");
		gnutls_tls_fail_event(conn, NULL, 0, NULL, "signed not found",
				      TLS_FAIL_UNTRUSTED);
		err = GNUTLS_A_UNKNOWN_CA;
		goto out;
	}

	if (status & GNUTLS_CERT_REVOKED) {
		wpa_printf(MSG_INFO, "TLS: Peer certificate has been revoked");
		gnutls_tls_fail_event(conn, NULL, 0, NULL,
				      "certificate revoked",
				      TLS_FAIL_REVOKED);
		err = GNUTLS_A_CERTIFICATE_REVOKED;
		goto out;
	}

	if (status != 0) {
		wpa_printf(MSG_INFO, "TLS: Unknown verification status: %d",
			   status);
		err = GNUTLS_A_INTERNAL_ERROR;
		goto out;
	}

	if (check_ocsp(conn, session, &err))
		goto out;

	os_get_time(&now);

	for (i = 0; i < num_certs; i++) {
		char *buf;
		size_t len;
		if (gnutls_x509_crt_init(&cert) < 0) {
			wpa_printf(MSG_INFO, "TLS: Certificate initialization "
				   "failed");
			err = GNUTLS_A_BAD_CERTIFICATE;
			goto out;
		}

		if (gnutls_x509_crt_import(cert, &certs[i],
					   GNUTLS_X509_FMT_DER) < 0) {
			wpa_printf(MSG_INFO, "TLS: Could not parse peer "
				   "certificate %d/%d", i + 1, num_certs);
			gnutls_x509_crt_deinit(cert);
			err = GNUTLS_A_BAD_CERTIFICATE;
			goto out;
		}

		gnutls_x509_crt_get_dn(cert, NULL, &len);
		len++;
		buf = os_malloc(len + 1);
		if (buf) {
			buf[0] = buf[len] = '\0';
			gnutls_x509_crt_get_dn(cert, buf, &len);
		}
		wpa_printf(MSG_DEBUG, "TLS: Peer cert chain %d/%d: %s",
			   i + 1, num_certs, buf);

		if (conn->global->event_cb) {
			struct wpabuf *cert_buf = NULL;
			union tls_event_data ev;
#ifdef CONFIG_SHA256
			u8 hash[32];
			const u8 *_addr[1];
			size_t _len[1];
#endif /* CONFIG_SHA256 */

			os_memset(&ev, 0, sizeof(ev));
			if (conn->global->cert_in_cb) {
				cert_buf = wpabuf_alloc_copy(certs[i].data,
							     certs[i].size);
				ev.peer_cert.cert = cert_buf;
			}
#ifdef CONFIG_SHA256
			_addr[0] = certs[i].data;
			_len[0] = certs[i].size;
			if (sha256_vector(1, _addr, _len, hash) == 0) {
				ev.peer_cert.hash = hash;
				ev.peer_cert.hash_len = sizeof(hash);
			}
#endif /* CONFIG_SHA256 */
			ev.peer_cert.depth = i;
			ev.peer_cert.subject = buf;
			conn->global->event_cb(conn->global->cb_ctx,
					       TLS_PEER_CERTIFICATE, &ev);
			wpabuf_free(cert_buf);
		}

		if (i == 0) {
			if (conn->suffix_match &&
			    !tls_match_suffix(cert, conn->suffix_match, 0)) {
				wpa_printf(MSG_WARNING,
					   "TLS: Domain suffix match '%s' not found",
					   conn->suffix_match);
				gnutls_tls_fail_event(
					conn, &certs[i], i, buf,
					"Domain suffix mismatch",
					TLS_FAIL_DOMAIN_SUFFIX_MISMATCH);
				err = GNUTLS_A_BAD_CERTIFICATE;
				gnutls_x509_crt_deinit(cert);
				os_free(buf);
				goto out;
			}

#if GNUTLS_VERSION_NUMBER >= 0x030300
			if (conn->domain_match &&
			    !tls_match_suffix(cert, conn->domain_match, 1)) {
				wpa_printf(MSG_WARNING,
					   "TLS: Domain match '%s' not found",
					   conn->domain_match);
				gnutls_tls_fail_event(
					conn, &certs[i], i, buf,
					"Domain mismatch",
					TLS_FAIL_DOMAIN_MISMATCH);
				err = GNUTLS_A_BAD_CERTIFICATE;
				gnutls_x509_crt_deinit(cert);
				os_free(buf);
				goto out;
			}
#endif /* >= 3.3.0 */

			/* TODO: validate altsubject_match.
			 * For now, any such configuration is rejected in
			 * tls_connection_set_params() */

#if GNUTLS_VERSION_NUMBER < 0x030300
			/*
			 * gnutls_certificate_verify_peers() not available, so
			 * need to check EKU separately.
			 */
			if (!conn->global->server &&
			    !server_eku_purpose(cert)) {
				wpa_printf(MSG_WARNING,
					   "GnuTLS: No server EKU");
				gnutls_tls_fail_event(
					conn, &certs[i], i, buf,
					"No server EKU",
					TLS_FAIL_BAD_CERTIFICATE);
				err = GNUTLS_A_BAD_CERTIFICATE;
				gnutls_x509_crt_deinit(cert);
				os_free(buf);
				goto out;
			}
#endif /* < 3.3.0 */
		}

		if (!conn->disable_time_checks &&
		    (gnutls_x509_crt_get_expiration_time(cert) < now.sec ||
		     gnutls_x509_crt_get_activation_time(cert) > now.sec)) {
			wpa_printf(MSG_INFO, "TLS: Peer certificate %d/%d is "
				   "not valid at this time",
				   i + 1, num_certs);
			gnutls_tls_fail_event(
				conn, &certs[i], i, buf,
				"Certificate is not valid at this time",
				TLS_FAIL_EXPIRED);
			gnutls_x509_crt_deinit(cert);
			os_free(buf);
			err = GNUTLS_A_CERTIFICATE_EXPIRED;
			goto out;
		}

		os_free(buf);

		gnutls_x509_crt_deinit(cert);
	}

	if (conn->global->event_cb != NULL)
		conn->global->event_cb(conn->global->cb_ctx,
				       TLS_CERT_CHAIN_SUCCESS, NULL);

	return 0;

out:
	conn->failed++;
	gnutls_alert_send(session, GNUTLS_AL_FATAL, err);
	return GNUTLS_E_CERTIFICATE_ERROR;
}