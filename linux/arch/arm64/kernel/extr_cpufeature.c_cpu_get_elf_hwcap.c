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
 unsigned long lower_32_bits (int /*<<< orphan*/ ) ; 

unsigned long cpu_get_elf_hwcap(void)
{
	/*
	 * We currently only populate the first 32 bits of AT_HWCAP. Please
	 * note that for userspace compatibility we guarantee that bits 62
	 * and 63 will always be returned as 0.
	 */
	return lower_32_bits(elf_hwcap);
}