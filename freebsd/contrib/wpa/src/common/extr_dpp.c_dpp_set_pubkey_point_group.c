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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/ * BN_bin2bn (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new () ; 
 int /*<<< orphan*/  EC_KEY_set_asn1_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EC_KEY_set_group (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int EC_KEY_set_public_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 scalar_t__ EC_POINT_is_at_infinity (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_is_on_curve (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_set_affine_coordinates_GFp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int EVP_PKEY_set1_EC_KEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  OPENSSL_EC_NAMED_CURVE ; 
 int /*<<< orphan*/  dpp_debug_print_point (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static EVP_PKEY * dpp_set_pubkey_point_group(const EC_GROUP *group,
					     const u8 *buf_x, const u8 *buf_y,
					     size_t len)
{
	EC_KEY *eckey = NULL;
	BN_CTX *ctx;
	EC_POINT *point = NULL;
	BIGNUM *x = NULL, *y = NULL;
	EVP_PKEY *pkey = NULL;

	ctx = BN_CTX_new();
	if (!ctx) {
		wpa_printf(MSG_ERROR, "DPP: Out of memory");
		return NULL;
	}

	point = EC_POINT_new(group);
	x = BN_bin2bn(buf_x, len, NULL);
	y = BN_bin2bn(buf_y, len, NULL);
	if (!point || !x || !y) {
		wpa_printf(MSG_ERROR, "DPP: Out of memory");
		goto fail;
	}

	if (!EC_POINT_set_affine_coordinates_GFp(group, point, x, y, ctx)) {
		wpa_printf(MSG_ERROR,
			   "DPP: OpenSSL: EC_POINT_set_affine_coordinates_GFp failed: %s",
			   ERR_error_string(ERR_get_error(), NULL));
		goto fail;
	}

	if (!EC_POINT_is_on_curve(group, point, ctx) ||
	    EC_POINT_is_at_infinity(group, point)) {
		wpa_printf(MSG_ERROR, "DPP: Invalid point");
		goto fail;
	}
	dpp_debug_print_point("DPP: dpp_set_pubkey_point_group", group, point);

	eckey = EC_KEY_new();
	if (!eckey ||
	    EC_KEY_set_group(eckey, group) != 1 ||
	    EC_KEY_set_public_key(eckey, point) != 1) {
		wpa_printf(MSG_ERROR,
			   "DPP: Failed to set EC_KEY: %s",
			   ERR_error_string(ERR_get_error(), NULL));
		goto fail;
	}
	EC_KEY_set_asn1_flag(eckey, OPENSSL_EC_NAMED_CURVE);

	pkey = EVP_PKEY_new();
	if (!pkey || EVP_PKEY_set1_EC_KEY(pkey, eckey) != 1) {
		wpa_printf(MSG_ERROR, "DPP: Could not create EVP_PKEY");
		goto fail;
	}

out:
	BN_free(x);
	BN_free(y);
	EC_KEY_free(eckey);
	EC_POINT_free(point);
	BN_CTX_free(ctx);
	return pkey;
fail:
	EVP_PKEY_free(pkey);
	pkey = NULL;
	goto out;
}