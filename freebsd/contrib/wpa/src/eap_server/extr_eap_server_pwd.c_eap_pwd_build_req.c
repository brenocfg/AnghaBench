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
struct eap_pwd_data {int state; scalar_t__ out_frag_pos; scalar_t__ mtu; struct wpabuf* outbuf; scalar_t__ in_frag_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 scalar_t__ EAP_PWD_GET_LENGTH_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ EAP_PWD_HDR_SIZE ; 
 int /*<<< orphan*/  EAP_PWD_OPCODE_COMMIT_EXCH ; 
 int /*<<< orphan*/  EAP_PWD_OPCODE_CONFIRM_EXCH ; 
 int /*<<< orphan*/  EAP_PWD_OPCODE_ID_EXCH ; 
 int /*<<< orphan*/  EAP_PWD_SET_LENGTH_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EAP_PWD_SET_MORE_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EAP_TYPE_PWD ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
#define  PWD_Commit_Req 130 
#define  PWD_Confirm_Req 129 
#define  PWD_ID_Req 128 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_pwd_build_commit_req (struct eap_sm*,struct eap_pwd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_pwd_build_confirm_req (struct eap_sm*,struct eap_pwd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_pwd_build_id_req (struct eap_sm*,struct eap_pwd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_pwd_state (struct eap_pwd_data*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_head_u8 (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf *
eap_pwd_build_req(struct eap_sm *sm, void *priv, u8 id)
{
	struct eap_pwd_data *data = priv;
	struct wpabuf *req;
	u8 lm_exch;
	const u8 *buf;
	u16 totlen = 0;
	size_t len;

	/*
	 * if we're buffering response fragments then just ACK
	 */
	if (data->in_frag_pos) {
		wpa_printf(MSG_DEBUG, "EAP-pwd: ACKing a fragment!!");
		req = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_PWD,
				    EAP_PWD_HDR_SIZE, EAP_CODE_REQUEST, id);
		if (req == NULL) {
			eap_pwd_state(data, FAILURE);
			return NULL;
		}
		switch (data->state) {
		case PWD_ID_Req:
			wpabuf_put_u8(req, EAP_PWD_OPCODE_ID_EXCH);
			break;
		case PWD_Commit_Req:
			wpabuf_put_u8(req, EAP_PWD_OPCODE_COMMIT_EXCH);
			break;
		case PWD_Confirm_Req:
			wpabuf_put_u8(req, EAP_PWD_OPCODE_CONFIRM_EXCH);
			break;
		default:
			eap_pwd_state(data, FAILURE);   /* just to be sure */
			wpabuf_free(req);
			return NULL;
		}
		return req;
	}

	/*
	 * build the data portion of a request
	 */
	switch (data->state) {
	case PWD_ID_Req:
		eap_pwd_build_id_req(sm, data, id);
		lm_exch = EAP_PWD_OPCODE_ID_EXCH;
		break;
	case PWD_Commit_Req:
		eap_pwd_build_commit_req(sm, data, id);
		lm_exch = EAP_PWD_OPCODE_COMMIT_EXCH;
		break;
	case PWD_Confirm_Req:
		eap_pwd_build_confirm_req(sm, data, id);
		lm_exch = EAP_PWD_OPCODE_CONFIRM_EXCH;
		break;
	default:
		wpa_printf(MSG_INFO, "EAP-pwd: Unknown state %d in build_req",
			   data->state);
		eap_pwd_state(data, FAILURE);
		lm_exch = 0;    /* hush now, sweet compiler */
		break;
	}

	if (data->state == FAILURE)
		return NULL;

	/*
	 * determine whether that data needs to be fragmented
	 */
	len = wpabuf_len(data->outbuf) - data->out_frag_pos;
	if ((len + EAP_PWD_HDR_SIZE) > data->mtu) {
		len = data->mtu - EAP_PWD_HDR_SIZE;
		EAP_PWD_SET_MORE_BIT(lm_exch);
		/*
		 * if this is the first fragment, need to set the M bit
		 * and add the total length to the eap_pwd_hdr
		 */
		if (data->out_frag_pos == 0) {
			EAP_PWD_SET_LENGTH_BIT(lm_exch);
			totlen = wpabuf_len(data->outbuf) +
				EAP_PWD_HDR_SIZE + sizeof(u16);
			len -= sizeof(u16);
			wpa_printf(MSG_DEBUG, "EAP-pwd: Fragmenting output, "
				   "total length = %d", totlen);
		}
		wpa_printf(MSG_DEBUG, "EAP-pwd: Send a %d byte fragment",
			   (int) len);
	}

	/*
	 * alloc an eap request and populate it with the data
	 */
	req = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_PWD,
			    EAP_PWD_HDR_SIZE + len +
			    (totlen ? sizeof(u16) : 0),
			    EAP_CODE_REQUEST, id);
	if (req == NULL) {
		eap_pwd_state(data, FAILURE);
		return NULL;
	}

	wpabuf_put_u8(req, lm_exch);
	if (EAP_PWD_GET_LENGTH_BIT(lm_exch))
		wpabuf_put_be16(req, totlen);

	buf = wpabuf_head_u8(data->outbuf);
	wpabuf_put_data(req, buf + data->out_frag_pos, len);
	data->out_frag_pos += len;
	/*
	 * either not fragged or last fragment, either way free up the data
	 */
	if (data->out_frag_pos >= wpabuf_len(data->outbuf)) {
		wpabuf_free(data->outbuf);
		data->outbuf = NULL;
		data->out_frag_pos = 0;
	}

	return req;
}