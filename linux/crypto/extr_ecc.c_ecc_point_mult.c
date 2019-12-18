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
typedef  int /*<<< orphan*/  const u64 ;
struct ecc_point {int /*<<< orphan*/  const* y; int /*<<< orphan*/  const* x; int /*<<< orphan*/  ndigits; } ;
struct ecc_curve {int /*<<< orphan*/  n; int /*<<< orphan*/  const* p; } ;

/* Variables and functions */
 int ECC_MAX_DIGITS ; 
 int /*<<< orphan*/  apply_z (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int vli_add (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  vli_mod_inv (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vli_mod_mult_fast (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  vli_mod_sub (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  vli_set (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  vli_test_bit (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  xycz_add (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  xycz_add_c (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  xycz_initial_double (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void ecc_point_mult(struct ecc_point *result,
			   const struct ecc_point *point, const u64 *scalar,
			   u64 *initial_z, const struct ecc_curve *curve,
			   unsigned int ndigits)
{
	/* R0 and R1 */
	u64 rx[2][ECC_MAX_DIGITS];
	u64 ry[2][ECC_MAX_DIGITS];
	u64 z[ECC_MAX_DIGITS];
	u64 sk[2][ECC_MAX_DIGITS];
	u64 *curve_prime = curve->p;
	int i, nb;
	int num_bits;
	int carry;

	carry = vli_add(sk[0], scalar, curve->n, ndigits);
	vli_add(sk[1], sk[0], curve->n, ndigits);
	scalar = sk[!carry];
	num_bits = sizeof(u64) * ndigits * 8 + 1;

	vli_set(rx[1], point->x, ndigits);
	vli_set(ry[1], point->y, ndigits);

	xycz_initial_double(rx[1], ry[1], rx[0], ry[0], initial_z, curve_prime,
			    ndigits);

	for (i = num_bits - 2; i > 0; i--) {
		nb = !vli_test_bit(scalar, i);
		xycz_add_c(rx[1 - nb], ry[1 - nb], rx[nb], ry[nb], curve_prime,
			   ndigits);
		xycz_add(rx[nb], ry[nb], rx[1 - nb], ry[1 - nb], curve_prime,
			 ndigits);
	}

	nb = !vli_test_bit(scalar, 0);
	xycz_add_c(rx[1 - nb], ry[1 - nb], rx[nb], ry[nb], curve_prime,
		   ndigits);

	/* Find final 1/Z value. */
	/* X1 - X0 */
	vli_mod_sub(z, rx[1], rx[0], curve_prime, ndigits);
	/* Yb * (X1 - X0) */
	vli_mod_mult_fast(z, z, ry[1 - nb], curve_prime, ndigits);
	/* xP * Yb * (X1 - X0) */
	vli_mod_mult_fast(z, z, point->x, curve_prime, ndigits);

	/* 1 / (xP * Yb * (X1 - X0)) */
	vli_mod_inv(z, z, curve_prime, point->ndigits);

	/* yP / (xP * Yb * (X1 - X0)) */
	vli_mod_mult_fast(z, z, point->y, curve_prime, ndigits);
	/* Xb * yP / (xP * Yb * (X1 - X0)) */
	vli_mod_mult_fast(z, z, rx[1 - nb], curve_prime, ndigits);
	/* End 1/Z calculation */

	xycz_add(rx[nb], ry[nb], rx[1 - nb], ry[1 - nb], curve_prime, ndigits);

	apply_z(rx[0], ry[0], z, curve_prime, ndigits);

	vli_set(result->x, rx[0], ndigits);
	vli_set(result->y, ry[0], ndigits);
}