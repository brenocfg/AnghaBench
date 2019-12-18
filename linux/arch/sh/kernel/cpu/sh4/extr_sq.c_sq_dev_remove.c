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
struct subsys_interface {int dummy; } ;
struct kobject {int dummy; } ;
struct device {unsigned int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 struct kobject** sq_kobject ; 

__attribute__((used)) static void sq_dev_remove(struct device *dev, struct subsys_interface *sif)
{
	unsigned int cpu = dev->id;
	struct kobject *kobj = sq_kobject[cpu];

	kobject_put(kobj);
}