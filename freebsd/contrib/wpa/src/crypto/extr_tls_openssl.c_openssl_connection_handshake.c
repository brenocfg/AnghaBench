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
struct wpabuf {int dummy; } ;
struct tls_connection {scalar_t__ invalid_hb_used; int /*<<< orphan*/  ssl; scalar_t__ server; int /*<<< orphan*/  ssl_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ SSL_get_shared_ciphers (int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ SSL_is_init_finished (int /*<<< orphan*/ ) ; 
 struct wpabuf* openssl_get_appl_data (struct tls_connection*,int /*<<< orphan*/ ) ; 
 struct wpabuf* openssl_handshake (struct tls_connection*,struct wpabuf const*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  tls_connection_resumed (int /*<<< orphan*/ ,struct tls_connection*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 

__attribute__((used)) static struct wpabuf *
openssl_connection_handshake(struct tls_connection *conn,
			     const struct wpabuf *in_data,
			     struct wpabuf **appl_data)
{
	struct wpabuf *out_data;

	if (appl_data)
		*appl_data = NULL;

	out_data = openssl_handshake(conn, in_data);
	if (out_data == NULL)
		return NULL;
	if (conn->invalid_hb_used) {
		wpa_printf(MSG_INFO, "TLS: Heartbeat attack detected - do not send response");
		wpabuf_free(out_data);
		return NULL;
	}

	if (SSL_is_init_finished(conn->ssl)) {
		wpa_printf(MSG_DEBUG,
			   "OpenSSL: Handshake finished - resumed=%d",
			   tls_connection_resumed(conn->ssl_ctx, conn));
		if (conn->server) {
			char *buf;
			size_t buflen = 2000;

			buf = os_malloc(buflen);
			if (buf) {
				if (SSL_get_shared_ciphers(conn->ssl, buf,
							   buflen)) {
					buf[buflen - 1] = '\0';
					wpa_printf(MSG_DEBUG,
						   "OpenSSL: Shared ciphers: %s",
						   buf);
				}
				os_free(buf);
			}
		}
		if (appl_data && in_data)
			*appl_data = openssl_get_appl_data(conn,
							   wpabuf_len(in_data));
	}

	if (conn->invalid_hb_used) {
		wpa_printf(MSG_INFO, "TLS: Heartbeat attack detected - do not send response");
		if (appl_data) {
			wpabuf_free(*appl_data);
			*appl_data = NULL;
		}
		wpabuf_free(out_data);
		return NULL;
	}

	return out_data;
}