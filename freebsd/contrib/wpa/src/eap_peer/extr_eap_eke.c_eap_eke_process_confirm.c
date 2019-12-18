#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct eap_method_ret {int /*<<< orphan*/  allowNotifications; int /*<<< orphan*/  decision; int /*<<< orphan*/  methodState; } ;
struct TYPE_7__ {int pnonce_ps_len; size_t prf_len; size_t nonce_len; scalar_t__ pnonce_len; } ;
struct eap_eke_data {scalar_t__ state; TYPE_1__ sess; int /*<<< orphan*/  dh_priv; int /*<<< orphan*/  emsk; int /*<<< orphan*/  msk; int /*<<< orphan*/  nonce_p; int /*<<< orphan*/ * nonce_s; int /*<<< orphan*/  peerid_len; int /*<<< orphan*/  peerid; int /*<<< orphan*/  serverid_len; int /*<<< orphan*/  serverid; int /*<<< orphan*/  msgs; } ;
typedef  int /*<<< orphan*/  nonces ;

/* Variables and functions */
 scalar_t__ CONFIRM ; 
 int /*<<< orphan*/  DECISION_COND_SUCC ; 
 int /*<<< orphan*/  EAP_EKE_CONFIRM ; 
 int /*<<< orphan*/  EAP_EKE_FAIL_AUTHENTICATION_FAIL ; 
 int /*<<< orphan*/  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EAP_EKE_FAIL_PROTO_ERROR ; 
 int EAP_EKE_MAX_HASH_LEN ; 
 int EAP_EKE_MAX_NONCE_LEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  METHOD_MAY_CONT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  SUCCESS ; 
 scalar_t__ eap_eke_auth (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct wpabuf* eap_eke_build_fail (struct eap_eke_data*,struct eap_method_ret*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_eke_build_msg (struct eap_eke_data*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_eke_decrypt_prot (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ eap_eke_derive_ka (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ eap_eke_derive_msk (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_eke_prot (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  eap_eke_session_clean (TYPE_1__*) ; 
 int /*<<< orphan*/  eap_eke_state (struct eap_eke_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_get_id (struct wpabuf const*) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,size_t) ; 
 size_t wpabuf_tailroom (struct wpabuf*) ; 

__attribute__((used)) static struct wpabuf * eap_eke_process_confirm(struct eap_eke_data *data,
					       struct eap_method_ret *ret,
					       const struct wpabuf *reqData,
					       const u8 *payload,
					       size_t payload_len)
{
	struct wpabuf *resp;
	const u8 *pos, *end;
	size_t prot_len;
	u8 nonces[2 * EAP_EKE_MAX_NONCE_LEN];
	u8 auth_s[EAP_EKE_MAX_HASH_LEN];
	size_t decrypt_len;
	u8 *auth;
	u8 id = eap_get_id(reqData);

	if (data->state != CONFIRM) {
		wpa_printf(MSG_DEBUG, "EAP-EKE: EAP-EKE-Confirm/Request received in unexpected state (%d)",
			   data->state);
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PROTO_ERROR);
	}

	wpa_printf(MSG_DEBUG, "EAP-EKE: Received EAP-EKE-Confirm/Request");

	pos = payload;
	end = payload + payload_len;

	if (pos + data->sess.pnonce_ps_len + data->sess.prf_len > end) {
		wpa_printf(MSG_DEBUG, "EAP-EKE: Too short EAP-EKE-Confirm");
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PROTO_ERROR);
	}

	decrypt_len = sizeof(nonces);
	if (eap_eke_decrypt_prot(&data->sess, pos, data->sess.pnonce_ps_len,
				 nonces, &decrypt_len) < 0) {
		wpa_printf(MSG_INFO, "EAP-EKE: Failed to decrypt PNonce_PS");
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_AUTHENTICATION_FAIL);
	}
	if (decrypt_len != (size_t) 2 * data->sess.nonce_len) {
		wpa_printf(MSG_INFO, "EAP-EKE: PNonce_PS protected data length does not match length of Nonce_P and Nonce_S");
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_AUTHENTICATION_FAIL);
	}
	wpa_hexdump_key(MSG_DEBUG, "EAP-EKE: Received Nonce_P | Nonce_S",
			nonces, 2 * data->sess.nonce_len);
	if (os_memcmp(data->nonce_p, nonces, data->sess.nonce_len) != 0) {
		wpa_printf(MSG_INFO, "EAP-EKE: Received Nonce_P does not match transmitted Nonce_P");
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_AUTHENTICATION_FAIL);
	}

	os_memcpy(data->nonce_s, nonces + data->sess.nonce_len,
		  data->sess.nonce_len);
	wpa_hexdump_key(MSG_DEBUG, "EAP-EKE: Nonce_S",
			data->nonce_s, data->sess.nonce_len);

	if (eap_eke_derive_ka(&data->sess, data->serverid, data->serverid_len,
			      data->peerid, data->peerid_len,
			      data->nonce_p, data->nonce_s) < 0) {
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}

	if (eap_eke_auth(&data->sess, "EAP-EKE server", data->msgs, auth_s) < 0)
	{
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}
	wpa_hexdump(MSG_DEBUG, "EAP-EKE: Auth_S", auth_s, data->sess.prf_len);
	if (os_memcmp_const(auth_s, pos + data->sess.pnonce_ps_len,
			    data->sess.prf_len) != 0) {
		wpa_printf(MSG_INFO, "EAP-EKE: Auth_S does not match");
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_AUTHENTICATION_FAIL);
	}

	wpa_printf(MSG_DEBUG, "EAP-EKE: Sending EAP-EKE-Confirm/Response");

	resp = eap_eke_build_msg(data, id,
				 data->sess.pnonce_len + data->sess.prf_len,
				 EAP_EKE_CONFIRM);
	if (resp == NULL) {
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}

	prot_len = wpabuf_tailroom(resp);
	if (eap_eke_prot(&data->sess, data->nonce_s, data->sess.nonce_len,
			 wpabuf_put(resp, 0), &prot_len) < 0) {
		wpabuf_free(resp);
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}
	wpabuf_put(resp, prot_len);

	auth = wpabuf_put(resp, data->sess.prf_len);
	if (eap_eke_auth(&data->sess, "EAP-EKE peer", data->msgs, auth) < 0) {
		wpabuf_free(resp);
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}
	wpa_hexdump(MSG_DEBUG, "EAP-EKE: Auth_P", auth, data->sess.prf_len);

	if (eap_eke_derive_msk(&data->sess, data->serverid, data->serverid_len,
			       data->peerid, data->peerid_len,
			       data->nonce_s, data->nonce_p,
			       data->msk, data->emsk) < 0) {
		wpa_printf(MSG_INFO, "EAP-EKE: Failed to derive MSK/EMSK");
		wpabuf_free(resp);
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}

	os_memset(data->dh_priv, 0, sizeof(data->dh_priv));
	eap_eke_session_clean(&data->sess);

	eap_eke_state(data, SUCCESS);
	ret->methodState = METHOD_MAY_CONT;
	ret->decision = DECISION_COND_SUCC;
	ret->allowNotifications = FALSE;

	return resp;
}