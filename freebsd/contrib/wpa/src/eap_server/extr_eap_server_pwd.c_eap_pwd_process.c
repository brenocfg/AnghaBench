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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_pwd_data {size_t in_frag_pos; int /*<<< orphan*/ * inbuf; scalar_t__ out_frag_pos; } ;

/* Variables and functions */
 int EAP_PWD_GET_EXCHANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ EAP_PWD_GET_LENGTH_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ EAP_PWD_GET_MORE_BIT (int /*<<< orphan*/ ) ; 
#define  EAP_PWD_OPCODE_COMMIT_EXCH 130 
#define  EAP_PWD_OPCODE_CONFIRM_EXCH 129 
#define  EAP_PWD_OPCODE_ID_EXCH 128 
 int /*<<< orphan*/  EAP_TYPE_PWD ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*,size_t*) ; 
 int /*<<< orphan*/  eap_pwd_process_commit_resp (struct eap_sm*,struct eap_pwd_data*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  eap_pwd_process_confirm_resp (struct eap_sm*,struct eap_pwd_data*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  eap_pwd_process_id_resp (struct eap_sm*,struct eap_pwd_data*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  eap_pwd_state (struct eap_pwd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpabuf_head_u8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_put_data (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 size_t wpabuf_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eap_pwd_process(struct eap_sm *sm, void *priv,
			    struct wpabuf *respData)
{
	struct eap_pwd_data *data = priv;
	const u8 *pos;
	size_t len;
	u8 lm_exch;
	u16 tot_len;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_PWD, respData, &len);
	if ((pos == NULL) || (len < 1)) {
		wpa_printf(MSG_INFO, "Bad EAP header! pos %s and len = %d",
			   (pos == NULL) ? "is NULL" : "is not NULL",
			   (int) len);
		return;
	}

	lm_exch = *pos;
	pos++;            /* skip over the bits and the exch */
	len--;

	/*
	 * if we're fragmenting then this should be an ACK with no data,
	 * just return and continue fragmenting in the "build" section above
	 */
	if (data->out_frag_pos) {
		if (len > 1)
			wpa_printf(MSG_INFO, "EAP-pwd: Bad response! "
				   "Fragmenting but not an ACK");
		else
			wpa_printf(MSG_DEBUG, "EAP-pwd: received ACK from "
				   "peer");
		return;
	}
	/*
	 * if we're receiving fragmented packets then we need to buffer...
	 *
	 * the first fragment has a total length
	 */
	if (EAP_PWD_GET_LENGTH_BIT(lm_exch)) {
		if (len < 2) {
			wpa_printf(MSG_DEBUG,
				   "EAP-pwd: Frame too short to contain Total-Length field");
			return;
		}
		tot_len = WPA_GET_BE16(pos);
		wpa_printf(MSG_DEBUG, "EAP-pwd: Incoming fragments, total "
			   "length = %d", tot_len);
		if (tot_len > 15000)
			return;
		if (data->inbuf) {
			wpa_printf(MSG_DEBUG,
				   "EAP-pwd: Unexpected new fragment start when previous fragment is still in use");
			return;
		}
		data->inbuf = wpabuf_alloc(tot_len);
		if (data->inbuf == NULL) {
			wpa_printf(MSG_INFO, "EAP-pwd: Out of memory to "
				   "buffer fragments!");
			return;
		}
		data->in_frag_pos = 0;
		pos += sizeof(u16);
		len -= sizeof(u16);
	}
	/*
	 * the first and all intermediate fragments have the M bit set
	 */
	if (EAP_PWD_GET_MORE_BIT(lm_exch) || data->in_frag_pos) {
		if (!data->inbuf) {
			wpa_printf(MSG_DEBUG,
				   "EAP-pwd: No buffer for reassembly");
			eap_pwd_state(data, FAILURE);
			return;
		}
		if ((data->in_frag_pos + len) > wpabuf_size(data->inbuf)) {
			wpa_printf(MSG_DEBUG, "EAP-pwd: Buffer overflow "
				   "attack detected! (%d+%d > %d)",
				   (int) data->in_frag_pos, (int) len,
				   (int) wpabuf_size(data->inbuf));
			eap_pwd_state(data, FAILURE);
			return;
		}
		wpabuf_put_data(data->inbuf, pos, len);
		data->in_frag_pos += len;
	}
	if (EAP_PWD_GET_MORE_BIT(lm_exch)) {
		wpa_printf(MSG_DEBUG, "EAP-pwd: Got a %d byte fragment",
			   (int) len);
		return;
	}
	/*
	 * last fragment won't have the M bit set (but we're obviously
	 * buffering fragments so that's how we know it's the last)
	 */
	if (data->in_frag_pos && data->inbuf) {
		pos = wpabuf_head_u8(data->inbuf);
		len = data->in_frag_pos;
		wpa_printf(MSG_DEBUG, "EAP-pwd: Last fragment, %d bytes",
			   (int) len);
	}
	switch (EAP_PWD_GET_EXCHANGE(lm_exch)) {
	case EAP_PWD_OPCODE_ID_EXCH:
		eap_pwd_process_id_resp(sm, data, pos, len);
		break;
	case EAP_PWD_OPCODE_COMMIT_EXCH:
		eap_pwd_process_commit_resp(sm, data, pos, len);
		break;
	case EAP_PWD_OPCODE_CONFIRM_EXCH:
		eap_pwd_process_confirm_resp(sm, data, pos, len);
		break;
	}
	/*
	 * if we had been buffering fragments, here's a great place
	 * to clean up
	 */
	if (data->in_frag_pos) {
		wpabuf_free(data->inbuf);
		data->inbuf = NULL;
		data->in_frag_pos = 0;
	}
}