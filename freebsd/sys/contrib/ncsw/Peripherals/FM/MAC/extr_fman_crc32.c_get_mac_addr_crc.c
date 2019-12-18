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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int* crc_tbl ; 
 int get_mirror32 (int) ; 

uint32_t get_mac_addr_crc(uint64_t _addr)
{
	uint32_t i;
	uint8_t  data;
	uint32_t crc;

	/* CRC calculation */
	crc = 0xffffffff;
	for (i = 0; i < 6; i++) {
		data = (uint8_t)(_addr >> ((5-i)*8));
		crc = crc ^ data;
		crc = crc_tbl[crc&0xff] ^ (crc>>8);
	}

	crc = get_mirror32(crc);
	return crc;
}