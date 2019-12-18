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
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct eap_ttls_data {int /*<<< orphan*/  ttls_version; int /*<<< orphan*/  resuming; TYPE_1__ ssl; } ;
struct eap_sm {int /*<<< orphan*/  ssl_ctx; } ;
struct eap_method_ret {int dummy; } ;

/* Variables and functions */
 int EAP_TLS_FLAGS_START ; 
 int EAP_TLS_VERSION_MASK ; 
 int /*<<< orphan*/  EAP_TYPE_TTLS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int eap_get_id (struct wpabuf const*) ; 
 struct wpabuf* eap_peer_tls_build_ack (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* eap_peer_tls_process_init (struct eap_sm*,TYPE_1__*,int /*<<< orphan*/ ,struct eap_method_ret*,struct wpabuf const*,size_t*,int*) ; 
 int /*<<< orphan*/  eap_ttls_check_auth_status (struct eap_sm*,struct eap_ttls_data*,struct eap_method_ret*) ; 
 int eap_ttls_decrypt (struct eap_sm*,struct eap_ttls_data*,struct eap_method_ret*,int,struct wpabuf*,struct wpabuf**) ; 
 int eap_ttls_process_handshake (struct eap_sm*,struct eap_ttls_data*,struct eap_method_ret*,int,struct wpabuf*,struct wpabuf**) ; 
 scalar_t__ tls_connection_established (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_clear_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_set (struct wpabuf*,int const*,size_t) ; 

__attribute__((used)) static struct wpabuf * eap_ttls_process(struct eap_sm *sm, void *priv,
					struct eap_method_ret *ret,
					const struct wpabuf *reqData)
{
	size_t left;
	int res;
	u8 flags, id;
	struct wpabuf *resp;
	const u8 *pos;
	struct eap_ttls_data *data = priv;
	struct wpabuf msg;

	pos = eap_peer_tls_process_init(sm, &data->ssl, EAP_TYPE_TTLS, ret,
					reqData, &left, &flags);
	if (pos == NULL)
		return NULL;
	id = eap_get_id(reqData);

	if (flags & EAP_TLS_FLAGS_START) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS: Start (server ver=%d, own "
			   "ver=%d)", flags & EAP_TLS_VERSION_MASK,
			   data->ttls_version);

		/* RFC 5281, Ch. 9.2:
		 * "This packet MAY contain additional information in the form
		 * of AVPs, which may provide useful hints to the client"
		 * For now, ignore any potential extra data.
		 */
		left = 0;
	}

	wpabuf_set(&msg, pos, left);

	resp = NULL;
	if (tls_connection_established(sm->ssl_ctx, data->ssl.conn) &&
	    !data->resuming) {
		res = eap_ttls_decrypt(sm, data, ret, id, &msg, &resp);
	} else {
		res = eap_ttls_process_handshake(sm, data, ret, id,
						 &msg, &resp);
	}

	eap_ttls_check_auth_status(sm, data, ret);

	/* FIX: what about res == -1? Could just move all error processing into
	 * the other functions and get rid of this res==1 case here. */
	if (res == 1) {
		wpabuf_clear_free(resp);
		return eap_peer_tls_build_ack(id, EAP_TYPE_TTLS,
					      data->ttls_version);
	}
	return resp;
}