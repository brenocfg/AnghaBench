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
typedef  int /*<<< orphan*/  WC_RNG ;

/* Variables and functions */
 scalar_t__ TEST_FAIL () ; 
 int mp_count_bits (int /*<<< orphan*/ *) ; 
 scalar_t__ mp_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mp_rand_prime (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wc_FreeRng (int /*<<< orphan*/ *) ; 
 scalar_t__ wc_InitRng (int /*<<< orphan*/ *) ; 

int crypto_bignum_rand(struct crypto_bignum *r, const struct crypto_bignum *m)
{
	int ret = 0;
	WC_RNG rng;

	if (TEST_FAIL())
		return -1;
	if (wc_InitRng(&rng) != 0)
		return -1;
	if (mp_rand_prime((mp_int *) r,
			  (mp_count_bits((mp_int *) m) + 7) / 8 * 2,
			  &rng, NULL) != 0)
		ret = -1;
	if (ret == 0 &&
	    mp_mod((mp_int *) r, (mp_int *) m, (mp_int *) r) != 0)
		ret = -1;
	wc_FreeRng(&rng);
	return ret;
}