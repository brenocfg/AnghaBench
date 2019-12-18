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
struct kobject {struct kobject* parent; } ;
struct device {unsigned int id; } ;
struct cache_index_dir {struct kobject kobj; } ;

/* Variables and functions */
 struct device* kobj_to_dev (struct kobject*) ; 

__attribute__((used)) static unsigned int index_dir_to_cpu(struct cache_index_dir *index)
{
	struct kobject *index_dir_kobj = &index->kobj;
	struct kobject *cache_dir_kobj = index_dir_kobj->parent;
	struct kobject *cpu_dev_kobj = cache_dir_kobj->parent;
	struct device *dev = kobj_to_dev(cpu_dev_kobj);

	return dev->id;
}