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
typedef  int /*<<< orphan*/  WOLFSSL_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  tls_ex_idx_session ; 
 struct wpabuf* wolfSSL_SESSION_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wolfSSL_SESSION_set_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wpabuf*) ; 
 int /*<<< orphan*/ * wolfSSL_get_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

void tls_connection_set_success_data(struct tls_connection *conn,
				     struct wpabuf *data)
{
	WOLFSSL_SESSION *sess;
	struct wpabuf *old;

	wpa_printf(MSG_DEBUG, "wolfSSL: Set success data");

	sess = wolfSSL_get_session(conn->ssl);
	if (!sess) {
		wpa_printf(MSG_DEBUG,
			   "wolfSSL: No session found for success data");
		goto fail;
	}

	old = wolfSSL_SESSION_get_ex_data(sess, tls_ex_idx_session);
	if (old) {
		wpa_printf(MSG_DEBUG, "wolfSSL: Replacing old success data %p",
			   old);
		wpabuf_free(old);
	}
	if (wolfSSL_SESSION_set_ex_data(sess, tls_ex_idx_session, data) != 1)
		goto fail;

	wpa_printf(MSG_DEBUG, "wolfSSL: Stored success data %p", data);
	conn->success_data = 1;
	return;

fail:
	wpa_printf(MSG_INFO, "wolfSSL: Failed to store success data");
	wpabuf_free(data);
}