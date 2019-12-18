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

__attribute__((used)) static inline unsigned char
vt_vga2bsd(unsigned char vga)
{
	static const unsigned char lut[8] = {
		0,
		4,	/* 1 and 4 swap */
		2,
		6,	/* 3 and 6 swap */
		1,	/* 4 and 1 swap */
		5,
		3,	/* 6 and 3 swap */
		7,
	};
	unsigned int bright;

	bright = (vga & 0x8);
	return (lut[vga & 0x7] | bright);
}