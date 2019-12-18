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
struct devinfo_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVINFO_ROOT_DEVICE ; 
 int /*<<< orphan*/  acpi0_check ; 
 int devinfo_foreach_device_child (struct devinfo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devinfo_free () ; 
 struct devinfo_dev* devinfo_handle_to_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devinfo_init () ; 

__attribute__((used)) static int
acpi0_present(void)
{
	struct devinfo_dev *root;
	int found;

	found = 0;
	devinfo_init();
	root = devinfo_handle_to_device(DEVINFO_ROOT_DEVICE);
	if (root != NULL)
		found = devinfo_foreach_device_child(root, acpi0_check, NULL);
	devinfo_free();
	return found;
}