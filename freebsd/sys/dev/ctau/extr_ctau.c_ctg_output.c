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
typedef  int /*<<< orphan*/  port_t ;

/* Variables and functions */
 unsigned char GMD0_SCLK ; 
 unsigned char GMD0_SDI ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void ctg_output (port_t port, unsigned char val, unsigned char v0)
{
	int i;

	for (i=0; i<8; ++i) {
		unsigned char v = v0;
		if ((val >> i) & 1)
			v |= GMD0_SDI;
		outb (port, v);
		outb (port, v);
		outb (port, v);
		outb (port, v);
		outb (port, v | GMD0_SCLK);
		outb (port, v | GMD0_SCLK);
		outb (port, v | GMD0_SCLK);
		outb (port, v | GMD0_SCLK);
	}
	outb (port, v0);
}