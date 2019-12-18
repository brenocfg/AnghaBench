#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct edac_device_block {TYPE_2__* instance; } ;
struct TYPE_4__ {TYPE_1__* ctl; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int,char*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 struct edac_device_block* to_block (struct kobject*) ; 

__attribute__((used)) static void edac_device_ctrl_block_release(struct kobject *kobj)
{
	struct edac_device_block *block;

	edac_dbg(1, "\n");

	/* get the container of the kobj */
	block = to_block(kobj);

	/* map from 'block kobj' to 'block->instance->controller->main_kobj'
	 * now 'release' the block kobject
	 */
	kobject_put(&block->instance->ctl->kobj);
}