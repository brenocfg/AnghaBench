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
 int /*<<< orphan*/  vli_add (scalar_t__*,scalar_t__*,scalar_t__ const*,unsigned int) ; 
 scalar_t__ vli_sub (scalar_t__*,scalar_t__ const*,scalar_t__ const*,unsigned int) ; 

__attribute__((used)) static void vli_mod_sub(u64 *result, const u64 *left, const u64 *right,
			const u64 *mod, unsigned int ndigits)
{
	u64 borrow = vli_sub(result, left, right, ndigits);

	/* In this case, p_result == -diff == (max int) - diff.
	 * Since -x % d == d - x, we can get the correct result from
	 * result + mod (with overflow).
	 */
	if (borrow)
		vli_add(result, result, mod, ndigits);
}