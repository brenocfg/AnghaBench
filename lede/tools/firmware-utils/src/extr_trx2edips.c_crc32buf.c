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
 int UPDC32 (char,int) ; 

uint32_t crc32buf(char *buf, size_t len)
{
	uint32_t crc;

	crc = 0xFFFFFFFF;

	for (; len; --len, ++buf)
		crc = UPDC32(*buf, crc);

	return crc;
}