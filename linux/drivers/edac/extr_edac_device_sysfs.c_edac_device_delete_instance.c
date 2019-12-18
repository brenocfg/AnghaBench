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
struct edac_device_instance {int nr_blocks; int /*<<< orphan*/  kobj; int /*<<< orphan*/ * blocks; } ;
struct edac_device_ctl_info {struct edac_device_instance* instances; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_device_delete_block (struct edac_device_ctl_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void edac_device_delete_instance(struct edac_device_ctl_info *edac_dev,
					int idx)
{
	struct edac_device_instance *instance;
	int i;

	instance = &edac_dev->instances[idx];

	/* unregister all blocks in this instance */
	for (i = 0; i < instance->nr_blocks; i++)
		edac_device_delete_block(edac_dev, &instance->blocks[i]);

	/* unregister this instance's kobject, SEE:
	 *	edac_device_ctrl_instance_release() for callback operation
	 */
	kobject_put(&instance->kobj);
}