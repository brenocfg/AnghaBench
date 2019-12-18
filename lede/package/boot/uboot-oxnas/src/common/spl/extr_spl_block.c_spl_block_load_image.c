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
typedef  int /*<<< orphan*/  block_dev_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SYS_BLOCK_RAW_MODE_U_BOOT_SECTOR ; 
 int block_load_image_raw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ block_load_image_raw_os (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hang () ; 
 int /*<<< orphan*/ * spl_get_block_device () ; 
 scalar_t__ spl_start_uboot () ; 

void spl_block_load_image(void)
{
	int err;
	block_dev_desc_t * device;

	device = spl_get_block_device();
#ifdef CONFIG_SPL_OS_BOOT
	if (spl_start_uboot() || block_load_image_raw_os(device))
#endif
	{
		err = block_load_image_raw(device,
					 CONFIG_SYS_BLOCK_RAW_MODE_U_BOOT_SECTOR);
		if (err)
			hang();
	}
}