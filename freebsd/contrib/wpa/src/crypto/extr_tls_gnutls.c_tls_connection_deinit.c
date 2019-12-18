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
struct tls_connection {struct tls_connection* domain_match; struct tls_connection* suffix_match; int /*<<< orphan*/  pull_buf; int /*<<< orphan*/  push_buf; struct tls_connection* pre_shared_secret; int /*<<< orphan*/  session; int /*<<< orphan*/  xcred; } ;

/* Variables and functions */
 int /*<<< orphan*/  gnutls_certificate_free_credentials (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct tls_connection*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void tls_connection_deinit(void *ssl_ctx, struct tls_connection *conn)
{
	if (conn == NULL)
		return;

	gnutls_certificate_free_credentials(conn->xcred);
	gnutls_deinit(conn->session);
	os_free(conn->pre_shared_secret);
	wpabuf_free(conn->push_buf);
	wpabuf_free(conn->pull_buf);
	os_free(conn->suffix_match);
	os_free(conn->domain_match);
	os_free(conn);
}