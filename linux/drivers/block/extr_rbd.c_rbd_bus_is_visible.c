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
typedef  int /*<<< orphan*/  umode_t ;
struct kobject {int dummy; } ;
struct attribute {int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {struct attribute attr; } ;
struct TYPE_3__ {struct attribute attr; } ;

/* Variables and functions */
 TYPE_2__ bus_attr_add_single_major ; 
 TYPE_1__ bus_attr_remove_single_major ; 
 int /*<<< orphan*/  single_major ; 

__attribute__((used)) static umode_t rbd_bus_is_visible(struct kobject *kobj,
				  struct attribute *attr, int index)
{
	if (!single_major &&
	    (attr == &bus_attr_add_single_major.attr ||
	     attr == &bus_attr_remove_single_major.attr))
		return 0;

	return attr->mode;
}