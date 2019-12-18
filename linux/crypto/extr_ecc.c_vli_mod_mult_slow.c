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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int ECC_MAX_DIGITS ; 
 int /*<<< orphan*/  vli_mmod_slow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  vli_mult (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 

void vli_mod_mult_slow(u64 *result, const u64 *left, const u64 *right,
		       const u64 *mod, unsigned int ndigits)
{
	u64 product[ECC_MAX_DIGITS * 2];

	vli_mult(product, left, right, ndigits);
	vli_mmod_slow(result, product, mod, ndigits);
}