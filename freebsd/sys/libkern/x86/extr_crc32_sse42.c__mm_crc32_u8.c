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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

__attribute__((used)) static __inline uint32_t
_mm_crc32_u8(uint32_t x, uint8_t y)
{
	/*
	 * clang (at least 3.9.[0-1]) pessimizes "rm" (y) and "m" (y)
	 * significantly and "r" (y) a lot by copying y to a different
	 * local variable (on the stack or in a register), so only use
	 * the latter.  This costs a register and an instruction but
	 * not a uop.
	 */
	__asm("crc32b %1,%0" : "+r" (x) : "r" (y));
	return (x);
}