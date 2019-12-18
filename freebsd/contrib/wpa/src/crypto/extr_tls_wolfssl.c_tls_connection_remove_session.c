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
struct tls_connection {int /*<<< orphan*/  ssl; } ;
typedef  int /*<<< orphan*/  WOLFSSL_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wolfSSL_SSL_SESSION_set_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wolfSSL_get_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

void tls_connection_remove_session(struct tls_connection *conn)
{
	WOLFSSL_SESSION *sess;

	sess = wolfSSL_get_session(conn->ssl);
	if (!sess)
		return;

	wolfSSL_SSL_SESSION_set_timeout(sess, 0);
	wpa_printf(MSG_DEBUG,
		   "wolfSSL: Removed cached session to disable session resumption");
}