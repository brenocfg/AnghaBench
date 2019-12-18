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
struct tls_global {scalar_t__ server; } ;
struct tls_connection {int /*<<< orphan*/  session; } ;
typedef  int /*<<< orphan*/  gnutls_transport_ptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTLS_CLIENT ; 
 int /*<<< orphan*/  GNUTLS_SERVER ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  gnutls_deinit (int /*<<< orphan*/ ) ; 
 int gnutls_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gnutls_priority_set_direct (int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  gnutls_session_set_ptr (int /*<<< orphan*/ ,struct tls_connection*) ; 
 int gnutls_set_default_priority (int /*<<< orphan*/ ) ; 
 char const* gnutls_strerror (int) ; 
 int /*<<< orphan*/  gnutls_transport_set_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_transport_set_pull_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_transport_set_push_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_pull_func ; 
 int /*<<< orphan*/  tls_push_func ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int tls_gnutls_init_session(struct tls_global *global,
				   struct tls_connection *conn)
{
	const char *err;
	int ret;

	ret = gnutls_init(&conn->session,
			  global->server ? GNUTLS_SERVER : GNUTLS_CLIENT);
	if (ret < 0) {
		wpa_printf(MSG_INFO, "TLS: Failed to initialize new TLS "
			   "connection: %s", gnutls_strerror(ret));
		return -1;
	}

	ret = gnutls_set_default_priority(conn->session);
	if (ret < 0)
		goto fail;

	ret = gnutls_priority_set_direct(conn->session, "NORMAL:-VERS-SSL3.0",
					 &err);
	if (ret < 0) {
		wpa_printf(MSG_ERROR, "GnuTLS: Priority string failure at "
			   "'%s'", err);
		goto fail;
	}

	gnutls_transport_set_pull_function(conn->session, tls_pull_func);
	gnutls_transport_set_push_function(conn->session, tls_push_func);
	gnutls_transport_set_ptr(conn->session, (gnutls_transport_ptr_t) conn);
	gnutls_session_set_ptr(conn->session, conn);

	return 0;

fail:
	wpa_printf(MSG_INFO, "TLS: Failed to setup new TLS connection: %s",
		   gnutls_strerror(ret));
	gnutls_deinit(conn->session);
	return -1;
}