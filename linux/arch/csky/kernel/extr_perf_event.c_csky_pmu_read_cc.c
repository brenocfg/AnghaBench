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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ cprgr (char*) ; 

__attribute__((used)) static uint64_t csky_pmu_read_cc(void)
{
	uint32_t lo, hi, tmp;
	uint64_t result;

	do {
		tmp = cprgr("<0, 0x3>");
		lo  = cprgr("<0, 0x2>");
		hi  = cprgr("<0, 0x3>");
	} while (hi != tmp);

	result = (uint64_t) (hi) << 32;
	result |= lo;

	return result;
}