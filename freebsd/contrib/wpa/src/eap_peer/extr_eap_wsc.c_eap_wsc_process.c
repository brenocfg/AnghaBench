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
typedef  int u16 ;
struct wpabuf {int dummy; } ;
struct eap_wsc_data {scalar_t__ state; scalar_t__ out_used; int /*<<< orphan*/ * out_buf; int /*<<< orphan*/  out_op_code; int /*<<< orphan*/  wps; struct wpabuf* in_buf; } ;
struct eap_sm {int ClientTimeout; } ;
struct eap_method_ret {scalar_t__ methodState; int /*<<< orphan*/  decision; void* ignore; } ;
typedef  enum wps_process_res { ____Placeholder_wps_process_res } wps_process_res ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAIL ; 
 int /*<<< orphan*/  EAP_VENDOR_TYPE_WSC ; 
 int /*<<< orphan*/  EAP_VENDOR_WFA ; 
 scalar_t__ FAIL ; 
 scalar_t__ MESG ; 
 scalar_t__ METHOD_DONE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 void* TRUE ; 
 scalar_t__ WAIT_FRAG_ACK ; 
 scalar_t__ WAIT_START ; 
 int WPA_GET_BE16 (int const*) ; 
#define  WPS_CONTINUE 131 
#define  WPS_DONE 130 
#define  WPS_FAILURE 129 
#define  WPS_PENDING 128 
 int WSC_ACK ; 
 int WSC_Done ; 
 int WSC_FLAGS_LF ; 
 int WSC_FLAGS_MF ; 
 int WSC_FRAG_ACK ; 
 int WSC_MSG ; 
 int WSC_NACK ; 
 int WSC_Start ; 
 int eap_get_id (struct wpabuf const*) ; 
 int* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf const*,size_t*) ; 
 struct wpabuf* eap_wsc_build_msg (struct eap_wsc_data*,struct eap_method_ret*,int) ; 
 scalar_t__ eap_wsc_process_cont (struct eap_wsc_data*,int const*,int,int) ; 
 struct wpabuf* eap_wsc_process_fragment (struct eap_wsc_data*,struct eap_method_ret*,int,int,int,int,int const*,int) ; 
 int /*<<< orphan*/  eap_wsc_state (struct eap_wsc_data*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_set (struct wpabuf*,int const*,int) ; 
 int /*<<< orphan*/ * wps_get_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wps_process_msg (int /*<<< orphan*/ ,int,struct wpabuf*) ; 

__attribute__((used)) static struct wpabuf * eap_wsc_process(struct eap_sm *sm, void *priv,
				       struct eap_method_ret *ret,
				       const struct wpabuf *reqData)
{
	struct eap_wsc_data *data = priv;
	const u8 *start, *pos, *end;
	size_t len;
	u8 op_code, flags, id;
	u16 message_length = 0;
	enum wps_process_res res;
	struct wpabuf tmpbuf;
	struct wpabuf *r;

	pos = eap_hdr_validate(EAP_VENDOR_WFA, EAP_VENDOR_TYPE_WSC, reqData,
			       &len);
	if (pos == NULL || len < 2) {
		ret->ignore = TRUE;
		return NULL;
	}

	id = eap_get_id(reqData);

	start = pos;
	end = start + len;

	op_code = *pos++;
	flags = *pos++;
	if (flags & WSC_FLAGS_LF) {
		if (end - pos < 2) {
			wpa_printf(MSG_DEBUG, "EAP-WSC: Message underflow");
			ret->ignore = TRUE;
			return NULL;
		}
		message_length = WPA_GET_BE16(pos);
		pos += 2;

		if (message_length < end - pos || message_length > 50000) {
			wpa_printf(MSG_DEBUG, "EAP-WSC: Invalid Message "
				   "Length");
			ret->ignore = TRUE;
			return NULL;
		}
	}

	wpa_printf(MSG_DEBUG, "EAP-WSC: Received packet: Op-Code %d "
		   "Flags 0x%x Message Length %d",
		   op_code, flags, message_length);

	if (data->state == WAIT_FRAG_ACK) {
		if (op_code != WSC_FRAG_ACK) {
			wpa_printf(MSG_DEBUG, "EAP-WSC: Unexpected Op-Code %d "
				   "in WAIT_FRAG_ACK state", op_code);
			ret->ignore = TRUE;
			return NULL;
		}
		wpa_printf(MSG_DEBUG, "EAP-WSC: Fragment acknowledged");
		eap_wsc_state(data, MESG);
		return eap_wsc_build_msg(data, ret, id);
	}

	if (op_code != WSC_ACK && op_code != WSC_NACK && op_code != WSC_MSG &&
	    op_code != WSC_Done && op_code != WSC_Start) {
		wpa_printf(MSG_DEBUG, "EAP-WSC: Unexpected Op-Code %d",
			   op_code);
		ret->ignore = TRUE;
		return NULL;
	}

	if (data->state == WAIT_START) {
		if (op_code != WSC_Start) {
			wpa_printf(MSG_DEBUG, "EAP-WSC: Unexpected Op-Code %d "
				   "in WAIT_START state", op_code);
			ret->ignore = TRUE;
			return NULL;
		}
		wpa_printf(MSG_DEBUG, "EAP-WSC: Received start");
		eap_wsc_state(data, MESG);
		/* Start message has empty payload, skip processing */
		goto send_msg;
	} else if (op_code == WSC_Start) {
		wpa_printf(MSG_DEBUG, "EAP-WSC: Unexpected Op-Code %d",
			   op_code);
		ret->ignore = TRUE;
		return NULL;
	}

	if (data->in_buf &&
	    eap_wsc_process_cont(data, pos, end - pos, op_code) < 0) {
		ret->ignore = TRUE;
		return NULL;
	}

	if (flags & WSC_FLAGS_MF) {
		return eap_wsc_process_fragment(data, ret, id, flags, op_code,
						message_length, pos,
						end - pos);
	}

	if (data->in_buf == NULL) {
		/* Wrap unfragmented messages as wpabuf without extra copy */
		wpabuf_set(&tmpbuf, pos, end - pos);
		data->in_buf = &tmpbuf;
	}

	res = wps_process_msg(data->wps, op_code, data->in_buf);
	switch (res) {
	case WPS_DONE:
		wpa_printf(MSG_DEBUG, "EAP-WSC: WPS processing completed "
			   "successfully - wait for EAP failure");
		eap_wsc_state(data, FAIL);
		break;
	case WPS_CONTINUE:
		eap_wsc_state(data, MESG);
		break;
	case WPS_FAILURE:
	case WPS_PENDING:
		wpa_printf(MSG_DEBUG, "EAP-WSC: WPS processing failed");
		eap_wsc_state(data, FAIL);
		break;
	}

	if (data->in_buf != &tmpbuf)
		wpabuf_free(data->in_buf);
	data->in_buf = NULL;

send_msg:
	if (data->out_buf == NULL) {
		data->out_buf = wps_get_msg(data->wps, &data->out_op_code);
		if (data->out_buf == NULL) {
			wpa_printf(MSG_DEBUG, "EAP-WSC: Failed to receive "
				   "message from WPS");
			eap_wsc_state(data, FAIL);
			ret->methodState = METHOD_DONE;
			ret->decision = DECISION_FAIL;
			return NULL;
		}
		data->out_used = 0;
	}

	eap_wsc_state(data, MESG);
	r = eap_wsc_build_msg(data, ret, id);
	if (data->state == FAIL && ret->methodState == METHOD_DONE) {
		/* Use reduced client timeout for WPS to avoid long wait */
		if (sm->ClientTimeout > 2)
			sm->ClientTimeout = 2;
	}
	return r;
}