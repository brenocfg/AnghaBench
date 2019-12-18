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

/* Variables and functions */
 int /*<<< orphan*/  crypto_bignum_deinit (struct crypto_bignum*,int /*<<< orphan*/ ) ; 
 struct crypto_bignum* crypto_bignum_init () ; 
 int crypto_bignum_legendre (struct crypto_bignum*,struct crypto_bignum const*) ; 
 scalar_t__ crypto_bignum_rand (struct crypto_bignum*,struct crypto_bignum const*) ; 

int dragonfly_get_random_qr_qnr(const struct crypto_bignum *prime,
				struct crypto_bignum **qr,
				struct crypto_bignum **qnr)
{
	*qr = *qnr = NULL;

	while (!(*qr) || !(*qnr)) {
		struct crypto_bignum *tmp;
		int res;

		tmp = crypto_bignum_init();
		if (!tmp || crypto_bignum_rand(tmp, prime) < 0) {
			crypto_bignum_deinit(tmp, 0);
			break;
		}

		res = crypto_bignum_legendre(tmp, prime);
		if (res == 1 && !(*qr))
			*qr = tmp;
		else if (res == -1 && !(*qnr))
			*qnr = tmp;
		else
			crypto_bignum_deinit(tmp, 0);
	}

	if (*qr && *qnr)
		return 0;
	crypto_bignum_deinit(*qr, 0);
	crypto_bignum_deinit(*qnr, 0);
	*qr = *qnr = NULL;
	return -1;
}