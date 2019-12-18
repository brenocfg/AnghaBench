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
struct device {int /*<<< orphan*/ * bus; scalar_t__ id; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmm_attrs ; 
 int /*<<< orphan*/  cmm_subsys ; 
 int device_create_file (struct device*,int /*<<< orphan*/ ) ; 
 int device_register (struct device*) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int subsys_system_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmm_sysfs_register(struct device *dev)
{
	int i, rc;

	if ((rc = subsys_system_register(&cmm_subsys, NULL)))
		return rc;

	dev->id = 0;
	dev->bus = &cmm_subsys;

	if ((rc = device_register(dev)))
		goto subsys_unregister;

	for (i = 0; i < ARRAY_SIZE(cmm_attrs); i++) {
		if ((rc = device_create_file(dev, cmm_attrs[i])))
			goto fail;
	}

	return 0;

fail:
	while (--i >= 0)
		device_remove_file(dev, cmm_attrs[i]);
	device_unregister(dev);
subsys_unregister:
	bus_unregister(&cmm_subsys);
	return rc;
}