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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
int32_to_uint32_2cpl(
	const int32_t v)
{
	uint32_t vu;
	
#   if TARGET_HAS_2CPL

	/* Just copy through the 32 bits from the signed value if we're
	 * on a two's complement target.
	 */
	vu = (uint32_t)v;
	
#   else

	/* Convert from signed int to unsigned int two's complement. Do
	 * not make any assumptions about the representation of signed
	 * integers, but make sure signed integer overflow cannot happen
	 * here. A compiler on a two's complement target *might* find
	 * out that this is just a complicated cast (as above), but your
	 * mileage might vary.
	 */
	if (v < 0)
		vu = ~(uint32_t)(-(v + 1));
	else
		vu = (uint32_t)v;
	
#   endif
	
	return vu;
}