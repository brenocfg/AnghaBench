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
struct tls_connection {int /*<<< orphan*/  ssl_ctx; int /*<<< orphan*/  ssl; } ;
typedef  int /*<<< orphan*/  SSL_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int SSL_CTX_remove_session (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

void tls_connection_remove_session(struct tls_connection *conn)
{
	SSL_SESSION *sess;

	sess = SSL_get_session(conn->ssl);
	if (!sess)
		return;

	if (SSL_CTX_remove_session(conn->ssl_ctx, sess) != 1)
		wpa_printf(MSG_DEBUG,
			   "OpenSSL: Session was not cached");
	else
		wpa_printf(MSG_DEBUG,
			   "OpenSSL: Removed cached session to disable session resumption");
}