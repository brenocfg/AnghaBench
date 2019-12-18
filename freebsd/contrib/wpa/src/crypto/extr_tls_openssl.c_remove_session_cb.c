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
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct wpabuf* SSL_SESSION_get_ex_data (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SSL_SESSION_set_ex_data (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ tls_ex_idx_session ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,struct wpabuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static void remove_session_cb(SSL_CTX *ctx, SSL_SESSION *sess)
{
	struct wpabuf *buf;

	if (tls_ex_idx_session < 0)
		return;
	buf = SSL_SESSION_get_ex_data(sess, tls_ex_idx_session);
	if (!buf)
		return;
	wpa_printf(MSG_DEBUG,
		   "OpenSSL: Free application session data %p (sess %p)",
		   buf, sess);
	wpabuf_free(buf);

	SSL_SESSION_set_ex_data(sess, tls_ex_idx_session, NULL);
}