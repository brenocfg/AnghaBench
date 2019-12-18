#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct kobj_ns_type_operations {int dummy; } ;
struct class_dir {TYPE_1__* class; } ;
struct TYPE_2__ {struct kobj_ns_type_operations const* ns_type; } ;

/* Variables and functions */
 struct class_dir* to_class_dir (struct kobject*) ; 

__attribute__((used)) static const
struct kobj_ns_type_operations *class_dir_child_ns_type(struct kobject *kobj)
{
	struct class_dir *dir = to_class_dir(kobj);
	return dir->class->ns_type;
}