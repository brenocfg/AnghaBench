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
struct eap_ttls_data {TYPE_1__ ssl; } ;
struct eap_sm {scalar_t__ const* identity; scalar_t__ identity_len; int /*<<< orphan*/  ssl_ctx; } ;

/* Variables and functions */
 scalar_t__ const EAP_TYPE_TTLS ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SUCCESS ; 
 scalar_t__ eap_server_tls_process (struct eap_sm*,TYPE_1__*,struct wpabuf*,struct eap_ttls_data*,scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_ttls_process_msg ; 
 int /*<<< orphan*/  eap_ttls_process_version ; 
 int /*<<< orphan*/  eap_ttls_state (struct eap_ttls_data*,int /*<<< orphan*/ ) ; 
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

__attribute__((used)) static void eap_ttls_process(struct eap_sm *sm, void *priv,
			     struct wpabuf *respData)
{
	struct eap_ttls_data *data = priv;
	const struct wpabuf *buf;
	const u8 *pos;
	u8 id_len;

	if (eap_server_tls_process(sm, &data->ssl, respData, data,
				   EAP_TYPE_TTLS, eap_ttls_process_version,
				   eap_ttls_process_msg) < 0) {
		eap_ttls_state(data, FAILURE);
		return;
	}

	if (!tls_connection_established(sm->ssl_ctx, data->ssl.conn) ||
	    !tls_connection_resumed(sm->ssl_ctx, data->ssl.conn))
		return;

	buf = tls_connection_get_success_data(data->ssl.conn);
	if (!buf || wpabuf_len(buf) < 1) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TTLS: No success data in resumed session - reject attempt");
		eap_ttls_state(data, FAILURE);
		return;
	}

	pos = wpabuf_head(buf);
	if (*pos != EAP_TYPE_TTLS) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TTLS: Resumed session for another EAP type (%u) - reject attempt",
			   *pos);
		eap_ttls_state(data, FAILURE);
		return;
	}

	pos++;
	id_len = *pos++;
	wpa_hexdump_ascii(MSG_DEBUG, "EAP-TTLS: Identity from cached session",
			  pos, id_len);
	os_free(sm->identity);
	sm->identity = os_malloc(id_len ? id_len : 1);
	if (!sm->identity) {
		sm->identity_len = 0;
		eap_ttls_state(data, FAILURE);
		return;
	}

	os_memcpy(sm->identity, pos, id_len);
	sm->identity_len = id_len;

	if (eap_user_get(sm, sm->identity, sm->identity_len, 1) != 0) {
		wpa_hexdump_ascii(MSG_DEBUG, "EAP-TTLS: Phase2 Identity not found in the user database",
				  sm->identity, sm->identity_len);
		eap_ttls_state(data, FAILURE);
		return;
	}

	wpa_printf(MSG_DEBUG,
		   "EAP-TTLS: Resuming previous session - skip Phase2");
	eap_ttls_state(data, SUCCESS);
	tls_connection_set_success_data_resumed(data->ssl.conn);
}