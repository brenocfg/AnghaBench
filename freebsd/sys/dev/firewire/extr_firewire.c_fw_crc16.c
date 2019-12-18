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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */

uint16_t
fw_crc16(uint32_t *ptr, uint32_t len)
{
	uint32_t i, sum, crc = 0;
	int shift;
	len = (len + 3) & ~3;
	for (i = 0; i < len; i += 4) {
		for (shift = 28; shift >= 0; shift -= 4) {
			sum = ((crc >> 12) ^ (ptr[i/4] >> shift)) & 0xf;
			crc = (crc << 4) ^ (sum << 12) ^ (sum << 5) ^ sum;
		}
		crc &= 0xffff;
	}
	return ((uint16_t) crc);
}