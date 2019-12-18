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
struct tls_connection {struct tls_connection* session_ticket; struct tls_connection* check_cert_subject; struct tls_connection* domain_match; struct tls_connection* suffix_match; struct tls_connection* altsubject_match; struct tls_connection* subject_match; int /*<<< orphan*/  ssl; scalar_t__ success_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_quiet_shutdown (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct tls_connection*) ; 
 int /*<<< orphan*/  tls_engine_deinit (struct tls_connection*) ; 

void tls_connection_deinit(void *ssl_ctx, struct tls_connection *conn)
{
	if (conn == NULL)
		return;
	if (conn->success_data) {
		/*
		 * Make sure ssl_clear_bad_session() does not remove this
		 * session.
		 */
		SSL_set_quiet_shutdown(conn->ssl, 1);
		SSL_shutdown(conn->ssl);
	}
	SSL_free(conn->ssl);
	tls_engine_deinit(conn);
	os_free(conn->subject_match);
	os_free(conn->altsubject_match);
	os_free(conn->suffix_match);
	os_free(conn->domain_match);
	os_free(conn->check_cert_subject);
	os_free(conn->session_ticket);
	os_free(conn);
}