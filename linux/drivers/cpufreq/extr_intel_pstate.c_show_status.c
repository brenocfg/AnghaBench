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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pstate_driver_lock ; 
 int /*<<< orphan*/  intel_pstate_show_status (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t show_status(struct kobject *kobj,
			   struct kobj_attribute *attr, char *buf)
{
	ssize_t ret;

	mutex_lock(&intel_pstate_driver_lock);
	ret = intel_pstate_show_status(buf);
	mutex_unlock(&intel_pstate_driver_lock);

	return ret;
}