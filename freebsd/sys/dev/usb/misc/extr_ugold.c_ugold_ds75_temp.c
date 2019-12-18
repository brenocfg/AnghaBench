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
typedef  int uint8_t ;
typedef  int int64_t ;
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static int
ugold_ds75_temp(uint8_t msb, uint8_t lsb)
{
	/* DS75: 12bit precision mode : 0.0625 degrees Celsius ticks */
	/* NOTE: MSB has a sign bit for negative temperatures */
	int32_t temp = (msb << 24) | ((lsb & 0xF0) << 16);
	return (((int64_t)temp * (int64_t)1000000LL) >> 24);
}