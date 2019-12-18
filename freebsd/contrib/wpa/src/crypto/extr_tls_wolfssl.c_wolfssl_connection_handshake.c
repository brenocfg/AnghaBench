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
struct tls_connection {int /*<<< orphan*/  ssl; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  tls_connection_resumed (int /*<<< orphan*/ *,struct tls_connection*) ; 
 scalar_t__ wolfSSL_is_init_finished (int /*<<< orphan*/ ) ; 
 struct wpabuf* wolfssl_get_appl_data (struct tls_connection*,int /*<<< orphan*/ ) ; 
 struct wpabuf* wolfssl_handshake (struct tls_connection*,struct wpabuf const*,int) ; 
 int /*<<< orphan*/  wolfssl_reset_in_data (int /*<<< orphan*/ *,struct wpabuf const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 

__attribute__((used)) static struct wpabuf *
wolfssl_connection_handshake(struct tls_connection *conn,
			     const struct wpabuf *in_data,
			     struct wpabuf **appl_data, int server)
{
	struct wpabuf *out_data;

	wolfssl_reset_in_data(&conn->input, in_data);

	if (appl_data)
		*appl_data = NULL;

	out_data = wolfssl_handshake(conn, in_data, server);
	if (!out_data)
		return NULL;

	if (wolfSSL_is_init_finished(conn->ssl)) {
		wpa_printf(MSG_DEBUG,
			   "wolfSSL: Handshake finished - resumed=%d",
			   tls_connection_resumed(NULL, conn));
		if (appl_data && in_data)
			*appl_data = wolfssl_get_appl_data(conn,
							   wpabuf_len(in_data));
	}

	return out_data;
}