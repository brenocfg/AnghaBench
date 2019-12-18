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
struct eap_wsc_data {scalar_t__ out_used; int fragment_size; int out_op_code; scalar_t__ state; int /*<<< orphan*/ * out_buf; } ;
struct eap_method_ret {int /*<<< orphan*/  methodState; int /*<<< orphan*/  decision; int /*<<< orphan*/  allowNotifications; int /*<<< orphan*/  ignore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAIL ; 
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_VENDOR_TYPE_WSC ; 
 int /*<<< orphan*/  EAP_VENDOR_WFA ; 
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MESG ; 
 int /*<<< orphan*/  METHOD_DONE ; 
 int /*<<< orphan*/  METHOD_MAY_CONT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WAIT_FRAG_ACK ; 
 int WSC_ACK ; 
 int WSC_Done ; 
 int WSC_FLAGS_LF ; 
 int WSC_FLAGS_MF ; 
 int WSC_NACK ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  eap_wsc_state (struct eap_wsc_data*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 
 scalar_t__ wpabuf_head_u8 (int /*<<< orphan*/ *) ; 
 scalar_t__ wpabuf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * eap_wsc_build_msg(struct eap_wsc_data *data,
					 struct eap_method_ret *ret, u8 id)
{
	struct wpabuf *resp;
	u8 flags;
	size_t send_len, plen;

	ret->ignore = FALSE;
	wpa_printf(MSG_DEBUG, "EAP-WSC: Generating Response");
	ret->allowNotifications = TRUE;

	flags = 0;
	send_len = wpabuf_len(data->out_buf) - data->out_used;
	if (2 + send_len > data->fragment_size) {
		send_len = data->fragment_size - 2;
		flags |= WSC_FLAGS_MF;
		if (data->out_used == 0) {
			flags |= WSC_FLAGS_LF;
			send_len -= 2;
		}
	}
	plen = 2 + send_len;
	if (flags & WSC_FLAGS_LF)
		plen += 2;
	resp = eap_msg_alloc(EAP_VENDOR_WFA, EAP_VENDOR_TYPE_WSC, plen,
			     EAP_CODE_RESPONSE, id);
	if (resp == NULL)
		return NULL;

	wpabuf_put_u8(resp, data->out_op_code); /* Op-Code */
	wpabuf_put_u8(resp, flags); /* Flags */
	if (flags & WSC_FLAGS_LF)
		wpabuf_put_be16(resp, wpabuf_len(data->out_buf));

	wpabuf_put_data(resp, wpabuf_head_u8(data->out_buf) + data->out_used,
			send_len);
	data->out_used += send_len;

	ret->methodState = METHOD_MAY_CONT;
	ret->decision = DECISION_FAIL;

	if (data->out_used == wpabuf_len(data->out_buf)) {
		wpa_printf(MSG_DEBUG, "EAP-WSC: Sending out %lu bytes "
			   "(message sent completely)",
			   (unsigned long) send_len);
		wpabuf_free(data->out_buf);
		data->out_buf = NULL;
		data->out_used = 0;
		if ((data->state == FAIL && data->out_op_code == WSC_ACK) ||
		    data->out_op_code == WSC_NACK ||
		    data->out_op_code == WSC_Done) {
			eap_wsc_state(data, FAIL);
			ret->methodState = METHOD_DONE;
		} else
			eap_wsc_state(data, MESG);
	} else {
		wpa_printf(MSG_DEBUG, "EAP-WSC: Sending out %lu bytes "
			   "(%lu more to send)", (unsigned long) send_len,
			   (unsigned long) wpabuf_len(data->out_buf) -
			   data->out_used);
		eap_wsc_state(data, WAIT_FRAG_ACK);
	}

	return resp;
}