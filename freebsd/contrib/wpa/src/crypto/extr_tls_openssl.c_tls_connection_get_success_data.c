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
typedef  int /*<<< orphan*/  SSL_SESSION ;

/* Variables and functions */
 struct wpabuf const* SSL_SESSION_get_ex_data (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * SSL_get_session (int /*<<< orphan*/ ) ; 
 scalar_t__ tls_ex_idx_session ; 

const struct wpabuf *
tls_connection_get_success_data(struct tls_connection *conn)
{
	SSL_SESSION *sess;

	if (tls_ex_idx_session < 0 ||
	    !(sess = SSL_get_session(conn->ssl)))
		return NULL;
	return SSL_SESSION_get_ex_data(sess, tls_ex_idx_session);
}