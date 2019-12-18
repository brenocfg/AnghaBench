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
typedef  size_t u_int32_t ;
typedef  size_t u_char ;

/* Variables and functions */
 size_t* crc32tab ; 

u_int32_t
ssh_crc32(const u_char *buf, u_int32_t size)
{
	u_int32_t i, crc;

	crc = 0;
	for (i = 0; i < size; i++)
		crc = crc32tab[(crc ^ buf[i]) & 0xff] ^ (crc >> 8);
	return crc;
}