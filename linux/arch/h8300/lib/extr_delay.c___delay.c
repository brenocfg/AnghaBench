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

void __delay(unsigned long cycles)
{
	__asm__ volatile ("1: dec.l #1,%0\n\t"
			  "bne 1b":"=r"(cycles):"0"(cycles));
}