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
struct wpabuf {int dummy; } ;
struct dpp_pkex {int /*<<< orphan*/  Mx; int /*<<< orphan*/  identifier; void* x; int /*<<< orphan*/  code; int /*<<< orphan*/  own_mac; TYPE_1__* own_bi; } ;
struct dpp_curve_params {int prime_len; int ike_group; } ;
struct TYPE_2__ {struct dpp_curve_params* curve; } ;
typedef  int /*<<< orphan*/  const EC_POINT ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int DPP_ATTR_CODE_IDENTIFIER ; 
 int DPP_ATTR_ENCRYPTED_KEY ; 
 int DPP_ATTR_FINITE_CYCLIC_GROUP ; 
 int /*<<< orphan*/  DPP_PA_PKEX_EXCHANGE_REQ ; 
 scalar_t__ DPP_TEST_INVALID_ENCRYPTED_KEY_PKEX_EXCHANGE_REQ ; 
 scalar_t__ DPP_TEST_NO_ENCRYPTED_KEY_PKEX_EXCHANGE_REQ ; 
 scalar_t__ DPP_TEST_NO_FINITE_CYCLIC_GROUP_PKEX_EXCHANGE_REQ ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* EC_KEY_get0_public_key (int /*<<< orphan*/ *) ; 
 int EC_POINT_add (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/  const*) ; 
 int EC_POINT_get_affine_coordinates_GFp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* EC_POINT_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_EC_KEY (void*) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 struct wpabuf* dpp_alloc_msg (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ dpp_bn2bin_pad (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dpp_debug_print_point (char*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 void* dpp_gen_keypair (struct dpp_curve_params const*) ; 
 int /*<<< orphan*/  const* dpp_pkex_derive_Qi (struct dpp_curve_params const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dpp_pkex_ephemeral_key_override ; 
 scalar_t__ dpp_pkex_ephemeral_key_override_len ; 
 void* dpp_set_keypair (struct dpp_curve_params const**,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ dpp_test ; 
 scalar_t__ dpp_test_gen_invalid_key (struct wpabuf*,struct dpp_curve_params const*) ; 
 int os_strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * dpp_pkex_build_exchange_req(struct dpp_pkex *pkex)
{
	EC_KEY *X_ec = NULL;
	const EC_POINT *X_point;
	BN_CTX *bnctx = NULL;
	EC_GROUP *group = NULL;
	EC_POINT *Qi = NULL, *M = NULL;
	struct wpabuf *M_buf = NULL;
	BIGNUM *Mx = NULL, *My = NULL;
	struct wpabuf *msg = NULL;
	size_t attr_len;
	const struct dpp_curve_params *curve = pkex->own_bi->curve;

	wpa_printf(MSG_DEBUG, "DPP: Build PKEX Exchange Request");

	/* Qi = H(MAC-Initiator | [identifier |] code) * Pi */
	bnctx = BN_CTX_new();
	if (!bnctx)
		goto fail;
	Qi = dpp_pkex_derive_Qi(curve, pkex->own_mac, pkex->code,
				pkex->identifier, bnctx, &group);
	if (!Qi)
		goto fail;

	/* Generate a random ephemeral keypair x/X */
#ifdef CONFIG_TESTING_OPTIONS
	if (dpp_pkex_ephemeral_key_override_len) {
		const struct dpp_curve_params *tmp_curve;

		wpa_printf(MSG_INFO,
			   "DPP: TESTING - override ephemeral key x/X");
		pkex->x = dpp_set_keypair(&tmp_curve,
					  dpp_pkex_ephemeral_key_override,
					  dpp_pkex_ephemeral_key_override_len);
	} else {
		pkex->x = dpp_gen_keypair(curve);
	}
#else /* CONFIG_TESTING_OPTIONS */
	pkex->x = dpp_gen_keypair(curve);
#endif /* CONFIG_TESTING_OPTIONS */
	if (!pkex->x)
		goto fail;

	/* M = X + Qi */
	X_ec = EVP_PKEY_get1_EC_KEY(pkex->x);
	if (!X_ec)
		goto fail;
	X_point = EC_KEY_get0_public_key(X_ec);
	if (!X_point)
		goto fail;
	dpp_debug_print_point("DPP: X", group, X_point);
	M = EC_POINT_new(group);
	Mx = BN_new();
	My = BN_new();
	if (!M || !Mx || !My ||
	    EC_POINT_add(group, M, X_point, Qi, bnctx) != 1 ||
	    EC_POINT_get_affine_coordinates_GFp(group, M, Mx, My, bnctx) != 1)
		goto fail;
	dpp_debug_print_point("DPP: M", group, M);

	/* Initiator -> Responder: group, [identifier,] M */
	attr_len = 4 + 2;
	if (pkex->identifier)
		attr_len += 4 + os_strlen(pkex->identifier);
	attr_len += 4 + 2 * curve->prime_len;
	msg = dpp_alloc_msg(DPP_PA_PKEX_EXCHANGE_REQ, attr_len);
	if (!msg)
		goto fail;

#ifdef CONFIG_TESTING_OPTIONS
	if (dpp_test == DPP_TEST_NO_FINITE_CYCLIC_GROUP_PKEX_EXCHANGE_REQ) {
		wpa_printf(MSG_INFO, "DPP: TESTING - no Finite Cyclic Group");
		goto skip_finite_cyclic_group;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	/* Finite Cyclic Group attribute */
	wpabuf_put_le16(msg, DPP_ATTR_FINITE_CYCLIC_GROUP);
	wpabuf_put_le16(msg, 2);
	wpabuf_put_le16(msg, curve->ike_group);

#ifdef CONFIG_TESTING_OPTIONS
skip_finite_cyclic_group:
#endif /* CONFIG_TESTING_OPTIONS */

	/* Code Identifier attribute */
	if (pkex->identifier) {
		wpabuf_put_le16(msg, DPP_ATTR_CODE_IDENTIFIER);
		wpabuf_put_le16(msg, os_strlen(pkex->identifier));
		wpabuf_put_str(msg, pkex->identifier);
	}

#ifdef CONFIG_TESTING_OPTIONS
	if (dpp_test == DPP_TEST_NO_ENCRYPTED_KEY_PKEX_EXCHANGE_REQ) {
		wpa_printf(MSG_INFO, "DPP: TESTING - no Encrypted Key");
		goto out;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	/* M in Encrypted Key attribute */
	wpabuf_put_le16(msg, DPP_ATTR_ENCRYPTED_KEY);
	wpabuf_put_le16(msg, 2 * curve->prime_len);

#ifdef CONFIG_TESTING_OPTIONS
	if (dpp_test == DPP_TEST_INVALID_ENCRYPTED_KEY_PKEX_EXCHANGE_REQ) {
		wpa_printf(MSG_INFO, "DPP: TESTING - invalid Encrypted Key");
		if (dpp_test_gen_invalid_key(msg, curve) < 0)
			goto fail;
		goto out;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	if (dpp_bn2bin_pad(Mx, wpabuf_put(msg, curve->prime_len),
			   curve->prime_len) < 0 ||
	    dpp_bn2bin_pad(Mx, pkex->Mx, curve->prime_len) < 0 ||
	    dpp_bn2bin_pad(My, wpabuf_put(msg, curve->prime_len),
			   curve->prime_len) < 0)
		goto fail;

out:
	wpabuf_free(M_buf);
	EC_KEY_free(X_ec);
	EC_POINT_free(M);
	EC_POINT_free(Qi);
	BN_clear_free(Mx);
	BN_clear_free(My);
	BN_CTX_free(bnctx);
	EC_GROUP_free(group);
	return msg;
fail:
	wpa_printf(MSG_INFO, "DPP: Failed to build PKEX Exchange Request");
	wpabuf_free(msg);
	msg = NULL;
	goto out;
}