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
struct tls_connection {int /*<<< orphan*/  ssl; } ;
typedef  int /*<<< orphan*/  WOLFSSL_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  tls_ex_idx_session ; 
 struct wpabuf const* wolfSSL_SESSION_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wolfSSL_get_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

const struct wpabuf *
tls_connection_get_success_data(struct tls_connection *conn)
{
	WOLFSSL_SESSION *sess;

	wpa_printf(MSG_DEBUG, "wolfSSL: Get success data");

	sess = wolfSSL_get_session(conn->ssl);
	if (!sess)
		return NULL;
	return wolfSSL_SESSION_get_ex_data(sess, tls_ex_idx_session);
}