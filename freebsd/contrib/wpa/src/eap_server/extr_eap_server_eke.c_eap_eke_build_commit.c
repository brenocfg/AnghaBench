#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int /*<<< orphan*/  server_id_len; int /*<<< orphan*/  server_id; TYPE_1__* user; } ;
struct TYPE_5__ {int /*<<< orphan*/  dhcomp_len; int /*<<< orphan*/  dhgroup; } ;
struct eap_eke_data {int /*<<< orphan*/  msgs; TYPE_2__ sess; int /*<<< orphan*/  key; int /*<<< orphan*/  dh_priv; int /*<<< orphan*/  peerid_len; int /*<<< orphan*/  peerid; } ;
struct TYPE_4__ {int /*<<< orphan*/  password_len; int /*<<< orphan*/ * password; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_EKE_COMMIT ; 
 int /*<<< orphan*/  EAP_EKE_FAIL_PASSWD_NOT_FOUND ; 
 int /*<<< orphan*/  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR ; 
 int EAP_EKE_MAX_DH_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 struct wpabuf* eap_eke_build_failure (struct eap_eke_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_eke_build_msg (struct eap_eke_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_eke_derive_key (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_eke_dh_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ eap_eke_dhcomp (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_eke_fail (struct eap_eke_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_buf (int /*<<< orphan*/ ,struct wpabuf*) ; 
 scalar_t__ wpabuf_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * eap_eke_build_commit(struct eap_sm *sm,
					    struct eap_eke_data *data, u8 id)
{
	struct wpabuf *msg;
	u8 pub[EAP_EKE_MAX_DH_LEN];

	wpa_printf(MSG_DEBUG, "EAP-EKE: Request/Commit");

	if (sm->user == NULL || sm->user->password == NULL) {
		wpa_printf(MSG_INFO, "EAP-EKE: Password with not configured");
		eap_eke_fail(data, EAP_EKE_FAIL_PASSWD_NOT_FOUND);
		return eap_eke_build_failure(data, id);
	}

	if (eap_eke_derive_key(&data->sess, sm->user->password,
			       sm->user->password_len,
			       sm->server_id, sm->server_id_len,
			       data->peerid, data->peerid_len, data->key) < 0) {
		wpa_printf(MSG_INFO, "EAP-EKE: Failed to derive key");
		eap_eke_fail(data, EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
		return eap_eke_build_failure(data, id);
	}

	msg = eap_eke_build_msg(data, id, data->sess.dhcomp_len,
				EAP_EKE_COMMIT);
	if (msg == NULL) {
		eap_eke_fail(data, EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
		return eap_eke_build_failure(data, id);
	}

	/*
	 * y_s = g ^ x_s (mod p)
	 * x_s = random number 2 .. p-1
	 * temp = prf(0+, password)
	 * key = prf+(temp, ID_S | ID_P)
	 * DHComponent_S = Encr(key, y_s)
	 */

	if (eap_eke_dh_init(data->sess.dhgroup, data->dh_priv, pub) < 0) {
		wpa_printf(MSG_INFO, "EAP-EKE: Failed to initialize DH");
		eap_eke_fail(data, EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
		return eap_eke_build_failure(data, id);
	}

	if (eap_eke_dhcomp(&data->sess, data->key, pub,
			   wpabuf_put(msg, data->sess.dhcomp_len))
	    < 0) {
		wpa_printf(MSG_INFO, "EAP-EKE: Failed to build DHComponent_S");
		wpabuf_free(msg);
		eap_eke_fail(data, EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
		return eap_eke_build_failure(data, id);
	}

	if (wpabuf_resize(&data->msgs, wpabuf_len(msg)) < 0) {
		wpabuf_free(msg);
		eap_eke_fail(data, EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
		return eap_eke_build_failure(data, id);
	}
	wpabuf_put_buf(data->msgs, msg);

	return msg;
}