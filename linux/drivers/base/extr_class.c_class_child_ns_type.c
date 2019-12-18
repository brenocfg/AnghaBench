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
struct subsys_private {struct class* class; } ;
struct kobject {int dummy; } ;
struct kobj_ns_type_operations {int dummy; } ;
struct class {struct kobj_ns_type_operations const* ns_type; } ;

/* Variables and functions */
 struct subsys_private* to_subsys_private (struct kobject*) ; 

__attribute__((used)) static const struct kobj_ns_type_operations *class_child_ns_type(struct kobject *kobj)
{
	struct subsys_private *cp = to_subsys_private(kobj);
	struct class *class = cp->class;

	return class->ns_type;
}