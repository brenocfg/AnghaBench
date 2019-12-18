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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
dc_scaling_incr(uint32_t src, uint32_t dst, uint32_t maxscale)
{
	uint32_t val;

	val = (src - 1) << 12 ; /* 4.12 fixed float */
	val /= (dst - 1);
	if (val  > (maxscale << 12))
		val = maxscale << 12;
	return val;
}