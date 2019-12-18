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
typedef  struct wpabuf const wpabuf ;
struct tls_connection {int /*<<< orphan*/  ssl; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int wolfSSL_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfssl_reset_in_data (int /*<<< orphan*/ *,struct wpabuf const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf const* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_mhead (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_put (struct wpabuf const*,int) ; 
 int /*<<< orphan*/  wpabuf_size (struct wpabuf const*) ; 

struct wpabuf * tls_connection_decrypt(void *tls_ctx,
				       struct tls_connection *conn,
				       const struct wpabuf *in_data)
{
	int res;
	struct wpabuf *buf;

	if (!conn)
		return NULL;

	wpa_printf(MSG_DEBUG, "SSL: decrypt");

	wolfssl_reset_in_data(&conn->input, in_data);

	/* Read decrypted data for further processing */
	/*
	 * Even though we try to disable TLS compression, it is possible that
	 * this cannot be done with all TLS libraries. Add extra buffer space
	 * to handle the possibility of the decrypted data being longer than
	 * input data.
	 */
	buf = wpabuf_alloc((wpabuf_len(in_data) + 500) * 3);
	if (!buf)
		return NULL;
	res = wolfSSL_read(conn->ssl, wpabuf_mhead(buf), wpabuf_size(buf));
	if (res < 0) {
		wpa_printf(MSG_INFO, "Decryption failed - SSL_read");
		wpabuf_free(buf);
		return NULL;
	}
	wpabuf_put(buf, res);

	wpa_printf(MSG_DEBUG, "SSL: decrypt: %ld bytes", wpabuf_len(buf));

	return buf;
}