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
 scalar_t__ PMSU_BOOT_ADDR_REDIRECT_OFFSET (int) ; 
 int /*<<< orphan*/  __pa_symbol (void*) ; 
 scalar_t__ pmsu_mp_base ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void mvebu_pmsu_set_cpu_boot_addr(int hw_cpu, void *boot_addr)
{
	writel(__pa_symbol(boot_addr), pmsu_mp_base +
		PMSU_BOOT_ADDR_REDIRECT_OFFSET(hw_cpu));
}