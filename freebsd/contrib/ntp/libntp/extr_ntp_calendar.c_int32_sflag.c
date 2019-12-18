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
 scalar_t__ UINT32_C (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t
int32_sflag(
	const int32_t v)
{
#   if TARGET_HAS_2CPL && TARGET_HAS_SAR && SIZEOF_INT >= 4

	/* Let's assume that shift is the fastest way to get the sign
	 * extension of of a signed integer. This might not always be
	 * true, though -- On 8bit CPUs or machines without barrel
	 * shifter this will kill the performance. So we make sure
	 * we do this only if 'int' has at least 4 bytes.
	 */
	return (uint32_t)(v >> 31);
	
#   else

	/* This should be a rather generic approach for getting a sign
	 * extension mask...
	 */
	return UINT32_C(0) - (uint32_t)(v < 0);
	
#   endif
}