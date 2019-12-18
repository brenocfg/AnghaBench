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
 scalar_t__ big_endian ; 

__attribute__((used)) static void put_u32(void *data, uint32_t val)
{
	unsigned char *p = data;

	if (big_endian) {
		p[0] = (val >> 24) & 0xff;
		p[1] = (val >> 16) & 0xff;
		p[2] = (val >> 8) & 0xff;
		p[3] = val & 0xff;
	} else {
		p[3] = (val >> 24) & 0xff;
		p[2] = (val >> 16) & 0xff;
		p[1] = (val >> 8) & 0xff;
		p[0] = val & 0xff;
	}
}