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
typedef  int /*<<< orphan*/  u32 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_method_ret {void* ignore; } ;
struct eap_ikev2_data {scalar_t__ state; scalar_t__ out_used; int /*<<< orphan*/ * out_buf; int /*<<< orphan*/  ikev2; struct wpabuf* in_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_IKEV2 ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FAIL ; 
 int IKEV2_FLAGS_LENGTH_INCLUDED ; 
 int IKEV2_FLAGS_MORE_FRAGMENTS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  PROC_MSG ; 
 void* TRUE ; 
 scalar_t__ WAIT_FRAG_ACK ; 
 int /*<<< orphan*/  WPA_GET_BE32 (int const*) ; 
 int eap_get_id (struct wpabuf const*) ; 
 int* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf const*,size_t*) ; 
 struct wpabuf* eap_ikev2_build_msg (struct eap_ikev2_data*,struct eap_method_ret*,int) ; 
 scalar_t__ eap_ikev2_process_cont (struct eap_ikev2_data*,int const*,int) ; 
 struct wpabuf* eap_ikev2_process_fragment (struct eap_ikev2_data*,struct eap_method_ret*,int,int,int /*<<< orphan*/ ,int const*,int) ; 
 scalar_t__ eap_ikev2_process_icv (struct eap_ikev2_data*,struct wpabuf const*,int,int const*,int const**,int) ; 
 int /*<<< orphan*/  eap_ikev2_state (struct eap_ikev2_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ikev2_responder_build (int /*<<< orphan*/ *) ; 
 scalar_t__ ikev2_responder_process (int /*<<< orphan*/ *,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_set (struct wpabuf*,int const*,int) ; 

__attribute__((used)) static struct wpabuf * eap_ikev2_process(struct eap_sm *sm, void *priv,
					 struct eap_method_ret *ret,
					 const struct wpabuf *reqData)
{
	struct eap_ikev2_data *data = priv;
	const u8 *start, *pos, *end;
	size_t len;
	u8 flags, id;
	u32 message_length = 0;
	struct wpabuf tmpbuf;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_IKEV2, reqData, &len);
	if (pos == NULL) {
		ret->ignore = TRUE;
		return NULL;
	}

	id = eap_get_id(reqData);

	start = pos;
	end = start + len;

	if (len == 0)
		flags = 0; /* fragment ack */
	else
		flags = *pos++;

	if (eap_ikev2_process_icv(data, reqData, flags, pos, &end,
				  data->state == WAIT_FRAG_ACK && len == 0) < 0)
	{
		ret->ignore = TRUE;
		return NULL;
	}

	if (flags & IKEV2_FLAGS_LENGTH_INCLUDED) {
		if (end - pos < 4) {
			wpa_printf(MSG_DEBUG, "EAP-IKEV2: Message underflow");
			ret->ignore = TRUE;
			return NULL;
		}
		message_length = WPA_GET_BE32(pos);
		pos += 4;

		if (message_length < (u32) (end - pos)) {
			wpa_printf(MSG_DEBUG, "EAP-IKEV2: Invalid Message "
				   "Length (%d; %ld remaining in this msg)",
				   message_length, (long) (end - pos));
			ret->ignore = TRUE;
			return NULL;
		}
	}

	wpa_printf(MSG_DEBUG, "EAP-IKEV2: Received packet: Flags 0x%x "
		   "Message Length %u", flags, message_length);

	if (data->state == WAIT_FRAG_ACK) {
		if (len != 0) {
			wpa_printf(MSG_DEBUG, "EAP-IKEV2: Unexpected payload "
				   "in WAIT_FRAG_ACK state");
			ret->ignore = TRUE;
			return NULL;
		}
		wpa_printf(MSG_DEBUG, "EAP-IKEV2: Fragment acknowledged");
		eap_ikev2_state(data, PROC_MSG);
		return eap_ikev2_build_msg(data, ret, id);
	}

	if (data->in_buf && eap_ikev2_process_cont(data, pos, end - pos) < 0) {
		ret->ignore = TRUE;
		return NULL;
	}
		
	if (flags & IKEV2_FLAGS_MORE_FRAGMENTS) {
		return eap_ikev2_process_fragment(data, ret, id, flags,
						  message_length, pos,
						  end - pos);
	}

	if (data->in_buf == NULL) {
		/* Wrap unfragmented messages as wpabuf without extra copy */
		wpabuf_set(&tmpbuf, pos, end - pos);
		data->in_buf = &tmpbuf;
	}

	if (ikev2_responder_process(&data->ikev2, data->in_buf) < 0) {
		if (data->in_buf == &tmpbuf)
			data->in_buf = NULL;
		eap_ikev2_state(data, FAIL);
		return NULL;
	}

	if (data->in_buf != &tmpbuf)
		wpabuf_free(data->in_buf);
	data->in_buf = NULL;

	if (data->out_buf == NULL) {
		data->out_buf = ikev2_responder_build(&data->ikev2);
		if (data->out_buf == NULL) {
			wpa_printf(MSG_DEBUG, "EAP-IKEV2: Failed to generate "
				   "IKEv2 message");
			return NULL;
		}
		data->out_used = 0;
	}

	eap_ikev2_state(data, PROC_MSG);
	return eap_ikev2_build_msg(data, ret, id);
}