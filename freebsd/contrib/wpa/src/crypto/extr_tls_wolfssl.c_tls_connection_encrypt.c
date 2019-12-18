#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpabuf {int dummy; } ;
struct TYPE_2__ {struct wpabuf* out_data; } ;
struct tls_connection {TYPE_1__ output; int /*<<< orphan*/  ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  wolfSSL_ERR_error_string (int,char*) ; 
 int wolfSSL_get_error (int /*<<< orphan*/ ,int) ; 
 int wolfSSL_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfssl_reset_out_data (TYPE_1__*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 

struct wpabuf * tls_connection_encrypt(void *tls_ctx,
				       struct tls_connection *conn,
				       const struct wpabuf *in_data)
{
	int res;

	if (!conn)
		return NULL;

	wpa_printf(MSG_DEBUG, "SSL: encrypt: %ld bytes", wpabuf_len(in_data));

	wolfssl_reset_out_data(&conn->output);

	res = wolfSSL_write(conn->ssl, wpabuf_head(in_data),
			    wpabuf_len(in_data));
	if (res < 0) {
		int  err = wolfSSL_get_error(conn->ssl, res);
		char msg[80];

		wpa_printf(MSG_INFO, "Encryption failed - SSL_write: %s",
			   wolfSSL_ERR_error_string(err, msg));
		return NULL;
	}

	return conn->output.out_data;
}