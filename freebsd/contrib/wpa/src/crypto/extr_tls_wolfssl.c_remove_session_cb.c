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
typedef  int /*<<< orphan*/  WOLFSSL_SESSION ;
typedef  int /*<<< orphan*/  WOLFSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  tls_ex_idx_session ; 
 struct wpabuf* wolfSSL_SESSION_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_SESSION_set_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,struct wpabuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static void remove_session_cb(WOLFSSL_CTX *ctx, WOLFSSL_SESSION *sess)
{
	struct wpabuf *buf;

	buf = wolfSSL_SESSION_get_ex_data(sess, tls_ex_idx_session);
	if (!buf)
		return;
	wpa_printf(MSG_DEBUG,
		   "wolfSSL: Free application session data %p (sess %p)",
		   buf, sess);
	wpabuf_free(buf);

	wolfSSL_SESSION_set_ex_data(sess, tls_ex_idx_session, NULL);
}