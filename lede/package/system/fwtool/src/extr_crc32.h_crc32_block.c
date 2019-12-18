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

__attribute__((used)) static inline uint32_t
crc32_block(uint32_t val, const void *buf, unsigned len, uint32_t *crc_table)
{
	const void *end = (uint8_t*)buf + len;

	while (buf != end) {
		val = crc_table[(uint8_t)val ^ *(uint8_t*)buf] ^ (val >> 8);
		buf = (uint8_t*)buf + 1;
	}
	return val;
}