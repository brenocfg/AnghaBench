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
struct eap_ssl_data {int tls_v13; int /*<<< orphan*/  conn; int /*<<< orphan*/ * tls_out; int /*<<< orphan*/  tls_in; } ;
struct eap_sm {int /*<<< orphan*/  ssl_ctx; scalar_t__ serial_num; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WPA_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 scalar_t__ tls_connection_established (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tls_connection_get_failed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tls_connection_peer_serial_num (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tls_connection_server_handshake (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ tls_get_version (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

int eap_server_tls_phase1(struct eap_sm *sm, struct eap_ssl_data *data)
{
	char buf[20];

	if (data->tls_out) {
		/* This should not happen.. */
		wpa_printf(MSG_INFO, "SSL: pending tls_out data when "
			   "processing new message");
		wpabuf_free(data->tls_out);
		WPA_ASSERT(data->tls_out == NULL);
	}

	data->tls_out = tls_connection_server_handshake(sm->ssl_ctx,
							data->conn,
							data->tls_in, NULL);
	if (data->tls_out == NULL) {
		wpa_printf(MSG_INFO, "SSL: TLS processing failed");
		return -1;
	}
	if (tls_connection_get_failed(sm->ssl_ctx, data->conn)) {
		/* TLS processing has failed - return error */
		wpa_printf(MSG_DEBUG, "SSL: Failed - tls_out available to "
			   "report error");
		return -1;
	}

	if (tls_get_version(sm->ssl_ctx, data->conn, buf, sizeof(buf)) == 0) {
		wpa_printf(MSG_DEBUG, "SSL: Using TLS version %s", buf);
		data->tls_v13 = os_strcmp(buf, "TLSv1.3") == 0;
	}

	if (!sm->serial_num &&
	    tls_connection_established(sm->ssl_ctx, data->conn))
		sm->serial_num = tls_connection_peer_serial_num(sm->ssl_ctx,
								data->conn);

	return 0;
}