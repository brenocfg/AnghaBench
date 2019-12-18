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
struct crypto_bignum {int dummy; } ;

/* Variables and functions */
 scalar_t__ crypto_bignum_cmp (struct crypto_bignum*,struct crypto_bignum const*) ; 
 int /*<<< orphan*/  crypto_bignum_deinit (struct crypto_bignum*,int /*<<< orphan*/ ) ; 
 struct crypto_bignum* crypto_bignum_init_set (int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ crypto_bignum_is_zero (struct crypto_bignum*) ; 

__attribute__((used)) static int eap_pwd_element_coord_ok(const struct crypto_bignum *prime,
				    const u8 *buf, size_t len)
{
	struct crypto_bignum *val;
	int ok = 1;

	val = crypto_bignum_init_set(buf, len);
	if (!val || crypto_bignum_is_zero(val) ||
	    crypto_bignum_cmp(val, prime) >= 0)
		ok = 0;
	crypto_bignum_deinit(val, 0);
	return ok;
}