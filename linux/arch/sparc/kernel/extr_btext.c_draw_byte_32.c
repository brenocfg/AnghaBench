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

__attribute__((used)) static void draw_byte_32(unsigned char *font, unsigned int *base, int rb)
{
	int l, bits;
	int fg = 0xFFFFFFFFUL;
	int bg = 0x00000000UL;

	for (l = 0; l < 16; ++l)
	{
		bits = *font++;
		base[0] = (-(bits >> 7) & fg) ^ bg;
		base[1] = (-((bits >> 6) & 1) & fg) ^ bg;
		base[2] = (-((bits >> 5) & 1) & fg) ^ bg;
		base[3] = (-((bits >> 4) & 1) & fg) ^ bg;
		base[4] = (-((bits >> 3) & 1) & fg) ^ bg;
		base[5] = (-((bits >> 2) & 1) & fg) ^ bg;
		base[6] = (-((bits >> 1) & 1) & fg) ^ bg;
		base[7] = (-(bits & 1) & fg) ^ bg;
		base = (unsigned int *) ((char *)base + rb);
	}
}