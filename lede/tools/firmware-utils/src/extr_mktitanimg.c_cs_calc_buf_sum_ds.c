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

/* Variables and functions */
 unsigned long* crctab ; 

unsigned long cs_calc_buf_sum_ds(char *buf, int buf_size, char *sign, int sign_len)
{
	unsigned long crc = 0;
	char *cp = buf;
	unsigned long length = buf_size+sign_len;

	while(buf_size--)
		crc =(crc << 8) ^ crctab[((crc >> 24) ^ *cp++) & 0xFF];

	cp = sign;
	while(sign_len--)
		crc =(crc << 8) ^ crctab[((crc >> 24) ^ *cp++) & 0xFF];


	for(; length; length >>= 8)
		crc =(crc << 8) ^ crctab[((crc >> 24) ^ length) & 0xFF];

	crc = ~crc & 0xFFFFFFFF;

	return crc;
}