#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int /*<<< orphan*/  server_id_len; int /*<<< orphan*/  server_id; } ;
struct TYPE_4__ {int dhcomp_len; int pnonce_len; scalar_t__ nonce_len; } ;
struct eap_eke_data {scalar_t__ state; int /*<<< orphan*/  msgs; TYPE_1__ sess; int /*<<< orphan*/  nonce_p; int /*<<< orphan*/  peerid_len; int /*<<< orphan*/  peerid; int /*<<< orphan*/  dh_priv; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 scalar_t__ COMMIT ; 
 int /*<<< orphan*/  CONFIRM ; 
 int /*<<< orphan*/  EAP_EKE_FAIL_AUTHENTICATION_FAIL ; 
 int /*<<< orphan*/  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EAP_EKE_FAIL_PROTO_ERROR ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ eap_eke_decrypt_prot (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ eap_eke_derive_ke_ki (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_eke_fail (struct eap_eke_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_eke_shared_secret (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  eap_eke_state (struct eap_eke_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_put_buf (int /*<<< orphan*/ ,struct wpabuf const*) ; 
 scalar_t__ wpabuf_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_eke_process_commit(struct eap_sm *sm,
				   struct eap_eke_data *data,
				   const struct wpabuf *respData,
				   const u8 *payload, size_t payloadlen)
{
	const u8 *pos, *end, *dhcomp, *pnonce;
	size_t decrypt_len;

	wpa_printf(MSG_DEBUG, "EAP-EKE: Received Response/Commit");

	if (data->state != COMMIT) {
		eap_eke_fail(data, EAP_EKE_FAIL_PROTO_ERROR);
		return;
	}

	pos = payload;
	end = payload + payloadlen;

	if (pos + data->sess.dhcomp_len + data->sess.pnonce_len > end) {
		wpa_printf(MSG_DEBUG, "EAP-EKE: Too short EAP-EKE-Commit");
		eap_eke_fail(data, EAP_EKE_FAIL_PROTO_ERROR);
		return;
	}

	wpa_hexdump(MSG_DEBUG, "EAP-EKE: DHComponent_P",
		    pos, data->sess.dhcomp_len);
	dhcomp = pos;
	pos += data->sess.dhcomp_len;
	wpa_hexdump(MSG_DEBUG, "EAP-EKE: PNonce_P", pos, data->sess.pnonce_len);
	pnonce = pos;
	pos += data->sess.pnonce_len;
	wpa_hexdump(MSG_DEBUG, "EAP-EKE: CBValue", pos, end - pos);

	if (eap_eke_shared_secret(&data->sess, data->key, data->dh_priv, dhcomp)
	    < 0) {
		wpa_printf(MSG_INFO, "EAP-EKE: Failed to derive shared secret");
		eap_eke_fail(data, EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
		return;
	}

	if (eap_eke_derive_ke_ki(&data->sess,
				 sm->server_id, sm->server_id_len,
				 data->peerid, data->peerid_len) < 0) {
		wpa_printf(MSG_INFO, "EAP-EKE: Failed to derive Ke/Ki");
		eap_eke_fail(data, EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
		return;
	}

	decrypt_len = sizeof(data->nonce_p);
	if (eap_eke_decrypt_prot(&data->sess, pnonce, data->sess.pnonce_len,
				 data->nonce_p, &decrypt_len) < 0) {
		wpa_printf(MSG_INFO, "EAP-EKE: Failed to decrypt PNonce_P");
		eap_eke_fail(data, EAP_EKE_FAIL_AUTHENTICATION_FAIL);
		return;
	}
	if (decrypt_len < (size_t) data->sess.nonce_len) {
		wpa_printf(MSG_INFO, "EAP-EKE: PNonce_P protected data too short to include Nonce_P");
		eap_eke_fail(data, EAP_EKE_FAIL_AUTHENTICATION_FAIL);
		return;
	}
	wpa_hexdump_key(MSG_DEBUG, "EAP-EKE: Nonce_P",
			data->nonce_p, data->sess.nonce_len);

	if (wpabuf_resize(&data->msgs, wpabuf_len(respData)) < 0) {
		eap_eke_fail(data, EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
		return;
	}
	wpabuf_put_buf(data->msgs, respData);

	eap_eke_state(data, CONFIRM);
}