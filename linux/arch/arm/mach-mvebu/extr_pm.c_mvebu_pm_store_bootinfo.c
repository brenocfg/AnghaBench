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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BOOT_INFO_ADDR ; 
 int ENODEV ; 
 int /*<<< orphan*/  mvebu_pm_store_armadaxp_bootinfo (int /*<<< orphan*/ *) ; 
 scalar_t__ of_machine_is_compatible (char*) ; 
 int /*<<< orphan*/ * phys_to_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvebu_pm_store_bootinfo(void)
{
	u32 *store_addr;

	store_addr = phys_to_virt(BOOT_INFO_ADDR);

	if (of_machine_is_compatible("marvell,armadaxp"))
		mvebu_pm_store_armadaxp_bootinfo(store_addr);
	else
		return -ENODEV;

	return 0;
}