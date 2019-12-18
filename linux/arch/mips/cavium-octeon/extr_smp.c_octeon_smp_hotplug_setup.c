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
struct linux_app_boot_info {scalar_t__ labi_signature; int /*<<< orphan*/  InitTLBStart_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LABI_ADDR_IN_BOOTLOADER ; 
 scalar_t__ LABI_SIGNATURE ; 
 scalar_t__ PHYS_TO_XKSEG_CACHED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_bootloader_entry_addr ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  setup_max_cpus ; 

__attribute__((used)) static void octeon_smp_hotplug_setup(void)
{
#ifdef CONFIG_HOTPLUG_CPU
	struct linux_app_boot_info *labi;

	if (!setup_max_cpus)
		return;

	labi = (struct linux_app_boot_info *)PHYS_TO_XKSEG_CACHED(LABI_ADDR_IN_BOOTLOADER);
	if (labi->labi_signature != LABI_SIGNATURE) {
		pr_info("The bootloader on this board does not support HOTPLUG_CPU.");
		return;
	}

	octeon_bootloader_entry_addr = labi->InitTLBStart_addr;
#endif
}