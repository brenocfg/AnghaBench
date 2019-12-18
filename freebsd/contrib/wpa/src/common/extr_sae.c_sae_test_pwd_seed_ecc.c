#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const u8 ;
struct sae_data {TYPE_1__* tmp; } ;
struct crypto_bignum {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ec; int /*<<< orphan*/  prime_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SHA256_MAC_LEN ; 
 int /*<<< orphan*/  buf_shift_right (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 unsigned int const_time_fill_msb (unsigned int) ; 
 int const_time_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int const_time_select_int (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_bignum_deinit (struct crypto_bignum*,int) ; 
 struct crypto_bignum* crypto_bignum_init_set (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct crypto_bignum* crypto_ec_point_compute_y_sqr (int /*<<< orphan*/ ,struct crypto_bignum*) ; 
 size_t crypto_ec_prime_len_bits (int /*<<< orphan*/ ) ; 
 int dragonfly_is_quadratic_residue_blind (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,struct crypto_bignum*) ; 
 scalar_t__ sha256_prf_bits (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sae_test_pwd_seed_ecc(struct sae_data *sae, const u8 *pwd_seed,
				 const u8 *prime, const u8 *qr, const u8 *qnr,
				 u8 *pwd_value)
{
	struct crypto_bignum *y_sqr, *x_cand;
	int res;
	size_t bits;
	int cmp_prime;
	unsigned int in_range;

	wpa_hexdump_key(MSG_DEBUG, "SAE: pwd-seed", pwd_seed, SHA256_MAC_LEN);

	/* pwd-value = KDF-z(pwd-seed, "SAE Hunting and Pecking", p) */
	bits = crypto_ec_prime_len_bits(sae->tmp->ec);
	if (sha256_prf_bits(pwd_seed, SHA256_MAC_LEN, "SAE Hunting and Pecking",
			    prime, sae->tmp->prime_len, pwd_value, bits) < 0)
		return -1;
	if (bits % 8)
		buf_shift_right(pwd_value, sae->tmp->prime_len, 8 - bits % 8);
	wpa_hexdump_key(MSG_DEBUG, "SAE: pwd-value",
			pwd_value, sae->tmp->prime_len);

	cmp_prime = const_time_memcmp(pwd_value, prime, sae->tmp->prime_len);
	/* Create a const_time mask for selection based on prf result
	 * being smaller than prime. */
	in_range = const_time_fill_msb((unsigned int) cmp_prime);
	/* The algorithm description would skip the next steps if
	 * cmp_prime >= 0 (reutnr 0 here), but go through them regardless to
	 * minimize externally observable differences in behavior. */

	x_cand = crypto_bignum_init_set(pwd_value, sae->tmp->prime_len);
	if (!x_cand)
		return -1;
	y_sqr = crypto_ec_point_compute_y_sqr(sae->tmp->ec, x_cand);
	crypto_bignum_deinit(x_cand, 1);
	if (!y_sqr)
		return -1;

	res = dragonfly_is_quadratic_residue_blind(sae->tmp->ec, qr, qnr,
						   y_sqr);
	crypto_bignum_deinit(y_sqr, 1);
	if (res < 0)
		return res;
	return const_time_select_int(in_range, res, 0);
}