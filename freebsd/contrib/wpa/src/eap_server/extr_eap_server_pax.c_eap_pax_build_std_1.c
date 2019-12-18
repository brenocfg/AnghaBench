#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_pax_hdr {int /*<<< orphan*/  public_key_id; int /*<<< orphan*/  dh_group_id; int /*<<< orphan*/  mac_id; scalar_t__ flags; int /*<<< orphan*/  op_code; } ;
struct TYPE_3__ {int /*<<< orphan*/ * x; } ;
struct TYPE_4__ {TYPE_1__ r; } ;
struct eap_pax_data {void* state; int /*<<< orphan*/  mac_id; TYPE_2__ rand; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  EAP_PAX_DH_GROUP_NONE ; 
 scalar_t__ EAP_PAX_ICV_LEN ; 
 int EAP_PAX_MAC_LEN ; 
 int /*<<< orphan*/  EAP_PAX_OP_STD_1 ; 
 int /*<<< orphan*/  EAP_PAX_PUBLIC_KEY_NONE ; 
 scalar_t__ EAP_PAX_RAND_LEN ; 
 int /*<<< orphan*/  EAP_TYPE_PAX ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 void* FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_pax_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_mhead (struct wpabuf*) ; 
 void* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static struct wpabuf * eap_pax_build_std_1(struct eap_sm *sm,
					   struct eap_pax_data *data, u8 id)
{
	struct wpabuf *req;
	struct eap_pax_hdr *pax;
	u8 *pos;

	wpa_printf(MSG_DEBUG, "EAP-PAX: PAX_STD-1 (sending)");

	if (random_get_bytes(data->rand.r.x, EAP_PAX_RAND_LEN)) {
		wpa_printf(MSG_ERROR, "EAP-PAX: Failed to get random data");
		data->state = FAILURE;
		return NULL;
	}

	req = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_PAX,
			    sizeof(*pax) + 2 + EAP_PAX_RAND_LEN +
			    EAP_PAX_ICV_LEN, EAP_CODE_REQUEST, id);
	if (req == NULL) {
		wpa_printf(MSG_ERROR, "EAP-PAX: Failed to allocate memory "
			   "request");
		data->state = FAILURE;
		return NULL;
	}

	pax = wpabuf_put(req, sizeof(*pax));
	pax->op_code = EAP_PAX_OP_STD_1;
	pax->flags = 0;
	pax->mac_id = data->mac_id;
	pax->dh_group_id = EAP_PAX_DH_GROUP_NONE;
	pax->public_key_id = EAP_PAX_PUBLIC_KEY_NONE;

	wpabuf_put_be16(req, EAP_PAX_RAND_LEN);
	wpabuf_put_data(req, data->rand.r.x, EAP_PAX_RAND_LEN);
	wpa_hexdump(MSG_MSGDUMP, "EAP-PAX: A = X (server rand)",
		    data->rand.r.x, EAP_PAX_RAND_LEN);

	pos = wpabuf_put(req, EAP_PAX_MAC_LEN);
	if (eap_pax_mac(data->mac_id, (u8 *) "", 0,
			wpabuf_mhead(req), wpabuf_len(req) - EAP_PAX_ICV_LEN,
			NULL, 0, NULL, 0, pos) < 0) {
		wpa_printf(MSG_ERROR, "EAP-PAX: Failed to calculate ICV");
		data->state = FAILURE;
		wpabuf_free(req);
		return NULL;
	}
	wpa_hexdump(MSG_MSGDUMP, "EAP-PAX: ICV", pos, EAP_PAX_ICV_LEN);

	return req;
}