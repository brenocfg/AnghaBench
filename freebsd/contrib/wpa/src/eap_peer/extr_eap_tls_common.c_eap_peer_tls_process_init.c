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
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct eap_ssl_data {unsigned int tls_in_left; unsigned int tls_in_total; int /*<<< orphan*/ * tls_in; int /*<<< orphan*/  ssl_ctx; } ;
struct eap_sm {int /*<<< orphan*/  workaround; } ;
struct eap_method_ret {void* allowNotifications; int /*<<< orphan*/  decision; int /*<<< orphan*/  methodState; void* ignore; } ;
typedef  scalar_t__ EapType ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAIL ; 
 int EAP_TLS_FLAGS_LENGTH_INCLUDED ; 
 scalar_t__ EAP_UNAUTH_TLS_TYPE ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 scalar_t__ EAP_VENDOR_TYPE_UNAUTH_TLS ; 
 int /*<<< orphan*/  EAP_VENDOR_UNAUTH_TLS ; 
 int /*<<< orphan*/  EAP_VENDOR_WFA_NEW ; 
 scalar_t__ EAP_VENDOR_WFA_UNAUTH_TLS ; 
 scalar_t__ EAP_WFA_UNAUTH_TLS_TYPE ; 
 void* FALSE ; 
 int /*<<< orphan*/  METHOD_MAY_CONT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 void* TRUE ; 
 unsigned int WPA_GET_BE32 (int const*) ; 
 int* eap_hdr_validate (int /*<<< orphan*/ ,scalar_t__,struct wpabuf const*,size_t*) ; 
 scalar_t__ tls_get_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 
 scalar_t__ wpabuf_len (struct wpabuf const*) ; 

const u8 * eap_peer_tls_process_init(struct eap_sm *sm,
				     struct eap_ssl_data *data,
				     EapType eap_type,
				     struct eap_method_ret *ret,
				     const struct wpabuf *reqData,
				     size_t *len, u8 *flags)
{
	const u8 *pos;
	size_t left;
	unsigned int tls_msg_len;

	if (tls_get_errors(data->ssl_ctx)) {
		wpa_printf(MSG_INFO, "SSL: TLS errors detected");
		ret->ignore = TRUE;
		return NULL;
	}

	if (eap_type == EAP_UNAUTH_TLS_TYPE)
		pos = eap_hdr_validate(EAP_VENDOR_UNAUTH_TLS,
				       EAP_VENDOR_TYPE_UNAUTH_TLS, reqData,
				       &left);
	else if (eap_type == EAP_WFA_UNAUTH_TLS_TYPE)
		pos = eap_hdr_validate(EAP_VENDOR_WFA_NEW,
				       EAP_VENDOR_WFA_UNAUTH_TLS, reqData,
				       &left);
	else
		pos = eap_hdr_validate(EAP_VENDOR_IETF, eap_type, reqData,
				       &left);
	if (pos == NULL) {
		ret->ignore = TRUE;
		return NULL;
	}
	if (left == 0) {
		wpa_printf(MSG_DEBUG, "SSL: Invalid TLS message: no Flags "
			   "octet included");
		if (!sm->workaround) {
			ret->ignore = TRUE;
			return NULL;
		}

		wpa_printf(MSG_DEBUG, "SSL: Workaround - assume no Flags "
			   "indicates ACK frame");
		*flags = 0;
	} else {
		*flags = *pos++;
		left--;
	}
	wpa_printf(MSG_DEBUG, "SSL: Received packet(len=%lu) - "
		   "Flags 0x%02x", (unsigned long) wpabuf_len(reqData),
		   *flags);
	if (*flags & EAP_TLS_FLAGS_LENGTH_INCLUDED) {
		if (left < 4) {
			wpa_printf(MSG_INFO, "SSL: Short frame with TLS "
				   "length");
			ret->ignore = TRUE;
			return NULL;
		}
		tls_msg_len = WPA_GET_BE32(pos);
		wpa_printf(MSG_DEBUG, "SSL: TLS Message Length: %d",
			   tls_msg_len);
		if (data->tls_in_left == 0) {
			data->tls_in_total = tls_msg_len;
			data->tls_in_left = tls_msg_len;
			wpabuf_free(data->tls_in);
			data->tls_in = NULL;
		}
		pos += 4;
		left -= 4;

		if (left > tls_msg_len) {
			wpa_printf(MSG_INFO, "SSL: TLS Message Length (%d "
				   "bytes) smaller than this fragment (%d "
				   "bytes)", (int) tls_msg_len, (int) left);
			ret->ignore = TRUE;
			return NULL;
		}
	}

	ret->ignore = FALSE;
	ret->methodState = METHOD_MAY_CONT;
	ret->decision = DECISION_FAIL;
	ret->allowNotifications = TRUE;

	*len = left;
	return pos;
}