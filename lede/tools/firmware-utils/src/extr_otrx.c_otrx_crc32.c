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
typedef  int uint32_t ;

/* Variables and functions */
 int* crc32_tbl ; 

uint32_t otrx_crc32(uint32_t crc, uint8_t *buf, size_t len) {
	while (len) {
		crc = crc32_tbl[(crc ^ *buf) & 0xff] ^ (crc >> 8);
		buf++;
		len--;
	}

	return crc;
}