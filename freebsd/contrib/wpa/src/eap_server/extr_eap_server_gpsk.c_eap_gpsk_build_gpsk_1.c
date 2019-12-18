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
struct wpabuf {int dummy; } ;
struct eap_sm {int server_id_len; int /*<<< orphan*/  server_id; } ;
struct eap_gpsk_data {int csuite_count; int /*<<< orphan*/  csuite_list; int /*<<< orphan*/  rand_server; } ;
struct eap_gpsk_csuite {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  EAP_GPSK_OPCODE_GPSK_1 ; 
 int EAP_GPSK_RAND_LEN ; 
 int /*<<< orphan*/  EAP_TYPE_GPSK ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  eap_gpsk_state (struct eap_gpsk_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * eap_gpsk_build_gpsk_1(struct eap_sm *sm,
					     struct eap_gpsk_data *data, u8 id)
{
	size_t len;
	struct wpabuf *req;

	wpa_printf(MSG_DEBUG, "EAP-GPSK: Request/GPSK-1");

	if (random_get_bytes(data->rand_server, EAP_GPSK_RAND_LEN)) {
		wpa_printf(MSG_ERROR, "EAP-GPSK: Failed to get random data");
		eap_gpsk_state(data, FAILURE);
		return NULL;
	}
	wpa_hexdump(MSG_MSGDUMP, "EAP-GPSK: RAND_Server",
		    data->rand_server, EAP_GPSK_RAND_LEN);

	len = 1 + 2 + sm->server_id_len + EAP_GPSK_RAND_LEN + 2 +
		data->csuite_count * sizeof(struct eap_gpsk_csuite);
	req = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_GPSK, len,
			    EAP_CODE_REQUEST, id);
	if (req == NULL) {
		wpa_printf(MSG_ERROR, "EAP-GPSK: Failed to allocate memory "
			   "for request/GPSK-1");
		eap_gpsk_state(data, FAILURE);
		return NULL;
	}

	wpabuf_put_u8(req, EAP_GPSK_OPCODE_GPSK_1);
	wpabuf_put_be16(req, sm->server_id_len);
	wpabuf_put_data(req, sm->server_id, sm->server_id_len);
	wpabuf_put_data(req, data->rand_server, EAP_GPSK_RAND_LEN);
	wpabuf_put_be16(req,
			data->csuite_count * sizeof(struct eap_gpsk_csuite));
	wpabuf_put_data(req, data->csuite_list,
			data->csuite_count * sizeof(struct eap_gpsk_csuite));

	return req;
}