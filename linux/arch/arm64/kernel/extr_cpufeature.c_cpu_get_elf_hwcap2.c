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
 int /*<<< orphan*/  elf_hwcap ; 
 unsigned long upper_32_bits (int /*<<< orphan*/ ) ; 

unsigned long cpu_get_elf_hwcap2(void)
{
	return upper_32_bits(elf_hwcap);
}