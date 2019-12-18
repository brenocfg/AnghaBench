#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const u8 ;
typedef  struct wpabuf const wpabuf ;
struct eap_sm {int dummy; } ;
struct eap_method_ret {int dummy; } ;
struct TYPE_6__ {int dhcomp_len; int /*<<< orphan*/  nonce_len; scalar_t__ pnonce_len; int /*<<< orphan*/  dhgroup; } ;
struct eap_eke_data {scalar_t__ state; int /*<<< orphan*/  msgs; TYPE_1__ sess; int /*<<< orphan*/  nonce_p; int /*<<< orphan*/  peerid_len; int /*<<< orphan*/  peerid; int /*<<< orphan*/  serverid_len; int /*<<< orphan*/  serverid; int /*<<< orphan*/  dh_priv; } ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 scalar_t__ COMMIT ; 
 int /*<<< orphan*/  CONFIRM ; 
 int /*<<< orphan*/  EAP_EKE_COMMIT ; 
 int /*<<< orphan*/  EAP_EKE_FAIL_PASSWD_NOT_FOUND ; 
 int /*<<< orphan*/  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EAP_EKE_FAIL_PROTO_ERROR ; 
 int EAP_EKE_MAX_DH_LEN ; 
 int EAP_EKE_MAX_KEY_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 struct wpabuf const* eap_eke_build_fail (struct eap_eke_data*,struct eap_method_ret*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 struct wpabuf const* eap_eke_build_msg (struct eap_eke_data*,int /*<<< orphan*/  const,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_eke_derive_ke_ki (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_eke_derive_key (TYPE_1__*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ eap_eke_dh_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ eap_eke_dhcomp (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ eap_eke_prot (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t*) ; 
 scalar_t__ eap_eke_shared_secret (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  eap_eke_state (struct eap_eke_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* eap_get_config_password (struct eap_sm*,size_t*) ; 
 int /*<<< orphan*/  const eap_get_id (struct wpabuf const*) ; 
 int /*<<< orphan*/  forced_memzero (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf const*) ; 
 scalar_t__ wpabuf_len (struct wpabuf const*) ; 
 int /*<<< orphan*/  const* wpabuf_put (struct wpabuf const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_buf (int /*<<< orphan*/ ,struct wpabuf const*) ; 
 scalar_t__ wpabuf_resize (int /*<<< orphan*/ *,scalar_t__) ; 
 size_t wpabuf_tailroom (struct wpabuf const*) ; 

__attribute__((used)) static struct wpabuf * eap_eke_process_commit(struct eap_sm *sm,
					      struct eap_eke_data *data,
					      struct eap_method_ret *ret,
					      const struct wpabuf *reqData,
					      const u8 *payload,
					      size_t payload_len)
{
	struct wpabuf *resp;
	const u8 *pos, *end, *dhcomp;
	size_t prot_len;
	u8 *rpos;
	u8 key[EAP_EKE_MAX_KEY_LEN];
	u8 pub[EAP_EKE_MAX_DH_LEN];
	const u8 *password;
	size_t password_len;
	u8 id = eap_get_id(reqData);

	if (data->state != COMMIT) {
		wpa_printf(MSG_DEBUG, "EAP-EKE: EAP-EKE-Commit/Request received in unexpected state (%d)", data->state);
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PROTO_ERROR);
	}

	wpa_printf(MSG_DEBUG, "EAP-EKE: Received EAP-EKE-Commit/Request");

	password = eap_get_config_password(sm, &password_len);
	if (password == NULL) {
		wpa_printf(MSG_INFO, "EAP-EKE: No password configured!");
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PASSWD_NOT_FOUND);
	}

	pos = payload;
	end = payload + payload_len;

	if (pos + data->sess.dhcomp_len > end) {
		wpa_printf(MSG_DEBUG, "EAP-EKE: Too short EAP-EKE-Commit");
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PROTO_ERROR);
	}

	wpa_hexdump(MSG_DEBUG, "EAP-EKE: DHComponent_S",
		    pos, data->sess.dhcomp_len);
	dhcomp = pos;
	pos += data->sess.dhcomp_len;
	wpa_hexdump(MSG_DEBUG, "EAP-EKE: CBValue", pos, end - pos);

	/*
	 * temp = prf(0+, password)
	 * key = prf+(temp, ID_S | ID_P)
	 */
	if (eap_eke_derive_key(&data->sess, password, password_len,
			       data->serverid, data->serverid_len,
			       data->peerid, data->peerid_len, key) < 0) {
		wpa_printf(MSG_INFO, "EAP-EKE: Failed to derive key");
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}

	/*
	 * y_p = g ^ x_p (mod p)
	 * x_p = random number 2 .. p-1
	 */
	if (eap_eke_dh_init(data->sess.dhgroup, data->dh_priv, pub) < 0) {
		wpa_printf(MSG_INFO, "EAP-EKE: Failed to initialize DH");
		forced_memzero(key, sizeof(key));
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}

	if (eap_eke_shared_secret(&data->sess, key, data->dh_priv, dhcomp) < 0)
	{
		wpa_printf(MSG_INFO, "EAP-EKE: Failed to derive shared secret");
		forced_memzero(key, sizeof(key));
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}

	if (eap_eke_derive_ke_ki(&data->sess,
				 data->serverid, data->serverid_len,
				 data->peerid, data->peerid_len) < 0) {
		wpa_printf(MSG_INFO, "EAP-EKE: Failed to derive Ke/Ki");
		forced_memzero(key, sizeof(key));
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}

	wpa_printf(MSG_DEBUG, "EAP-EKE: Sending EAP-EKE-Commit/Response");

	resp = eap_eke_build_msg(data, id,
				 data->sess.dhcomp_len + data->sess.pnonce_len,
				 EAP_EKE_COMMIT);
	if (resp == NULL) {
		forced_memzero(key, sizeof(key));
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}

	/* DHComponent_P = Encr(key, y_p) */
	rpos = wpabuf_put(resp, data->sess.dhcomp_len);
	if (eap_eke_dhcomp(&data->sess, key, pub, rpos) < 0) {
		wpabuf_free(resp);
		wpa_printf(MSG_INFO, "EAP-EKE: Failed to build DHComponent_P");
		forced_memzero(key, sizeof(key));
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}
	forced_memzero(key, sizeof(key));

	wpa_hexdump(MSG_DEBUG, "EAP-EKE: DHComponent_P",
		    rpos, data->sess.dhcomp_len);

	if (random_get_bytes(data->nonce_p, data->sess.nonce_len)) {
		wpabuf_free(resp);
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}
	wpa_hexdump_key(MSG_DEBUG, "EAP-EKE: Nonce_P",
			data->nonce_p, data->sess.nonce_len);
	prot_len = wpabuf_tailroom(resp);
	if (eap_eke_prot(&data->sess, data->nonce_p, data->sess.nonce_len,
			 wpabuf_put(resp, 0), &prot_len) < 0) {
		wpabuf_free(resp);
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}
	wpa_hexdump(MSG_DEBUG, "EAP-EKE: PNonce_P",
		    wpabuf_put(resp, 0), prot_len);
	wpabuf_put(resp, prot_len);

	/* TODO: CBValue */

	if (wpabuf_resize(&data->msgs, wpabuf_len(reqData) + wpabuf_len(resp))
	    < 0) {
		wpabuf_free(resp);
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}
	wpabuf_put_buf(data->msgs, reqData);
	wpabuf_put_buf(data->msgs, resp);

	eap_eke_state(data, CONFIRM);

	return resp;
}