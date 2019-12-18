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

/* Variables and functions */

__attribute__((used)) static void
hexbyte(char *buf, uint8_t temp)
{
	uint8_t lo;
	uint8_t hi;

	lo = temp & 0xF;
	hi = temp >> 4;

	if (hi < 10)
		buf[0] = '0' + hi;
	else
		buf[0] = 'A' + hi - 10;

	if (lo < 10)
		buf[1] = '0' + lo;
	else
		buf[1] = 'A' + lo - 10;
}