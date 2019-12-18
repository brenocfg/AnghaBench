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
struct dpp_authentication {int /*<<< orphan*/  secret_len; int /*<<< orphan*/  Lx_len; int /*<<< orphan*/  Lx; int /*<<< orphan*/  own_protocol_key; TYPE_2__* own_bi; TYPE_1__* peer_bi; } ;
struct TYPE_4__ {int /*<<< orphan*/  pubkey; } ;
struct TYPE_3__ {int /*<<< orphan*/  pubkey; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int BN_mod_add (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int EC_GROUP_get_order (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_private_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_public_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_clear_free (int /*<<< orphan*/ *) ; 
 int EC_POINT_get_affine_coordinates_GFp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EC_POINT_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ERR_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_EC_KEY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ dpp_bn2bin_pad (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpp_auth_derive_l_responder(struct dpp_authentication *auth)
{
	const EC_GROUP *group;
	EC_POINT *l = NULL;
	EC_KEY *BI = NULL, *bR = NULL, *pR = NULL;
	const EC_POINT *BI_point;
	BN_CTX *bnctx;
	BIGNUM *lx, *sum, *q;
	const BIGNUM *bR_bn, *pR_bn;
	int ret = -1;

	/* L = ((bR + pR) modulo q) * BI */

	bnctx = BN_CTX_new();
	sum = BN_new();
	q = BN_new();
	lx = BN_new();
	if (!bnctx || !sum || !q || !lx)
		goto fail;
	BI = EVP_PKEY_get1_EC_KEY(auth->peer_bi->pubkey);
	if (!BI)
		goto fail;
	BI_point = EC_KEY_get0_public_key(BI);
	group = EC_KEY_get0_group(BI);
	if (!group)
		goto fail;

	bR = EVP_PKEY_get1_EC_KEY(auth->own_bi->pubkey);
	pR = EVP_PKEY_get1_EC_KEY(auth->own_protocol_key);
	if (!bR || !pR)
		goto fail;
	bR_bn = EC_KEY_get0_private_key(bR);
	pR_bn = EC_KEY_get0_private_key(pR);
	if (!bR_bn || !pR_bn)
		goto fail;
	if (EC_GROUP_get_order(group, q, bnctx) != 1 ||
	    BN_mod_add(sum, bR_bn, pR_bn, q, bnctx) != 1)
		goto fail;
	l = EC_POINT_new(group);
	if (!l ||
	    EC_POINT_mul(group, l, NULL, BI_point, sum, bnctx) != 1 ||
	    EC_POINT_get_affine_coordinates_GFp(group, l, lx, NULL,
						bnctx) != 1) {
		wpa_printf(MSG_ERROR,
			   "OpenSSL: failed: %s",
			   ERR_error_string(ERR_get_error(), NULL));
		goto fail;
	}

	if (dpp_bn2bin_pad(lx, auth->Lx, auth->secret_len) < 0)
		goto fail;
	wpa_hexdump_key(MSG_DEBUG, "DPP: L.x", auth->Lx, auth->secret_len);
	auth->Lx_len = auth->secret_len;
	ret = 0;
fail:
	EC_POINT_clear_free(l);
	EC_KEY_free(BI);
	EC_KEY_free(bR);
	EC_KEY_free(pR);
	BN_clear_free(lx);
	BN_clear_free(sum);
	BN_free(q);
	BN_CTX_free(bnctx);
	return ret;
}