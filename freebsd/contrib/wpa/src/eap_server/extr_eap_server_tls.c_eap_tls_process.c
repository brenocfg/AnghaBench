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
typedef  scalar_t__ u8 ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct eap_tls_data {scalar_t__ const eap_type; TYPE_1__ ssl; } ;
struct eap_sm {int /*<<< orphan*/  ssl_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SUCCESS ; 
 scalar_t__ eap_server_tls_process (struct eap_sm*,TYPE_1__*,struct wpabuf*,struct eap_tls_data*,scalar_t__ const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_tls_process_msg ; 
 int /*<<< orphan*/  eap_tls_state (struct eap_tls_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_connection_established (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wpabuf* tls_connection_get_success_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_connection_resumed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_connection_set_success_data_resumed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__* wpabuf_head (struct wpabuf const*) ; 
 int wpabuf_len (struct wpabuf const*) ; 

__attribute__((used)) static void eap_tls_process(struct eap_sm *sm, void *priv,
			    struct wpabuf *respData)
{
	struct eap_tls_data *data = priv;
	const struct wpabuf *buf;
	const u8 *pos;

	if (eap_server_tls_process(sm, &data->ssl, respData, data,
				   data->eap_type, NULL, eap_tls_process_msg) <
	    0) {
		eap_tls_state(data, FAILURE);
		return;
	}

	if (!tls_connection_established(sm->ssl_ctx, data->ssl.conn) ||
	    !tls_connection_resumed(sm->ssl_ctx, data->ssl.conn))
		return;

	buf = tls_connection_get_success_data(data->ssl.conn);
	if (!buf || wpabuf_len(buf) < 1) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TLS: No success data in resumed session - reject attempt");
		eap_tls_state(data, FAILURE);
		return;
	}

	pos = wpabuf_head(buf);
	if (*pos != data->eap_type) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TLS: Resumed session for another EAP type (%u) - reject attempt",
			   *pos);
		eap_tls_state(data, FAILURE);
		return;
	}

	wpa_printf(MSG_DEBUG,
		   "EAP-TLS: Resuming previous session");
	eap_tls_state(data, SUCCESS);
	tls_connection_set_success_data_resumed(data->ssl.conn);
	/* TODO: Cache serial number with session and update EAP user
	 * information based on the cached serial number */
}