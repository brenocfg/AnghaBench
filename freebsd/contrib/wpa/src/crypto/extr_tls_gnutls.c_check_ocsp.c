#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tls_connection {int flags; } ;
typedef  int /*<<< orphan*/  gnutls_session_t ;
typedef  int /*<<< orphan*/  gnutls_ocsp_resp_t ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ gnutls_datum_t ;
typedef  int /*<<< orphan*/  gnutls_alert_description_t ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTLS_A_CERTIFICATE_REVOKED ; 
 int GNUTLS_E_SUCCESS ; 
 unsigned int GNUTLS_OCSP_CERT_GOOD ; 
 unsigned int GNUTLS_OCSP_CERT_REVOKED ; 
 int /*<<< orphan*/  GNUTLS_OCSP_PRINT_FULL ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int TLS_CONN_REQUEST_OCSP ; 
 int TLS_CONN_REQUIRE_OCSP ; 
 int /*<<< orphan*/  TLS_FAIL_REVOKED ; 
 int /*<<< orphan*/  gnutls_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_ocsp_resp_deinit (int /*<<< orphan*/ ) ; 
 int gnutls_ocsp_resp_get_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int gnutls_ocsp_resp_import (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int gnutls_ocsp_resp_init (int /*<<< orphan*/ *) ; 
 int gnutls_ocsp_resp_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int gnutls_ocsp_status_request_get (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gnutls_ocsp_status_request_is_checked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_strerror (int) ; 
 int /*<<< orphan*/  gnutls_tls_fail_event (struct tls_connection*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int check_ocsp(struct tls_connection *conn, gnutls_session_t session,
		      gnutls_alert_description_t *err)
{
#if GNUTLS_VERSION_NUMBER >= 0x030103
	gnutls_datum_t response, buf;
	gnutls_ocsp_resp_t resp;
	unsigned int cert_status;
	int res;

	if (!(conn->flags & (TLS_CONN_REQUEST_OCSP | TLS_CONN_REQUIRE_OCSP)))
		return 0;

	if (!gnutls_ocsp_status_request_is_checked(session, 0)) {
		if (conn->flags & TLS_CONN_REQUIRE_OCSP) {
			wpa_printf(MSG_INFO,
				   "GnuTLS: No valid OCSP response received");
			goto ocsp_error;
		}

		wpa_printf(MSG_DEBUG,
			   "GnuTLS: Valid OCSP response was not received - continue since OCSP was not required");
		return 0;
	}

	/*
	 * GnuTLS has already verified the OCSP response in
	 * check_ocsp_response() and rejected handshake if the certificate was
	 * found to be revoked. However, if the response indicates that the
	 * status is unknown, handshake continues and reaches here. We need to
	 * re-import the OCSP response to check for unknown certificate status,
	 * but we do not need to repeat gnutls_ocsp_resp_check_crt() and
	 * gnutls_ocsp_resp_verify_direct() calls.
	 */

	res = gnutls_ocsp_status_request_get(session, &response);
	if (res != GNUTLS_E_SUCCESS) {
		wpa_printf(MSG_INFO,
			   "GnuTLS: OCSP response was received, but it was not valid");
		goto ocsp_error;
	}

	if (gnutls_ocsp_resp_init(&resp) != GNUTLS_E_SUCCESS)
		goto ocsp_error;

	res = gnutls_ocsp_resp_import(resp, &response);
	if (res != GNUTLS_E_SUCCESS) {
		wpa_printf(MSG_INFO,
			   "GnuTLS: Could not parse received OCSP response: %s",
			   gnutls_strerror(res));
		gnutls_ocsp_resp_deinit(resp);
		goto ocsp_error;
	}

	res = gnutls_ocsp_resp_print(resp, GNUTLS_OCSP_PRINT_FULL, &buf);
	if (res == GNUTLS_E_SUCCESS) {
		wpa_printf(MSG_DEBUG, "GnuTLS: %s", buf.data);
		gnutls_free(buf.data);
	}

	res = gnutls_ocsp_resp_get_single(resp, 0, NULL, NULL, NULL,
					  NULL, &cert_status, NULL,
					  NULL, NULL, NULL);
	gnutls_ocsp_resp_deinit(resp);
	if (res != GNUTLS_E_SUCCESS) {
		wpa_printf(MSG_INFO,
			   "GnuTLS: Failed to extract OCSP information: %s",
			   gnutls_strerror(res));
		goto ocsp_error;
	}

	if (cert_status == GNUTLS_OCSP_CERT_GOOD) {
		wpa_printf(MSG_DEBUG, "GnuTLS: OCSP cert status: good");
	} else if (cert_status == GNUTLS_OCSP_CERT_REVOKED) {
		wpa_printf(MSG_DEBUG,
			   "GnuTLS: OCSP cert status: revoked");
		goto ocsp_error;
	} else {
		wpa_printf(MSG_DEBUG,
			   "GnuTLS: OCSP cert status: unknown");
		if (conn->flags & TLS_CONN_REQUIRE_OCSP)
			goto ocsp_error;
		wpa_printf(MSG_DEBUG,
			   "GnuTLS: OCSP was not required, so allow connection to continue");
	}

	return 0;

ocsp_error:
	gnutls_tls_fail_event(conn, NULL, 0, NULL,
			      "bad certificate status response",
			      TLS_FAIL_REVOKED);
	*err = GNUTLS_A_CERTIFICATE_REVOKED;
	return -1;
#else /* GnuTLS 3.1.3 or newer */
	return 0;
#endif /* GnuTLS 3.1.3 or newer */
}