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
struct tls_connection {int success_data; int /*<<< orphan*/  ssl; } ;
typedef  int /*<<< orphan*/  SSL_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 struct wpabuf* SSL_SESSION_get_ex_data (int /*<<< orphan*/ *,scalar_t__) ; 
 int SSL_SESSION_set_ex_data (int /*<<< orphan*/ *,scalar_t__,struct wpabuf*) ; 
 int /*<<< orphan*/ * SSL_get_session (int /*<<< orphan*/ ) ; 
 scalar_t__ tls_ex_idx_session ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

void tls_connection_set_success_data(struct tls_connection *conn,
				     struct wpabuf *data)
{
	SSL_SESSION *sess;
	struct wpabuf *old;

	if (tls_ex_idx_session < 0)
		goto fail;
	sess = SSL_get_session(conn->ssl);
	if (!sess)
		goto fail;
	old = SSL_SESSION_get_ex_data(sess, tls_ex_idx_session);
	if (old) {
		wpa_printf(MSG_DEBUG, "OpenSSL: Replacing old success data %p",
			   old);
		wpabuf_free(old);
	}
	if (SSL_SESSION_set_ex_data(sess, tls_ex_idx_session, data) != 1)
		goto fail;

	wpa_printf(MSG_DEBUG, "OpenSSL: Stored success data %p", data);
	conn->success_data = 1;
	return;

fail:
	wpa_printf(MSG_INFO, "OpenSSL: Failed to store success data");
	wpabuf_free(data);
}