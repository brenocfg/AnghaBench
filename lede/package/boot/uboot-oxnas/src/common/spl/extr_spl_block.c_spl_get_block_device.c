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
 int /*<<< orphan*/  CONFIG_SPL_BLOCKDEV_ID ; 
 char* CONFIG_SPL_BLOCKDEV_INTERFACE ; 
 int /*<<< orphan*/ * get_dev (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hang () ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_block_device_init () ; 

block_dev_desc_t * spl_get_block_device(void)
{
	block_dev_desc_t * device;

	spl_block_device_init();

	device = get_dev(CONFIG_SPL_BLOCKDEV_INTERFACE, CONFIG_SPL_BLOCKDEV_ID);
	if (!device) {
		printf("blk device %s%d not exists\n",
			CONFIG_SPL_BLOCKDEV_INTERFACE,
			CONFIG_SPL_BLOCKDEV_ID);
		hang();
	}

	return device;
}