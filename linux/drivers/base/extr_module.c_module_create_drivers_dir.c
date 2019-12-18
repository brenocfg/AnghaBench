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
struct module_kobject {int /*<<< orphan*/  kobj; scalar_t__ drivers_dir; } ;
typedef  int /*<<< orphan*/  DEFINE_MUTEX ;

/* Variables and functions */
 scalar_t__ kobject_create_and_add (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void module_create_drivers_dir(struct module_kobject *mk)
{
	static DEFINE_MUTEX(drivers_dir_mutex);

	mutex_lock(&drivers_dir_mutex);
	if (mk && !mk->drivers_dir)
		mk->drivers_dir = kobject_create_and_add("drivers", &mk->kobj);
	mutex_unlock(&drivers_dir_mutex);
}