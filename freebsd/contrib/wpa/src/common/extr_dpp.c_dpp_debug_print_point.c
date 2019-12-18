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
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 char* BN_bn2hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int EC_POINT_get_affine_coordinates_GFp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  wpa_debug_show_keys ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,char*,char*) ; 

__attribute__((used)) static void dpp_debug_print_point(const char *title, const EC_GROUP *group,
				  const EC_POINT *point)
{
	BIGNUM *x, *y;
	BN_CTX *ctx;
	char *x_str = NULL, *y_str = NULL;

	if (!wpa_debug_show_keys)
		return;

	ctx = BN_CTX_new();
	x = BN_new();
	y = BN_new();
	if (!ctx || !x || !y ||
	    EC_POINT_get_affine_coordinates_GFp(group, point, x, y, ctx) != 1)
		goto fail;

	x_str = BN_bn2hex(x);
	y_str = BN_bn2hex(y);
	if (!x_str || !y_str)
		goto fail;

	wpa_printf(MSG_DEBUG, "%s (%s,%s)", title, x_str, y_str);

fail:
	OPENSSL_free(x_str);
	OPENSSL_free(y_str);
	BN_free(x);
	BN_free(y);
	BN_CTX_free(ctx);
}