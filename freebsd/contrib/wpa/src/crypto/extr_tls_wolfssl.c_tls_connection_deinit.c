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
struct tls_connection {struct tls_connection* domain_match; struct tls_connection* suffix_match; struct tls_connection* alt_subject_match; struct tls_connection* subject_match; int /*<<< orphan*/  ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_free (struct tls_connection*) ; 
 int /*<<< orphan*/  wolfSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

void tls_connection_deinit(void *tls_ctx, struct tls_connection *conn)
{
	if (!conn)
		return;

	wpa_printf(MSG_DEBUG, "SSL: connection deinit");

	/* parts */
	wolfSSL_free(conn->ssl);
	os_free(conn->subject_match);
	os_free(conn->alt_subject_match);
	os_free(conn->suffix_match);
	os_free(conn->domain_match);

	/* self */
	os_free(conn);
}