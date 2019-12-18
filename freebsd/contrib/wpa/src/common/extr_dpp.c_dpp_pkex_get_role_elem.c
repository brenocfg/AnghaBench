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
struct dpp_curve_params {size_t prime_len; int ike_group; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_new_by_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_txt2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dpp_set_pubkey_point_group (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/ * pkex_init_x_bp_p256r1 ; 
 int /*<<< orphan*/ * pkex_init_x_bp_p384r1 ; 
 int /*<<< orphan*/ * pkex_init_x_bp_p512r1 ; 
 int /*<<< orphan*/ * pkex_init_x_p256 ; 
 int /*<<< orphan*/ * pkex_init_x_p384 ; 
 int /*<<< orphan*/ * pkex_init_x_p521 ; 
 int /*<<< orphan*/ * pkex_init_y_bp_p256r1 ; 
 int /*<<< orphan*/ * pkex_init_y_bp_p384r1 ; 
 int /*<<< orphan*/ * pkex_init_y_bp_p512r1 ; 
 int /*<<< orphan*/ * pkex_init_y_p256 ; 
 int /*<<< orphan*/ * pkex_init_y_p384 ; 
 int /*<<< orphan*/ * pkex_init_y_p521 ; 
 int /*<<< orphan*/ * pkex_resp_x_bp_p256r1 ; 
 int /*<<< orphan*/ * pkex_resp_x_bp_p384r1 ; 
 int /*<<< orphan*/ * pkex_resp_x_bp_p512r1 ; 
 int /*<<< orphan*/ * pkex_resp_x_p256 ; 
 int /*<<< orphan*/ * pkex_resp_x_p384 ; 
 int /*<<< orphan*/ * pkex_resp_x_p521 ; 
 int /*<<< orphan*/ * pkex_resp_y_bp_p256r1 ; 
 int /*<<< orphan*/ * pkex_resp_y_bp_p384r1 ; 
 int /*<<< orphan*/ * pkex_resp_y_bp_p512r1 ; 
 int /*<<< orphan*/ * pkex_resp_y_p256 ; 
 int /*<<< orphan*/ * pkex_resp_y_p384 ; 
 int /*<<< orphan*/ * pkex_resp_y_p521 ; 

__attribute__((used)) static EVP_PKEY * dpp_pkex_get_role_elem(const struct dpp_curve_params *curve,
					 int init)
{
	EC_GROUP *group;
	size_t len = curve->prime_len;
	const u8 *x, *y;
	EVP_PKEY *res;

	switch (curve->ike_group) {
	case 19:
		x = init ? pkex_init_x_p256 : pkex_resp_x_p256;
		y = init ? pkex_init_y_p256 : pkex_resp_y_p256;
		break;
	case 20:
		x = init ? pkex_init_x_p384 : pkex_resp_x_p384;
		y = init ? pkex_init_y_p384 : pkex_resp_y_p384;
		break;
	case 21:
		x = init ? pkex_init_x_p521 : pkex_resp_x_p521;
		y = init ? pkex_init_y_p521 : pkex_resp_y_p521;
		break;
	case 28:
		x = init ? pkex_init_x_bp_p256r1 : pkex_resp_x_bp_p256r1;
		y = init ? pkex_init_y_bp_p256r1 : pkex_resp_y_bp_p256r1;
		break;
	case 29:
		x = init ? pkex_init_x_bp_p384r1 : pkex_resp_x_bp_p384r1;
		y = init ? pkex_init_y_bp_p384r1 : pkex_resp_y_bp_p384r1;
		break;
	case 30:
		x = init ? pkex_init_x_bp_p512r1 : pkex_resp_x_bp_p512r1;
		y = init ? pkex_init_y_bp_p512r1 : pkex_resp_y_bp_p512r1;
		break;
	default:
		return NULL;
	}

	group = EC_GROUP_new_by_curve_name(OBJ_txt2nid(curve->name));
	if (!group)
		return NULL;
	res = dpp_set_pubkey_point_group(group, x, y, len);
	EC_GROUP_free(group);
	return res;
}