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
 scalar_t__ EVEN (int*) ; 
 int vli_add (int*,int*,int const*,unsigned int) ; 
 int /*<<< orphan*/  vli_clear (int*,unsigned int) ; 
 int vli_cmp (int*,int*,unsigned int) ; 
 scalar_t__ vli_is_zero (int const*,unsigned int) ; 
 int /*<<< orphan*/  vli_rshift1 (int*,unsigned int) ; 
 int /*<<< orphan*/  vli_set (int*,int const*,unsigned int) ; 
 int /*<<< orphan*/  vli_sub (int*,int*,int*,unsigned int) ; 

void vli_mod_inv(u64 *result, const u64 *input, const u64 *mod,
			unsigned int ndigits)
{
	u64 a[ECC_MAX_DIGITS], b[ECC_MAX_DIGITS];
	u64 u[ECC_MAX_DIGITS], v[ECC_MAX_DIGITS];
	u64 carry;
	int cmp_result;

	if (vli_is_zero(input, ndigits)) {
		vli_clear(result, ndigits);
		return;
	}

	vli_set(a, input, ndigits);
	vli_set(b, mod, ndigits);
	vli_clear(u, ndigits);
	u[0] = 1;
	vli_clear(v, ndigits);

	while ((cmp_result = vli_cmp(a, b, ndigits)) != 0) {
		carry = 0;

		if (EVEN(a)) {
			vli_rshift1(a, ndigits);

			if (!EVEN(u))
				carry = vli_add(u, u, mod, ndigits);

			vli_rshift1(u, ndigits);
			if (carry)
				u[ndigits - 1] |= 0x8000000000000000ull;
		} else if (EVEN(b)) {
			vli_rshift1(b, ndigits);

			if (!EVEN(v))
				carry = vli_add(v, v, mod, ndigits);

			vli_rshift1(v, ndigits);
			if (carry)
				v[ndigits - 1] |= 0x8000000000000000ull;
		} else if (cmp_result > 0) {
			vli_sub(a, a, b, ndigits);
			vli_rshift1(a, ndigits);

			if (vli_cmp(u, v, ndigits) < 0)
				vli_add(u, u, mod, ndigits);

			vli_sub(u, u, v, ndigits);
			if (!EVEN(u))
				carry = vli_add(u, u, mod, ndigits);

			vli_rshift1(u, ndigits);
			if (carry)
				u[ndigits - 1] |= 0x8000000000000000ull;
		} else {
			vli_sub(b, b, a, ndigits);
			vli_rshift1(b, ndigits);

			if (vli_cmp(v, u, ndigits) < 0)
				vli_add(v, v, mod, ndigits);

			vli_sub(v, v, u, ndigits);
			if (!EVEN(v))
				carry = vli_add(v, v, mod, ndigits);

			vli_rshift1(v, ndigits);
			if (carry)
				v[ndigits - 1] |= 0x8000000000000000ull;
		}
	}

	vli_set(result, u, ndigits);
}