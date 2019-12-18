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
typedef  int u_short ;

/* Variables and functions */

__attribute__((used)) static u_short
vga_flipattr(u_short a, int blink)
{
	if (blink)
		a = (a & 0x8800) | ((a & 0x7000) >> 4) |
		    ((a & 0x0700) << 4);
	else
		a = ((a & 0xf000) >> 4) | ((a & 0x0f00) << 4);
	return (a);
}