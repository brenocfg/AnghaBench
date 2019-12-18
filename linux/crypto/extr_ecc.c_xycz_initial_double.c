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
typedef  int u64 ;

/* Variables and functions */
 int ECC_MAX_DIGITS ; 
 int /*<<< orphan*/  apply_z (int*,int*,int*,int*,unsigned int) ; 
 int /*<<< orphan*/  ecc_point_double_jacobian (int*,int*,int*,int*,unsigned int) ; 
 int /*<<< orphan*/  vli_clear (int*,unsigned int) ; 
 int /*<<< orphan*/  vli_set (int*,int*,unsigned int) ; 

__attribute__((used)) static void xycz_initial_double(u64 *x1, u64 *y1, u64 *x2, u64 *y2,
				u64 *p_initial_z, u64 *curve_prime,
				unsigned int ndigits)
{
	u64 z[ECC_MAX_DIGITS];

	vli_set(x2, x1, ndigits);
	vli_set(y2, y1, ndigits);

	vli_clear(z, ndigits);
	z[0] = 1;

	if (p_initial_z)
		vli_set(z, p_initial_z, ndigits);

	apply_z(x1, y1, z, curve_prime, ndigits);

	ecc_point_double_jacobian(x1, y1, z, curve_prime, ndigits);

	apply_z(x2, y2, z, curve_prime, ndigits);
}