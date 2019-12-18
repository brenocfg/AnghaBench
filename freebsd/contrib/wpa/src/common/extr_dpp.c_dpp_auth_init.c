#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wpabuf {int dummy; } ;
struct hostapd_hw_modes {int dummy; } ;
struct dpp_curve_params {int dummy; } ;
struct dpp_bootstrap_info {int* pubkey_hash; int /*<<< orphan*/  pubkey; TYPE_1__* curve; } ;
struct dpp_authentication {int initiator; int waiting_auth_resp; int allowed_roles; int configurator; int* i_nonce; size_t secret_len; size_t Mx_len; int /*<<< orphan*/  req_msg; TYPE_1__* curve; struct dpp_bootstrap_info* own_bi; struct dpp_bootstrap_info* peer_bi; int /*<<< orphan*/  k1; int /*<<< orphan*/  Mx; void* own_protocol_key; void* msg_ctx; } ;
struct TYPE_3__ {size_t nonce_len; int prime_len; int /*<<< orphan*/  hash_len; } ;

/* Variables and functions */
 int DPP_CAPAB_CONFIGURATOR ; 
 scalar_t__ DPP_TEST_INVALID_I_BOOTSTRAP_KEY_HASH_AUTH_REQ ; 
 scalar_t__ DPP_TEST_INVALID_I_PROTO_KEY_AUTH_REQ ; 
 scalar_t__ DPP_TEST_INVALID_R_BOOTSTRAP_KEY_HASH_AUTH_REQ ; 
 scalar_t__ DPP_TEST_NO_I_BOOTSTRAP_KEY_HASH_AUTH_REQ ; 
 scalar_t__ DPP_TEST_NO_I_PROTO_KEY_AUTH_REQ ; 
 scalar_t__ DPP_TEST_NO_R_BOOTSTRAP_KEY_HASH_AUTH_REQ ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int SHA256_MAC_LEN ; 
 int /*<<< orphan*/  dpp_auth_build_req (struct dpp_authentication*,struct wpabuf*,size_t,int const*,int const*,unsigned int) ; 
 int /*<<< orphan*/  dpp_auth_deinit (struct dpp_authentication*) ; 
 scalar_t__ dpp_autogen_bootstrap_key (struct dpp_authentication*) ; 
 scalar_t__ dpp_derive_k1 (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dpp_ecdh (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 void* dpp_gen_keypair (TYPE_1__*) ; 
 struct wpabuf* dpp_get_pubkey_point (void*,int /*<<< orphan*/ ) ; 
 int const* dpp_nonce_override ; 
 size_t dpp_nonce_override_len ; 
 scalar_t__ dpp_prepare_channel_list (struct dpp_authentication*,struct hostapd_hw_modes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpp_protocol_key_override ; 
 scalar_t__ dpp_protocol_key_override_len ; 
 void* dpp_set_keypair (struct dpp_curve_params const**,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ dpp_test ; 
 scalar_t__ dpp_test_gen_invalid_key (struct wpabuf*,TYPE_1__*) ; 
 int /*<<< orphan*/  os_memcpy (int*,int const*,int) ; 
 struct dpp_authentication* os_zalloc (int) ; 
 scalar_t__ random_get_bytes (int*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

struct dpp_authentication * dpp_auth_init(void *msg_ctx,
					  struct dpp_bootstrap_info *peer_bi,
					  struct dpp_bootstrap_info *own_bi,
					  u8 dpp_allowed_roles,
					  unsigned int neg_freq,
					  struct hostapd_hw_modes *own_modes,
					  u16 num_modes)
{
	struct dpp_authentication *auth;
	size_t nonce_len;
	size_t secret_len;
	struct wpabuf *pi = NULL;
	const u8 *r_pubkey_hash, *i_pubkey_hash;
#ifdef CONFIG_TESTING_OPTIONS
	u8 test_hash[SHA256_MAC_LEN];
#endif /* CONFIG_TESTING_OPTIONS */

	auth = os_zalloc(sizeof(*auth));
	if (!auth)
		return NULL;
	auth->msg_ctx = msg_ctx;
	auth->initiator = 1;
	auth->waiting_auth_resp = 1;
	auth->allowed_roles = dpp_allowed_roles;
	auth->configurator = !!(dpp_allowed_roles & DPP_CAPAB_CONFIGURATOR);
	auth->peer_bi = peer_bi;
	auth->own_bi = own_bi;
	auth->curve = peer_bi->curve;

	if (dpp_autogen_bootstrap_key(auth) < 0 ||
	    dpp_prepare_channel_list(auth, own_modes, num_modes) < 0)
		goto fail;

#ifdef CONFIG_TESTING_OPTIONS
	if (dpp_nonce_override_len > 0) {
		wpa_printf(MSG_INFO, "DPP: TESTING - override I-nonce");
		nonce_len = dpp_nonce_override_len;
		os_memcpy(auth->i_nonce, dpp_nonce_override, nonce_len);
	} else {
		nonce_len = auth->curve->nonce_len;
		if (random_get_bytes(auth->i_nonce, nonce_len)) {
			wpa_printf(MSG_ERROR,
				   "DPP: Failed to generate I-nonce");
			goto fail;
		}
	}
#else /* CONFIG_TESTING_OPTIONS */
	nonce_len = auth->curve->nonce_len;
	if (random_get_bytes(auth->i_nonce, nonce_len)) {
		wpa_printf(MSG_ERROR, "DPP: Failed to generate I-nonce");
		goto fail;
	}
#endif /* CONFIG_TESTING_OPTIONS */
	wpa_hexdump(MSG_DEBUG, "DPP: I-nonce", auth->i_nonce, nonce_len);

#ifdef CONFIG_TESTING_OPTIONS
	if (dpp_protocol_key_override_len) {
		const struct dpp_curve_params *tmp_curve;

		wpa_printf(MSG_INFO,
			   "DPP: TESTING - override protocol key");
		auth->own_protocol_key = dpp_set_keypair(
			&tmp_curve, dpp_protocol_key_override,
			dpp_protocol_key_override_len);
	} else {
		auth->own_protocol_key = dpp_gen_keypair(auth->curve);
	}
#else /* CONFIG_TESTING_OPTIONS */
	auth->own_protocol_key = dpp_gen_keypair(auth->curve);
#endif /* CONFIG_TESTING_OPTIONS */
	if (!auth->own_protocol_key)
		goto fail;

	pi = dpp_get_pubkey_point(auth->own_protocol_key, 0);
	if (!pi)
		goto fail;

	/* ECDH: M = pI * BR */
	if (dpp_ecdh(auth->own_protocol_key, auth->peer_bi->pubkey,
		     auth->Mx, &secret_len) < 0)
		goto fail;
	auth->secret_len = secret_len;

	wpa_hexdump_key(MSG_DEBUG, "DPP: ECDH shared secret (M.x)",
			auth->Mx, auth->secret_len);
	auth->Mx_len = auth->secret_len;

	if (dpp_derive_k1(auth->Mx, auth->secret_len, auth->k1,
			  auth->curve->hash_len) < 0)
		goto fail;

	r_pubkey_hash = auth->peer_bi->pubkey_hash;
	i_pubkey_hash = auth->own_bi->pubkey_hash;

#ifdef CONFIG_TESTING_OPTIONS
	if (dpp_test == DPP_TEST_NO_R_BOOTSTRAP_KEY_HASH_AUTH_REQ) {
		wpa_printf(MSG_INFO, "DPP: TESTING - no R-Bootstrap Key Hash");
		r_pubkey_hash = NULL;
	} else if (dpp_test == DPP_TEST_INVALID_R_BOOTSTRAP_KEY_HASH_AUTH_REQ) {
		wpa_printf(MSG_INFO,
			   "DPP: TESTING - invalid R-Bootstrap Key Hash");
		os_memcpy(test_hash, r_pubkey_hash, SHA256_MAC_LEN);
		test_hash[SHA256_MAC_LEN - 1] ^= 0x01;
		r_pubkey_hash = test_hash;
	} else if (dpp_test == DPP_TEST_NO_I_BOOTSTRAP_KEY_HASH_AUTH_REQ) {
		wpa_printf(MSG_INFO, "DPP: TESTING - no I-Bootstrap Key Hash");
		i_pubkey_hash = NULL;
	} else if (dpp_test == DPP_TEST_INVALID_I_BOOTSTRAP_KEY_HASH_AUTH_REQ) {
		wpa_printf(MSG_INFO,
			   "DPP: TESTING - invalid I-Bootstrap Key Hash");
		os_memcpy(test_hash, i_pubkey_hash, SHA256_MAC_LEN);
		test_hash[SHA256_MAC_LEN - 1] ^= 0x01;
		i_pubkey_hash = test_hash;
	} else if (dpp_test == DPP_TEST_NO_I_PROTO_KEY_AUTH_REQ) {
		wpa_printf(MSG_INFO, "DPP: TESTING - no I-Proto Key");
		wpabuf_free(pi);
		pi = NULL;
	} else if (dpp_test == DPP_TEST_INVALID_I_PROTO_KEY_AUTH_REQ) {
		wpa_printf(MSG_INFO, "DPP: TESTING - invalid I-Proto Key");
		wpabuf_free(pi);
		pi = wpabuf_alloc(2 * auth->curve->prime_len);
		if (!pi || dpp_test_gen_invalid_key(pi, auth->curve) < 0)
			goto fail;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	auth->req_msg = dpp_auth_build_req(auth, pi, nonce_len, r_pubkey_hash,
					   i_pubkey_hash, neg_freq);
	if (!auth->req_msg)
		goto fail;

out:
	wpabuf_free(pi);
	return auth;
fail:
	dpp_auth_deinit(auth);
	auth = NULL;
	goto out;
}