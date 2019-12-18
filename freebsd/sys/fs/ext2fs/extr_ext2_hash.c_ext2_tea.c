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

__attribute__((used)) static void
ext2_tea(uint32_t hash[4], uint32_t data[8])
{
	uint32_t tea_delta = 0x9E3779B9;
	uint32_t sum;
	uint32_t x = hash[0], y = hash[1];
	int n = 16;
	int i = 1;

	while (n-- > 0) {
		sum = i * tea_delta;
		x += ((y << 4) + data[0]) ^ (y + sum) ^ ((y >> 5) + data[1]);
		y += ((x << 4) + data[2]) ^ (x + sum) ^ ((x >> 5) + data[3]);
		i++;
	}

	hash[0] += x;
	hash[1] += y;
}