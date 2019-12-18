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
typedef  size_t uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int* crctab ; 

__attribute__((used)) static uint32_t crc32(uint8_t* buf, uint32_t len)
{
	register int i;
	uint32_t sum;
	register uint32_t s0;
	s0 = ~0;
	for (i = 0; i < len; i++)
	{
		s0 = (s0 >> 8) ^ crctab[(uint8_t) (s0 & 0xFF) ^ buf[i]];
	}
	sum = ~s0;
	return sum;
}