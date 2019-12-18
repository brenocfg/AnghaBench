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

/* Variables and functions */
 int ECC_MAX_DIGITS ; 
 int /*<<< orphan*/  vli_add (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  vli_clear (int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ vli_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  vli_is_zero (int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  vli_set (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  vli_sub (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  vli_umult (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const,unsigned int) ; 

__attribute__((used)) static void vli_mmod_special(u64 *result, const u64 *product,
			      const u64 *mod, unsigned int ndigits)
{
	u64 c = -mod[0];
	u64 t[ECC_MAX_DIGITS * 2];
	u64 r[ECC_MAX_DIGITS * 2];

	vli_set(r, product, ndigits * 2);
	while (!vli_is_zero(r + ndigits, ndigits)) {
		vli_umult(t, r + ndigits, c, ndigits);
		vli_clear(r + ndigits, ndigits);
		vli_add(r, r, t, ndigits * 2);
	}
	vli_set(t, mod, ndigits);
	vli_clear(t + ndigits, ndigits);
	while (vli_cmp(r, t, ndigits * 2) >= 0)
		vli_sub(r, r, t, ndigits * 2);
	vli_set(result, r, ndigits);
}