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
struct crypto_bignum {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  group; } ;
typedef  TYPE_1__ EAP_PWD_group ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_ec_get_order (int /*<<< orphan*/ ) ; 
 int dragonfly_generate_scalar (int /*<<< orphan*/ ,struct crypto_bignum*,struct crypto_bignum*,struct crypto_bignum*) ; 

int eap_pwd_get_rand_mask(EAP_PWD_group *group, struct crypto_bignum *_rand,
			  struct crypto_bignum *_mask,
			  struct crypto_bignum *scalar)
{
	return dragonfly_generate_scalar(crypto_ec_get_order(group->group),
					 _rand, _mask, scalar);
}