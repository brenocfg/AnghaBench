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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int /*<<< orphan*/  eapol_ctx; TYPE_1__* eapol_cb; } ;
struct eap_identity_data {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {char* (* get_eap_req_id_text ) (int /*<<< orphan*/ ,size_t*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  EAP_TYPE_IDENTITY ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* stub1 (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,char const*,size_t) ; 

__attribute__((used)) static struct wpabuf * eap_identity_buildReq(struct eap_sm *sm, void *priv,
					     u8 id)
{
	struct eap_identity_data *data = priv;
	struct wpabuf *req;
	const char *req_data;
	size_t req_data_len;

	if (sm->eapol_cb->get_eap_req_id_text) {
		req_data = sm->eapol_cb->get_eap_req_id_text(sm->eapol_ctx,
							     &req_data_len);
	} else {
		req_data = NULL;
		req_data_len = 0;
	}
	req = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_IDENTITY, req_data_len,
			    EAP_CODE_REQUEST, id);
	if (req == NULL) {
		wpa_printf(MSG_ERROR, "EAP-Identity: Failed to allocate "
			   "memory for request");
		data->state = FAILURE;
		return NULL;
	}

	wpabuf_put_data(req, req_data, req_data_len);

	return req;
}