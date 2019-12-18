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
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int PMU_FL_TFA ; 
 TYPE_2__ dev_attr_allow_tsx_force_abort ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static umode_t
default_is_visible(struct kobject *kobj, struct attribute *attr, int i)
{
	if (attr == &dev_attr_allow_tsx_force_abort.attr)
		return x86_pmu.flags & PMU_FL_TFA ? attr->mode : 0;

	return attr->mode;
}