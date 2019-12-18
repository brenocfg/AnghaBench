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
 int /*<<< orphan*/  fw_cfg_dev_base ; 
 scalar_t__ fw_cfg_is_mmio ; 
 int /*<<< orphan*/  fw_cfg_p_base ; 
 int /*<<< orphan*/  fw_cfg_p_size ; 
 int /*<<< orphan*/  ioport_unmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fw_cfg_io_cleanup(void)
{
	if (fw_cfg_is_mmio) {
		iounmap(fw_cfg_dev_base);
		release_mem_region(fw_cfg_p_base, fw_cfg_p_size);
	} else {
		ioport_unmap(fw_cfg_dev_base);
		release_region(fw_cfg_p_base, fw_cfg_p_size);
	}
}