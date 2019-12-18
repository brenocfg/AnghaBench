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
struct tls_global {int /*<<< orphan*/  session_data_size; scalar_t__ session_data; int /*<<< orphan*/  xcred; } ;
struct tls_connection {int /*<<< orphan*/  session; int /*<<< orphan*/  xcred; scalar_t__ params_set; scalar_t__ established; int /*<<< orphan*/ * push_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTLS_CRD_CERTIFICATE ; 
 int /*<<< orphan*/  GNUTLS_SHUT_RDWR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  gnutls_bye (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gnutls_credentials_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_deinit (int /*<<< orphan*/ ) ; 
 int gnutls_session_set_data (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_strerror (int) ; 
 scalar_t__ tls_gnutls_init_session (struct tls_global*,struct tls_connection*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

int tls_connection_shutdown(void *ssl_ctx, struct tls_connection *conn)
{
	struct tls_global *global = ssl_ctx;
	int ret;

	if (conn == NULL)
		return -1;

	/* Shutdown previous TLS connection without notifying the peer
	 * because the connection was already terminated in practice
	 * and "close notify" shutdown alert would confuse AS. */
	gnutls_bye(conn->session, GNUTLS_SHUT_RDWR);
	wpabuf_free(conn->push_buf);
	conn->push_buf = NULL;
	conn->established = 0;

	gnutls_deinit(conn->session);
	if (tls_gnutls_init_session(global, conn)) {
		wpa_printf(MSG_INFO, "GnuTLS: Failed to preparare new session "
			   "for session resumption use");
		return -1;
	}

	ret = gnutls_credentials_set(conn->session, GNUTLS_CRD_CERTIFICATE,
				     conn->params_set ? conn->xcred :
				     global->xcred);
	if (ret < 0) {
		wpa_printf(MSG_INFO, "GnuTLS: Failed to configure credentials "
			   "for session resumption: %s", gnutls_strerror(ret));
		return -1;
	}

	if (global->session_data) {
		ret = gnutls_session_set_data(conn->session,
					      global->session_data,
					      global->session_data_size);
		if (ret < 0) {
			wpa_printf(MSG_INFO, "GnuTLS: Failed to set session "
				   "data: %s", gnutls_strerror(ret));
			return -1;
		}
	}

	return 0;
}