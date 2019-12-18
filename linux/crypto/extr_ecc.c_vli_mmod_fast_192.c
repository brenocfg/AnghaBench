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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int vli_add (scalar_t__*,scalar_t__*,scalar_t__*,unsigned int const) ; 
 int vli_cmp (scalar_t__ const*,scalar_t__*,unsigned int const) ; 
 int /*<<< orphan*/  vli_set (scalar_t__*,scalar_t__ const*,unsigned int const) ; 
 scalar_t__ vli_sub (scalar_t__*,scalar_t__*,scalar_t__ const*,unsigned int const) ; 

__attribute__((used)) static void vli_mmod_fast_192(u64 *result, const u64 *product,
			      const u64 *curve_prime, u64 *tmp)
{
	const unsigned int ndigits = 3;
	int carry;

	vli_set(result, product, ndigits);

	vli_set(tmp, &product[3], ndigits);
	carry = vli_add(result, result, tmp, ndigits);

	tmp[0] = 0;
	tmp[1] = product[3];
	tmp[2] = product[4];
	carry += vli_add(result, result, tmp, ndigits);

	tmp[0] = tmp[1] = product[5];
	tmp[2] = 0;
	carry += vli_add(result, result, tmp, ndigits);

	while (carry || vli_cmp(curve_prime, result, ndigits) != 1)
		carry -= vli_sub(result, result, curve_prime, ndigits);
}