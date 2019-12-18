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
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static int
extract_signed(uint32_t reg, int shift, int bits)
{
	int32_t val;
	uint32_t mask;

	mask = (1 << bits) - 1;
	val = ((reg >> shift) & mask) << (32 - bits);
	val >>= 32 - bits;
	return ((int32_t)val);
}