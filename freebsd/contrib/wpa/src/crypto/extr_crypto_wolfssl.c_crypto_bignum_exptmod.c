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
struct crypto_bignum {int dummy; } ;
typedef  int /*<<< orphan*/  mp_int ;

/* Variables and functions */
 scalar_t__ MP_OKAY ; 
 scalar_t__ TEST_FAIL () ; 
 scalar_t__ mp_exptmod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int crypto_bignum_exptmod(const struct crypto_bignum *b,
			  const struct crypto_bignum *e,
			  const struct crypto_bignum *m,
			  struct crypto_bignum *r)
{
	if (TEST_FAIL())
		return -1;

	return mp_exptmod((mp_int *) b, (mp_int *) e, (mp_int *) m,
			  (mp_int *) r) == MP_OKAY ?  0 : -1;
}