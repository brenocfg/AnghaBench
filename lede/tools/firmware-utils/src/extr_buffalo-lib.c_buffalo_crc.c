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
 int* crc32_table ; 

uint32_t buffalo_crc(void *buf, unsigned long len)
{
	unsigned char *p = buf;
	unsigned long t = len;
	uint32_t crc = 0;

	while (len--)
		crc = (crc << 8) ^ crc32_table[((crc >> 24) ^ *p++) & 0xFF];

	while (t) {
		crc = (crc << 8) ^ crc32_table[((crc >> 24) ^ t) & 0xFF];
		t >>= 8;
	}

	return ~crc;
}