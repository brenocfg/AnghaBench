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
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmm_attrs ; 
 int /*<<< orphan*/  cmm_subsys ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 

__attribute__((used)) static void cmm_unregister_sysfs(struct device *dev)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(cmm_attrs); i++)
		device_remove_file(dev, cmm_attrs[i]);
	device_unregister(dev);
	bus_unregister(&cmm_subsys);
}