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
typedef  int u32 ;
struct wpabuf {int dummy; } ;
struct eap_tnc_data {scalar_t__ state; struct wpabuf* in_buf; struct wpabuf* out_buf; int /*<<< orphan*/  tncc; } ;
struct eap_sm {int /*<<< orphan*/  msg_ctx; } ;
struct eap_method_ret {void* allowNotifications; int /*<<< orphan*/  decision; int /*<<< orphan*/  methodState; void* ignore; } ;
typedef  enum tncc_process_res { ____Placeholder_tncc_process_res } tncc_process_res ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_UNCOND_SUCC ; 
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int EAP_TNC_FLAGS_LENGTH_INCLUDED ; 
 int EAP_TNC_FLAGS_MORE_FRAGMENTS ; 
 int EAP_TNC_FLAGS_START ; 
 int EAP_TNC_VERSION ; 
 int EAP_TNC_VERSION_MASK ; 
 int /*<<< orphan*/  EAP_TYPE_TNC ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 void* FALSE ; 
 int /*<<< orphan*/  METHOD_MAY_CONT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 void* PROC_MSG ; 
#define  TNCCS_PROCESS_ERROR 133 
#define  TNCCS_PROCESS_OK_NO_RECOMMENDATION 132 
#define  TNCCS_RECOMMENDATION_ALLOW 131 
#define  TNCCS_RECOMMENDATION_ERROR 130 
#define  TNCCS_RECOMMENDATION_ISOLATE 129 
#define  TNCCS_RECOMMENDATION_NONE 128 
 void* TRUE ; 
 scalar_t__ WAIT_FRAG_ACK ; 
 scalar_t__ WAIT_START ; 
 int WPA_GET_BE32 (int const*) ; 
 int eap_get_id (struct wpabuf const*) ; 
 int* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf const*,size_t*) ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct wpabuf* eap_tnc_build_msg (struct eap_tnc_data*,struct eap_method_ret*,int) ; 
 scalar_t__ eap_tnc_process_cont (struct eap_tnc_data*,int const*,int) ; 
 struct wpabuf* eap_tnc_process_fragment (struct eap_tnc_data*,struct eap_method_ret*,int,int,int,int const*,int) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 size_t os_strlen (char*) ; 
 int* tncc_copy_send_buf (int /*<<< orphan*/ ,int*) ; 
 char* tncc_if_tnccs_end () ; 
 char* tncc_if_tnccs_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tncc_init_connection (int /*<<< orphan*/ ) ; 
 int tncc_process_if_tnccs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t tncc_total_send_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,char*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_set (struct wpabuf*,int const*,int) ; 

__attribute__((used)) static struct wpabuf * eap_tnc_process(struct eap_sm *sm, void *priv,
				       struct eap_method_ret *ret,
				       const struct wpabuf *reqData)
{
	struct eap_tnc_data *data = priv;
	struct wpabuf *resp;
	const u8 *pos, *end;
	u8 *rpos, *rpos1;
	size_t len, rlen;
	size_t imc_len;
	char *start_buf, *end_buf;
	size_t start_len, end_len;
	int tncs_done = 0;
	u8 flags, id;
	u32 message_length = 0;
	struct wpabuf tmpbuf;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_TNC, reqData, &len);
	if (pos == NULL) {
		wpa_printf(MSG_INFO, "EAP-TNC: Invalid frame (pos=%p len=%lu)",
			   pos, (unsigned long) len);
		ret->ignore = TRUE;
		return NULL;
	}

	id = eap_get_id(reqData);

	end = pos + len;

	if (len == 0)
		flags = 0; /* fragment ack */
	else
		flags = *pos++;

	if (len > 0 && (flags & EAP_TNC_VERSION_MASK) != EAP_TNC_VERSION) {
		wpa_printf(MSG_DEBUG, "EAP-TNC: Unsupported version %d",
			   flags & EAP_TNC_VERSION_MASK);
		ret->ignore = TRUE;
		return NULL;
	}

	if (flags & EAP_TNC_FLAGS_LENGTH_INCLUDED) {
		if (end - pos < 4) {
			wpa_printf(MSG_DEBUG, "EAP-TNC: Message underflow");
			ret->ignore = TRUE;
			return NULL;
		}
		message_length = WPA_GET_BE32(pos);
		pos += 4;

		if (message_length < (u32) (end - pos) ||
		    message_length > 75000) {
			wpa_printf(MSG_DEBUG, "EAP-TNC: Invalid Message "
				   "Length (%d; %ld remaining in this msg)",
				   message_length, (long) (end - pos));
			ret->ignore = TRUE;
			return NULL;
		}
	}

	wpa_printf(MSG_DEBUG, "EAP-TNC: Received packet: Flags 0x%x "
		   "Message Length %u", flags, message_length);

	if (data->state == WAIT_FRAG_ACK) {
		if (len > 1) {
			wpa_printf(MSG_DEBUG, "EAP-TNC: Unexpected payload in "
				   "WAIT_FRAG_ACK state");
			ret->ignore = TRUE;
			return NULL;
		}
		wpa_printf(MSG_DEBUG, "EAP-TNC: Fragment acknowledged");
		data->state = PROC_MSG;
		return eap_tnc_build_msg(data, ret, id);
	}

	if (data->in_buf && eap_tnc_process_cont(data, pos, end - pos) < 0) {
		ret->ignore = TRUE;
		return NULL;
	}
		
	if (flags & EAP_TNC_FLAGS_MORE_FRAGMENTS) {
		return eap_tnc_process_fragment(data, ret, id, flags,
						message_length, pos,
						end - pos);
	}

	if (data->in_buf == NULL) {
		/* Wrap unfragmented messages as wpabuf without extra copy */
		wpabuf_set(&tmpbuf, pos, end - pos);
		data->in_buf = &tmpbuf;
	}

	if (data->state == WAIT_START) {
		if (!(flags & EAP_TNC_FLAGS_START)) {
			wpa_printf(MSG_DEBUG, "EAP-TNC: Server did not use "
				   "start flag in the first message");
			ret->ignore = TRUE;
			goto fail;
		}

		tncc_init_connection(data->tncc);

		data->state = PROC_MSG;
	} else {
		enum tncc_process_res res;

		if (flags & EAP_TNC_FLAGS_START) {
			wpa_printf(MSG_DEBUG, "EAP-TNC: Server used start "
				   "flag again");
			ret->ignore = TRUE;
			goto fail;
		}

		res = tncc_process_if_tnccs(data->tncc,
					    wpabuf_head(data->in_buf),
					    wpabuf_len(data->in_buf));
		switch (res) {
		case TNCCS_PROCESS_ERROR:
			ret->ignore = TRUE;
			goto fail;
		case TNCCS_PROCESS_OK_NO_RECOMMENDATION:
		case TNCCS_RECOMMENDATION_ERROR:
			wpa_printf(MSG_DEBUG, "EAP-TNC: No "
				   "TNCCS-Recommendation received");
			break;
		case TNCCS_RECOMMENDATION_ALLOW:
			wpa_msg(sm->msg_ctx, MSG_INFO,
				"TNC: Recommendation = allow");
			tncs_done = 1;
			break;
		case TNCCS_RECOMMENDATION_NONE:
			wpa_msg(sm->msg_ctx, MSG_INFO,
				"TNC: Recommendation = none");
			tncs_done = 1;
			break;
		case TNCCS_RECOMMENDATION_ISOLATE:
			wpa_msg(sm->msg_ctx, MSG_INFO,
				"TNC: Recommendation = isolate");
			tncs_done = 1;
			break;
		}
	}

	if (data->in_buf != &tmpbuf)
		wpabuf_free(data->in_buf);
	data->in_buf = NULL;

	ret->ignore = FALSE;
	ret->methodState = METHOD_MAY_CONT;
	ret->decision = DECISION_UNCOND_SUCC;
	ret->allowNotifications = TRUE;

	if (tncs_done) {
		resp = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_TNC, 1,
				     EAP_CODE_RESPONSE, eap_get_id(reqData));
		if (resp == NULL)
			return NULL;

		wpabuf_put_u8(resp, EAP_TNC_VERSION);
		wpa_printf(MSG_DEBUG, "EAP-TNC: TNCS done - reply with an "
			   "empty ACK message");
		return resp;
	}

	imc_len = tncc_total_send_len(data->tncc);

	start_buf = tncc_if_tnccs_start(data->tncc);
	if (start_buf == NULL)
		return NULL;
	start_len = os_strlen(start_buf);
	end_buf = tncc_if_tnccs_end();
	if (end_buf == NULL) {
		os_free(start_buf);
		return NULL;
	}
	end_len = os_strlen(end_buf);

	rlen = start_len + imc_len + end_len;
	resp = wpabuf_alloc(rlen);
	if (resp == NULL) {
		os_free(start_buf);
		os_free(end_buf);
		return NULL;
	}

	wpabuf_put_data(resp, start_buf, start_len);
	os_free(start_buf);

	rpos1 = wpabuf_put(resp, 0);
	rpos = tncc_copy_send_buf(data->tncc, rpos1);
	wpabuf_put(resp, rpos - rpos1);

	wpabuf_put_data(resp, end_buf, end_len);
	os_free(end_buf);

	wpa_hexdump_ascii(MSG_MSGDUMP, "EAP-TNC: Response",
			  wpabuf_head(resp), wpabuf_len(resp));

	data->out_buf = resp;
	data->state = PROC_MSG;
	return eap_tnc_build_msg(data, ret, id);

fail:
	if (data->in_buf == &tmpbuf)
		data->in_buf = NULL;
	return NULL;
}