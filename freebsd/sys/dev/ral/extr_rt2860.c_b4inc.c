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
typedef  int int8_t ;

/* Variables and functions */

__attribute__((used)) static __inline uint32_t
b4inc(uint32_t b32, int8_t delta)
{
	int8_t i, b4;

	for (i = 0; i < 8; i++) {
		b4 = b32 & 0xf;
		b4 += delta;
		if (b4 < 0)
			b4 = 0;
		else if (b4 > 0xf)
			b4 = 0xf;
		b32 = b32 >> 4 | (uint32_t)b4 << 28;
	}
	return b32;
}