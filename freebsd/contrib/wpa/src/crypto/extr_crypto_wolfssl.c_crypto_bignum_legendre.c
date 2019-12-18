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
 int MP_OKAY ; 
 scalar_t__ TEST_FAIL () ; 
 int /*<<< orphan*/  mp_clear (int /*<<< orphan*/ *) ; 
 int mp_exptmod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mp_init (int /*<<< orphan*/ *) ; 
 scalar_t__ mp_isone (int /*<<< orphan*/ *) ; 
 scalar_t__ mp_iszero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_rshb (int /*<<< orphan*/ *,int) ; 
 int mp_sub_d (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int crypto_bignum_legendre(const struct crypto_bignum *a,
			   const struct crypto_bignum *p)
{
	mp_int t;
	int ret;
	int res = -2;

	if (TEST_FAIL())
		return -2;

	if (mp_init(&t) != MP_OKAY)
		return -2;

	/* t = (p-1) / 2 */
	ret = mp_sub_d((mp_int *) p, 1, &t);
	if (ret == MP_OKAY)
		mp_rshb(&t, 1);
	if (ret == MP_OKAY)
		ret = mp_exptmod((mp_int *) a, &t, (mp_int *) p, &t);
	if (ret == MP_OKAY) {
		if (mp_isone(&t))
			res = 1;
		else if (mp_iszero(&t))
			res = 0;
		else
			res = -1;
	}

	mp_clear(&t);
	return res;
}