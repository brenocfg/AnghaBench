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
 int /*<<< orphan*/  CVMX_CLOCK_SCLK ; 
 int FLASH_RoundUP (int,int) ; 
 int cvmx_clock_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t ns_to_tim_reg(int tim_mult, uint32_t nsecs)
{
	uint32_t val;

	/* Compute # of eclock periods to get desired duration in nanoseconds */
	val = FLASH_RoundUP(nsecs * (cvmx_clock_get_rate(CVMX_CLOCK_SCLK)/1000000), 1000);

	/* Factor in timing multiple, if not 1 */
	if (tim_mult != 1)
		val = FLASH_RoundUP(val, tim_mult);

	return (val);
}