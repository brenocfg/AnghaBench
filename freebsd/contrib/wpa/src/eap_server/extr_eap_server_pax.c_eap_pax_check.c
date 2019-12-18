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
struct eap_sm {int dummy; } ;
struct eap_pax_hdr {scalar_t__ op_code; int flags; scalar_t__ mac_id; scalar_t__ dh_group_id; scalar_t__ public_key_id; } ;
struct eap_pax_data {scalar_t__ state; scalar_t__ mac_id; int /*<<< orphan*/  ick; scalar_t__ keys_set; } ;
struct eap_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 scalar_t__ EAP_PAX_DH_GROUP_NONE ; 
 int EAP_PAX_FLAGS_CE ; 
 int EAP_PAX_FLAGS_MF ; 
 int /*<<< orphan*/  EAP_PAX_ICK_LEN ; 
 int EAP_PAX_ICV_LEN ; 
 scalar_t__ EAP_PAX_OP_ACK ; 
 scalar_t__ EAP_PAX_OP_STD_2 ; 
 scalar_t__ EAP_PAX_PUBLIC_KEY_NONE ; 
 int /*<<< orphan*/  EAP_TYPE_PAX ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 scalar_t__ PAX_STD_1 ; 
 scalar_t__ PAX_STD_3 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*,size_t*) ; 
 scalar_t__ eap_pax_mac (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_mhead (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_mhead_u8 (struct wpabuf*) ; 

__attribute__((used)) static Boolean eap_pax_check(struct eap_sm *sm, void *priv,
			     struct wpabuf *respData)
{
	struct eap_pax_data *data = priv;
	struct eap_pax_hdr *resp;
	const u8 *pos;
	size_t len, mlen;
	u8 icvbuf[EAP_PAX_ICV_LEN], *icv;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_PAX, respData, &len);
	if (pos == NULL || len < sizeof(*resp) + EAP_PAX_ICV_LEN) {
		wpa_printf(MSG_INFO, "EAP-PAX: Invalid frame");
		return TRUE;
	}

	mlen = sizeof(struct eap_hdr) + 1 + len;
	resp = (struct eap_pax_hdr *) pos;

	wpa_printf(MSG_DEBUG, "EAP-PAX: received frame: op_code 0x%x "
		   "flags 0x%x mac_id 0x%x dh_group_id 0x%x "
		   "public_key_id 0x%x",
		   resp->op_code, resp->flags, resp->mac_id, resp->dh_group_id,
		   resp->public_key_id);
	wpa_hexdump(MSG_MSGDUMP, "EAP-PAX: received payload",
		    (u8 *) (resp + 1), len - sizeof(*resp) - EAP_PAX_ICV_LEN);

	if (data->state == PAX_STD_1 &&
	    resp->op_code != EAP_PAX_OP_STD_2) {
		wpa_printf(MSG_DEBUG, "EAP-PAX: Expected PAX_STD-2 - "
			   "ignore op %d", resp->op_code);
		return TRUE;
	}

	if (data->state == PAX_STD_3 &&
	    resp->op_code != EAP_PAX_OP_ACK) {
		wpa_printf(MSG_DEBUG, "EAP-PAX: Expected PAX-ACK - "
			   "ignore op %d", resp->op_code);
		return TRUE;
	}

	if (resp->op_code != EAP_PAX_OP_STD_2 &&
	    resp->op_code != EAP_PAX_OP_ACK) {
		wpa_printf(MSG_DEBUG, "EAP-PAX: Unknown op_code 0x%x",
			   resp->op_code);
	}

	if (data->mac_id != resp->mac_id) {
		wpa_printf(MSG_DEBUG, "EAP-PAX: Expected MAC ID 0x%x, "
			   "received 0x%x", data->mac_id, resp->mac_id);
		return TRUE;
	}

	if (resp->dh_group_id != EAP_PAX_DH_GROUP_NONE) {
		wpa_printf(MSG_INFO, "EAP-PAX: Expected DH Group ID 0x%x, "
			   "received 0x%x", EAP_PAX_DH_GROUP_NONE,
			   resp->dh_group_id);
		return TRUE;
	}

	if (resp->public_key_id != EAP_PAX_PUBLIC_KEY_NONE) {
		wpa_printf(MSG_INFO, "EAP-PAX: Expected Public Key ID 0x%x, "
			   "received 0x%x", EAP_PAX_PUBLIC_KEY_NONE,
			   resp->public_key_id);
		return TRUE;
	}

	if (resp->flags & EAP_PAX_FLAGS_MF) {
		/* TODO: add support for reassembling fragments */
		wpa_printf(MSG_INFO, "EAP-PAX: fragmentation not supported");
		return TRUE;
	}

	if (resp->flags & EAP_PAX_FLAGS_CE) {
		wpa_printf(MSG_INFO, "EAP-PAX: Unexpected CE flag");
		return TRUE;
	}

	if (data->keys_set) {
		if (len - sizeof(*resp) < EAP_PAX_ICV_LEN) {
			wpa_printf(MSG_INFO, "EAP-PAX: No ICV in the packet");
			return TRUE;
		}
		icv = wpabuf_mhead_u8(respData) + mlen - EAP_PAX_ICV_LEN;
		wpa_hexdump(MSG_MSGDUMP, "EAP-PAX: ICV", icv, EAP_PAX_ICV_LEN);
		if (eap_pax_mac(data->mac_id, data->ick, EAP_PAX_ICK_LEN,
				wpabuf_mhead(respData),
				wpabuf_len(respData) - EAP_PAX_ICV_LEN,
				NULL, 0, NULL, 0, icvbuf) < 0) {
			wpa_printf(MSG_INFO,
				   "EAP-PAX: Failed to calculate ICV");
			return TRUE;
		}

		if (os_memcmp_const(icvbuf, icv, EAP_PAX_ICV_LEN) != 0) {
			wpa_printf(MSG_INFO, "EAP-PAX: Invalid ICV");
			wpa_hexdump(MSG_MSGDUMP, "EAP-PAX: Expected ICV",
				    icvbuf, EAP_PAX_ICV_LEN);
			return TRUE;
		}
	}

	return FALSE;
}