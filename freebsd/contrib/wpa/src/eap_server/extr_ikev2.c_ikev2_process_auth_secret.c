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
typedef  scalar_t__ u8 ;
struct ikev2_prf_alg {size_t hash_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  prf; } ;
struct ikev2_initiator_data {TYPE_1__ proposal; int /*<<< orphan*/ * r_sign_msg; int /*<<< orphan*/  key_pad_len; int /*<<< orphan*/  key_pad; int /*<<< orphan*/  i_nonce_len; int /*<<< orphan*/  i_nonce; int /*<<< orphan*/  shared_secret_len; int /*<<< orphan*/  shared_secret; int /*<<< orphan*/  keys; int /*<<< orphan*/  IDr_type; int /*<<< orphan*/  IDr_len; int /*<<< orphan*/  IDr; } ;

/* Variables and functions */
 scalar_t__ AUTH_SHARED_KEY_MIC ; 
 int IKEV2_MAX_HASH_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ ikev2_derive_auth_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct ikev2_prf_alg* ikev2_get_prf (int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp_const (scalar_t__ const*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ikev2_process_auth_secret(struct ikev2_initiator_data *data,
				     u8 method, const u8 *auth,
				     size_t auth_len)
{
	u8 auth_data[IKEV2_MAX_HASH_LEN];
	const struct ikev2_prf_alg *prf;

	if (method != AUTH_SHARED_KEY_MIC) {
		wpa_printf(MSG_INFO, "IKEV2: Unsupported authentication "
			   "method %d", method);
		return -1;
	}

	/* msg | Ni | prf(SK_pr,IDr') */
	if (ikev2_derive_auth_data(data->proposal.prf, data->r_sign_msg,
				   data->IDr, data->IDr_len, data->IDr_type,
				   &data->keys, 0, data->shared_secret,
				   data->shared_secret_len,
				   data->i_nonce, data->i_nonce_len,
				   data->key_pad, data->key_pad_len,
				   auth_data) < 0) {
		wpa_printf(MSG_INFO, "IKEV2: Could not derive AUTH data");
		return -1;
	}

	wpabuf_free(data->r_sign_msg);
	data->r_sign_msg = NULL;

	prf = ikev2_get_prf(data->proposal.prf);
	if (prf == NULL)
		return -1;

	if (auth_len != prf->hash_len ||
	    os_memcmp_const(auth, auth_data, auth_len) != 0) {
		wpa_printf(MSG_INFO, "IKEV2: Invalid Authentication Data");
		wpa_hexdump(MSG_DEBUG, "IKEV2: Received Authentication Data",
			    auth, auth_len);
		wpa_hexdump(MSG_DEBUG, "IKEV2: Expected Authentication Data",
			    auth_data, prf->hash_len);
		return -1;
	}

	wpa_printf(MSG_DEBUG, "IKEV2: Peer authenticated successfully "
		   "using shared keys");

	return 0;
}