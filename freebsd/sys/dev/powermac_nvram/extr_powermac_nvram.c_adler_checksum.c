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
typedef  scalar_t__ uint8_t ;
typedef  unsigned long uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t
adler_checksum(uint8_t *data, int len)
{
	uint32_t low, high;
	int i;

	low = 1;
	high = 0;
	for (i = 0; i < len; i++) {
		if ((i % 5000) == 0) {
			high %= 65521UL;
			high %= 65521UL;
		}
		low += data[i];
		high += low;
	}
	low %= 65521UL;
	high %= 65521UL;

	return (high << 16) | low;
}