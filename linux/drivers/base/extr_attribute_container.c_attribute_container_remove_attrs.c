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
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct attribute_container {scalar_t__ grp; struct device_attribute** attrs; } ;

/* Variables and functions */
 struct attribute_container* attribute_container_classdev_to_container (struct device*) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,struct device_attribute*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,scalar_t__) ; 

void
attribute_container_remove_attrs(struct device *classdev)
{
	struct attribute_container *cont =
		attribute_container_classdev_to_container(classdev);
	struct device_attribute **attrs = cont->attrs;
	int i;

	if (!attrs && !cont->grp)
		return;

	if (cont->grp) {
		sysfs_remove_group(&classdev->kobj, cont->grp);
		return ;
	}

	for (i = 0; attrs[i]; i++)
		device_remove_file(classdev, attrs[i]);
}