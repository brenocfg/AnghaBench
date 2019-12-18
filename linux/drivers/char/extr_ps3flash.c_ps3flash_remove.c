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
struct ps3_system_bus_device {int /*<<< orphan*/  core; } ;
struct ps3_storage_device {int /*<<< orphan*/  sbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ps3_os_area_flash_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ps3_system_bus_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ps3_system_bus_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ps3flash_dev ; 
 int /*<<< orphan*/  ps3flash_misc ; 
 int /*<<< orphan*/  ps3stor_teardown (struct ps3_storage_device*) ; 
 struct ps3_storage_device* to_ps3_storage_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ps3flash_remove(struct ps3_system_bus_device *_dev)
{
	struct ps3_storage_device *dev = to_ps3_storage_device(&_dev->core);

	ps3_os_area_flash_register(NULL);
	misc_deregister(&ps3flash_misc);
	ps3stor_teardown(dev);
	kfree(ps3_system_bus_get_drvdata(&dev->sbd));
	ps3_system_bus_set_drvdata(&dev->sbd, NULL);
	ps3flash_dev = NULL;
	return 0;
}