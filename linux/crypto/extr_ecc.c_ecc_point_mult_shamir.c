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
typedef  int u64 ;
struct ecc_point {int* x; int* y; } ;
struct TYPE_2__ {unsigned int ndigits; } ;
struct ecc_curve {int /*<<< orphan*/  p; TYPE_1__ g; } ;

/* Variables and functions */
 int ECC_MAX_DIGITS ; 
 struct ecc_point ECC_POINT_INIT (int*,int*,unsigned int) ; 
 int /*<<< orphan*/  apply_z (int*,int*,int*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ecc_point_add (struct ecc_point*,struct ecc_point const*,struct ecc_point const*,struct ecc_curve const*) ; 
 int /*<<< orphan*/  ecc_point_double_jacobian (int*,int*,int*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vli_clear (int*,unsigned int) ; 
 int /*<<< orphan*/  vli_mod_inv (int*,int*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  vli_mod_mult_fast (int*,int*,int*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  vli_mod_sub (int*,int*,int*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  vli_num_bits (int const*,unsigned int) ; 
 int /*<<< orphan*/  vli_set (int*,int*,unsigned int) ; 
 int /*<<< orphan*/  vli_test_bit (int const*,int) ; 
 int /*<<< orphan*/  xycz_add (int*,int*,int*,int*,int /*<<< orphan*/ ,unsigned int) ; 

void ecc_point_mult_shamir(const struct ecc_point *result,
			   const u64 *u1, const struct ecc_point *p,
			   const u64 *u2, const struct ecc_point *q,
			   const struct ecc_curve *curve)
{
	u64 z[ECC_MAX_DIGITS];
	u64 sump[2][ECC_MAX_DIGITS];
	u64 *rx = result->x;
	u64 *ry = result->y;
	unsigned int ndigits = curve->g.ndigits;
	unsigned int num_bits;
	struct ecc_point sum = ECC_POINT_INIT(sump[0], sump[1], ndigits);
	const struct ecc_point *points[4];
	const struct ecc_point *point;
	unsigned int idx;
	int i;

	ecc_point_add(&sum, p, q, curve);
	points[0] = NULL;
	points[1] = p;
	points[2] = q;
	points[3] = &sum;

	num_bits = max(vli_num_bits(u1, ndigits),
		       vli_num_bits(u2, ndigits));
	i = num_bits - 1;
	idx = (!!vli_test_bit(u1, i)) | ((!!vli_test_bit(u2, i)) << 1);
	point = points[idx];

	vli_set(rx, point->x, ndigits);
	vli_set(ry, point->y, ndigits);
	vli_clear(z + 1, ndigits - 1);
	z[0] = 1;

	for (--i; i >= 0; i--) {
		ecc_point_double_jacobian(rx, ry, z, curve->p, ndigits);
		idx = (!!vli_test_bit(u1, i)) | ((!!vli_test_bit(u2, i)) << 1);
		point = points[idx];
		if (point) {
			u64 tx[ECC_MAX_DIGITS];
			u64 ty[ECC_MAX_DIGITS];
			u64 tz[ECC_MAX_DIGITS];

			vli_set(tx, point->x, ndigits);
			vli_set(ty, point->y, ndigits);
			apply_z(tx, ty, z, curve->p, ndigits);
			vli_mod_sub(tz, rx, tx, curve->p, ndigits);
			xycz_add(tx, ty, rx, ry, curve->p, ndigits);
			vli_mod_mult_fast(z, z, tz, curve->p, ndigits);
		}
	}
	vli_mod_inv(z, z, curve->p, ndigits);
	apply_z(rx, ry, z, curve->p, ndigits);
}