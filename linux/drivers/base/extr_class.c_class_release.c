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
struct class {int /*<<< orphan*/  name; int /*<<< orphan*/  (* class_release ) (struct class*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct subsys_private*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct class*) ; 
 struct subsys_private* to_subsys_private (struct kobject*) ; 

__attribute__((used)) static void class_release(struct kobject *kobj)
{
	struct subsys_private *cp = to_subsys_private(kobj);
	struct class *class = cp->class;

	pr_debug("class '%s': release.\n", class->name);

	if (class->class_release)
		class->class_release(class);
	else
		pr_debug("class '%s' does not have a release() function, "
			 "be careful\n", class->name);

	kfree(cp);
}