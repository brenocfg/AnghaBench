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
struct wpabuf {int dummy; } ;
struct gas_server_response {int freq; size_t offset; int /*<<< orphan*/  dst; int /*<<< orphan*/  resp; int /*<<< orphan*/  list; int /*<<< orphan*/  frag_id; int /*<<< orphan*/  dialog_token; struct gas_server_handler* handler; } ;
struct gas_server_handler {int adv_proto_id_len; size_t adv_proto_id; struct gas_server* gas; } ;
struct gas_server {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* tx ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct wpabuf*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WLAN_EID_ADV_PROTO ; 
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 struct wpabuf* gas_build_comeback_resp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  gas_server_free_response (struct gas_server_response*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 size_t wpabuf_head_u8 (int /*<<< orphan*/ ) ; 
 size_t wpabuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,size_t,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static void
gas_server_handle_rx_comeback_req(struct gas_server_response *response)
{
	struct gas_server_handler *handler = response->handler;
	struct gas_server *gas = handler->gas;
	size_t max_len = (response->freq > 56160) ? 928 : 1400;
	size_t hdr_len = 24 + 2 + 6 + 3 + handler->adv_proto_id_len + 2;
	size_t remaining, resp_frag_len;
	struct wpabuf *resp;

	remaining = wpabuf_len(response->resp) - response->offset;
	if (hdr_len + remaining > max_len)
		resp_frag_len = max_len - hdr_len;
	else
		resp_frag_len = remaining;
	wpa_printf(MSG_DEBUG,
		   "GAS: Sending out %u/%u remaining Query Response octets",
		   (unsigned int) resp_frag_len, (unsigned int) remaining);

	resp = gas_build_comeback_resp(response->dialog_token,
				       WLAN_STATUS_SUCCESS,
				       response->frag_id++,
				       resp_frag_len < remaining, 0,
				       handler->adv_proto_id_len +
				       resp_frag_len);
	if (!resp) {
		dl_list_del(&response->list);
		gas_server_free_response(response);
		return;
	}

	/* Advertisement Protocol element */
	wpabuf_put_u8(resp, WLAN_EID_ADV_PROTO);
	wpabuf_put_u8(resp, 1 + handler->adv_proto_id_len); /* Length */
	wpabuf_put_u8(resp, 0x7f);
	/* Advertisement Protocol ID */
	wpabuf_put_data(resp, handler->adv_proto_id, handler->adv_proto_id_len);

	/* Query Response Length */
	wpabuf_put_le16(resp, resp_frag_len);
	wpabuf_put_data(resp, wpabuf_head_u8(response->resp) + response->offset,
			resp_frag_len);

	response->offset += resp_frag_len;

	gas->tx(gas->ctx, response->freq, response->dst, resp,
		remaining > resp_frag_len ? 2000 : 0);
	wpabuf_free(resp);
}