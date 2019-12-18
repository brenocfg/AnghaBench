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
struct eap_sm {scalar_t__ const* identity; scalar_t__ identity_len; int /*<<< orphan*/  ssl_ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct eap_peap_data {scalar_t__ state; TYPE_1__ ssl; } ;

/* Variables and functions */
 scalar_t__ const EAP_TYPE_PEAP ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ SUCCESS_REQ ; 
 int /*<<< orphan*/  eap_peap_process_msg ; 
 int /*<<< orphan*/  eap_peap_process_version ; 
 int /*<<< orphan*/  eap_peap_req_success (struct eap_sm*,struct eap_peap_data*) ; 
 int /*<<< orphan*/  eap_peap_state (struct eap_peap_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_server_tls_process (struct eap_sm*,TYPE_1__*,struct wpabuf*,struct eap_peap_data*,scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_user_get (struct eap_sm*,scalar_t__ const*,scalar_t__,int) ; 
 int /*<<< orphan*/  os_free (scalar_t__ const*) ; 
 scalar_t__ const* os_malloc (scalar_t__) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__ const*,scalar_t__ const*,scalar_t__) ; 
 int /*<<< orphan*/  tls_connection_established (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wpabuf* tls_connection_get_success_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_connection_resumed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_connection_set_success_data_resumed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,scalar_t__ const*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__* wpabuf_head (struct wpabuf const*) ; 
 int wpabuf_len (struct wpabuf const*) ; 

__attribute__((used)) static void eap_peap_process(struct eap_sm *sm, void *priv,
			     struct wpabuf *respData)
{
	struct eap_peap_data *data = priv;
	const struct wpabuf *buf;
	const u8 *pos;
	u8 id_len;

	if (eap_server_tls_process(sm, &data->ssl, respData, data,
				   EAP_TYPE_PEAP, eap_peap_process_version,
				   eap_peap_process_msg) < 0) {
		eap_peap_state(data, FAILURE);
		return;
	}

	if (data->state == SUCCESS ||
	    !tls_connection_established(sm->ssl_ctx, data->ssl.conn) ||
	    !tls_connection_resumed(sm->ssl_ctx, data->ssl.conn))
		return;

	buf = tls_connection_get_success_data(data->ssl.conn);
	if (!buf || wpabuf_len(buf) < 2) {
		wpa_printf(MSG_DEBUG,
			   "EAP-PEAP: No success data in resumed session - reject attempt");
		eap_peap_state(data, FAILURE);
		return;
	}

	pos = wpabuf_head(buf);
	if (*pos != EAP_TYPE_PEAP) {
		wpa_printf(MSG_DEBUG,
			   "EAP-PEAP: Resumed session for another EAP type (%u) - reject attempt",
			   *pos);
		eap_peap_state(data, FAILURE);
		return;
	}

	pos++;
	id_len = *pos++;
	wpa_hexdump_ascii(MSG_DEBUG, "EAP-PEAP: Identity from cached session",
			  pos, id_len);
	os_free(sm->identity);
	sm->identity = os_malloc(id_len ? id_len : 1);
	if (!sm->identity) {
		sm->identity_len = 0;
		eap_peap_state(data, FAILURE);
		return;
	}

	os_memcpy(sm->identity, pos, id_len);
	sm->identity_len = id_len;

	if (eap_user_get(sm, sm->identity, sm->identity_len, 1) != 0) {
		wpa_hexdump_ascii(MSG_DEBUG, "EAP-PEAP: Phase2 Identity not found in the user database",
				  sm->identity, sm->identity_len);
		eap_peap_state(data, FAILURE);
		return;
	}

	wpa_printf(MSG_DEBUG,
		   "EAP-PEAP: Resuming previous session - skip Phase2");
	eap_peap_req_success(sm, data);
	if (data->state == SUCCESS_REQ)
		tls_connection_set_success_data_resumed(data->ssl.conn);
}