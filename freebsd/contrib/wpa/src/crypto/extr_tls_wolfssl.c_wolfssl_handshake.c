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
struct wpabuf {int dummy; } ;
struct TYPE_2__ {struct wpabuf* out_data; } ;
struct tls_connection {TYPE_1__ output; int /*<<< orphan*/  failed; int /*<<< orphan*/  ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int SSL_ERROR_WANT_READ ; 
 int SSL_ERROR_WANT_WRITE ; 
 int wolfSSL_ERR_error_string (int,char*) ; 
 int wolfSSL_accept (int /*<<< orphan*/ ) ; 
 int wolfSSL_connect (int /*<<< orphan*/ ) ; 
 int wolfSSL_get_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wolfSSL_set_accept_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_set_connect_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfssl_reset_out_data (TYPE_1__*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct wpabuf * wolfssl_handshake(struct tls_connection *conn,
					 const struct wpabuf *in_data,
					 int server)
{
	int res;

	wolfssl_reset_out_data(&conn->output);

	/* Initiate TLS handshake or continue the existing handshake */
	if (server) {
		wolfSSL_set_accept_state(conn->ssl);
		res = wolfSSL_accept(conn->ssl);
		wpa_printf(MSG_DEBUG, "SSL: wolfSSL_accept: %d", res);
	} else {
		wolfSSL_set_connect_state(conn->ssl);
		res = wolfSSL_connect(conn->ssl);
		wpa_printf(MSG_DEBUG, "SSL: wolfSSL_connect: %d", res);
	}

	if (res != 1) {
		int err = wolfSSL_get_error(conn->ssl, res);

		if (err == SSL_ERROR_WANT_READ) {
			wpa_printf(MSG_DEBUG,
				   "SSL: wolfSSL_connect - want more data");
		} else if (err == SSL_ERROR_WANT_WRITE) {
			wpa_printf(MSG_DEBUG,
				   "SSL: wolfSSL_connect - want to write");
		} else {
			char msg[80];

			wpa_printf(MSG_DEBUG,
				   "SSL: wolfSSL_connect - failed %s",
				   wolfSSL_ERR_error_string(err, msg));
			conn->failed++;
		}
	}

	return conn->output.out_data;
}