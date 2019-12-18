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
struct tls_global {int /*<<< orphan*/  xcred; scalar_t__ params_set; } ;
struct tls_connection {int /*<<< orphan*/  xcred; int /*<<< orphan*/  session; struct tls_global* global; } ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTLS_CRD_CERTIFICATE ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ gnutls_certificate_allocate_credentials (int /*<<< orphan*/ *) ; 
 int gnutls_credentials_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_strerror (int) ; 
 int /*<<< orphan*/  os_free (struct tls_connection*) ; 
 struct tls_connection* os_zalloc (int) ; 
 scalar_t__ tls_gnutls_init_session (struct tls_global*,struct tls_connection*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct tls_connection * tls_connection_init(void *ssl_ctx)
{
	struct tls_global *global = ssl_ctx;
	struct tls_connection *conn;
	int ret;

	conn = os_zalloc(sizeof(*conn));
	if (conn == NULL)
		return NULL;
	conn->global = global;

	if (tls_gnutls_init_session(global, conn)) {
		os_free(conn);
		return NULL;
	}

	if (global->params_set) {
		ret = gnutls_credentials_set(conn->session,
					     GNUTLS_CRD_CERTIFICATE,
					     global->xcred);
		if (ret < 0) {
			wpa_printf(MSG_INFO, "Failed to configure "
				   "credentials: %s", gnutls_strerror(ret));
			os_free(conn);
			return NULL;
		}
	}

	if (gnutls_certificate_allocate_credentials(&conn->xcred)) {
		os_free(conn);
		return NULL;
	}

	return conn;
}