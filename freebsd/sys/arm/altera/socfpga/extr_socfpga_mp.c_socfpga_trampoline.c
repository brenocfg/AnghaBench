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

__attribute__((used)) static void
socfpga_trampoline(void)
{

	__asm __volatile(
			"ldr pc, 1f\n"
			".globl mpentry_addr\n"
			"mpentry_addr:\n"
			"1: .space 4\n");
}