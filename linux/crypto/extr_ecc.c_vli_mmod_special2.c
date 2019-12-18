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
 int /*<<< orphan*/  vli_add (int*,int*,int*,unsigned int) ; 
 int /*<<< orphan*/  vli_clear (int*,unsigned int) ; 
 scalar_t__ vli_cmp (int*,int*,unsigned int) ; 
 int vli_is_negative (int*,unsigned int) ; 
 int /*<<< orphan*/  vli_is_zero (int*,unsigned int) ; 
 int /*<<< orphan*/  vli_set (int*,int const*,unsigned int) ; 
 int /*<<< orphan*/  vli_sub (int*,int*,int*,unsigned int) ; 
 int /*<<< orphan*/  vli_uadd (int*,int*,int const,unsigned int) ; 
 int /*<<< orphan*/  vli_umult (int*,int*,int,unsigned int) ; 

__attribute__((used)) static void vli_mmod_special2(u64 *result, const u64 *product,
			       const u64 *mod, unsigned int ndigits)
{
	u64 c2 = mod[0] * 2;
	u64 q[ECC_MAX_DIGITS];
	u64 r[ECC_MAX_DIGITS * 2];
	u64 m[ECC_MAX_DIGITS * 2]; /* expanded mod */
	int carry; /* last bit that doesn't fit into q */
	int i;

	vli_set(m, mod, ndigits);
	vli_clear(m + ndigits, ndigits);

	vli_set(r, product, ndigits);
	/* q and carry are top bits */
	vli_set(q, product + ndigits, ndigits);
	vli_clear(r + ndigits, ndigits);
	carry = vli_is_negative(r, ndigits);
	if (carry)
		r[ndigits - 1] &= (1ull << 63) - 1;
	for (i = 1; carry || !vli_is_zero(q, ndigits); i++) {
		u64 qc[ECC_MAX_DIGITS * 2];

		vli_umult(qc, q, c2, ndigits);
		if (carry)
			vli_uadd(qc, qc, mod[0], ndigits * 2);
		vli_set(q, qc + ndigits, ndigits);
		vli_clear(qc + ndigits, ndigits);
		carry = vli_is_negative(qc, ndigits);
		if (carry)
			qc[ndigits - 1] &= (1ull << 63) - 1;
		if (i & 1)
			vli_sub(r, r, qc, ndigits * 2);
		else
			vli_add(r, r, qc, ndigits * 2);
	}
	while (vli_is_negative(r, ndigits * 2))
		vli_add(r, r, m, ndigits * 2);
	while (vli_cmp(r, m, ndigits * 2) >= 0)
		vli_sub(r, r, m, ndigits * 2);

	vli_set(result, r, ndigits);
}