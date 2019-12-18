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

void __delay(unsigned long loops)
{
	asm volatile (
		"mov r0, r0\n"
		"1:declt %0\n"
		"bf	1b"
		: "=r"(loops)
		: "0"(loops));
}