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
typedef  scalar_t__ uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ const INT32_MAX ; 

__attribute__((used)) static inline int32_t
uint32_2cpl_to_int32(
	const uint32_t vu)
{
	int32_t v;
	
#   if TARGET_HAS_2CPL

	/* Just copy through the 32 bits from the unsigned value if
	 * we're on a two's complement target.
	 */
	v = (int32_t)vu;

#   else

	/* Convert to signed integer, making sure signed integer
	 * overflow cannot happen. Again, the optimiser might or might
	 * not find out that this is just a copy of 32 bits on a target
	 * with two's complement representation for signed integers.
	 */
	if (vu > INT32_MAX)
		v = -(int32_t)(~vu) - 1;
	else
		v = (int32_t)vu;
	
#   endif
	
	return v;
}