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
 int cab_checksum_cfdata_4 (void const*,size_t,int) ; 

__attribute__((used)) static uint32_t
cab_checksum_cfdata(const void *p, size_t bytes, uint32_t seed)
{
	const unsigned char *b;
	uint32_t sum;
	uint32_t t;

	sum = cab_checksum_cfdata_4(p, bytes, seed);
	b = p;
	b += bytes & ~3;
	t = 0;
	switch (bytes & 3) {
	case 3:
		t |= ((uint32_t)(*b++)) << 16;
		/* FALL THROUGH */
	case 2:
		t |= ((uint32_t)(*b++)) << 8;
		/* FALL THROUGH */
	case 1:
		t |= *b;
		/* FALL THROUGH */
	default:
		break;
	}
	sum ^= t;

	return (sum);
}