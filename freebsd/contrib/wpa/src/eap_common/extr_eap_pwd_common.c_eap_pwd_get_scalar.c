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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_bignum {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  group; } ;
typedef  TYPE_1__ EAP_PWD_group ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ crypto_bignum_cmp (struct crypto_bignum*,struct crypto_bignum const*) ; 
 int /*<<< orphan*/  crypto_bignum_deinit (struct crypto_bignum*,int /*<<< orphan*/ ) ; 
 struct crypto_bignum* crypto_bignum_init_set (int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ crypto_bignum_is_one (struct crypto_bignum*) ; 
 scalar_t__ crypto_bignum_is_zero (struct crypto_bignum*) ; 
 struct crypto_bignum* crypto_ec_get_order (int /*<<< orphan*/ ) ; 
 size_t crypto_ec_order_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

struct crypto_bignum * eap_pwd_get_scalar(EAP_PWD_group *group, const u8 *buf)
{
	struct crypto_bignum *scalar;
	const struct crypto_bignum *order;
	size_t order_len;

	order = crypto_ec_get_order(group->group);
	order_len = crypto_ec_order_len(group->group);

	/* RFC 5931, 2.8.5.2: 1 < scalar < r */
	scalar = crypto_bignum_init_set(buf, order_len);
	if (!scalar || crypto_bignum_is_zero(scalar) ||
	    crypto_bignum_is_one(scalar) ||
	    crypto_bignum_cmp(scalar, order) >= 0) {
		wpa_printf(MSG_INFO, "EAP-pwd: received scalar is invalid");
		crypto_bignum_deinit(scalar, 0);
		scalar = NULL;
	}

	return scalar;
}