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
typedef  int uint16_t ;

/* Variables and functions */
 int fls (int) ; 

__attribute__((used)) static int
hdaa_allowed_stripes(uint16_t fmt)
{
	static const int bits[8] = { 8, 16, 20, 24, 32, 32, 32, 32 };
	int size;

	size = bits[(fmt >> 4) & 0x03];
	size *= (fmt & 0x0f) + 1;
	size *= ((fmt >> 11) & 0x07) + 1;
	return (0xffffffffU >> (32 - fls(size / 8)));
}