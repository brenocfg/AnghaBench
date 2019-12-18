#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {scalar_t__ parent; } ;
struct cache_info {TYPE_1__ kobj; } ;
struct TYPE_7__ {unsigned long num_cache_leaves; TYPE_1__ kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ADD ; 
 struct cache_info* LEAF_KOBJECT_PTR (unsigned int,unsigned long) ; 
 TYPE_5__* all_cpu_cache_info ; 
 int /*<<< orphan*/  cache_ktype ; 
 int /*<<< orphan*/  cache_ktype_percpu_entry ; 
 int /*<<< orphan*/  cpu_cache_sysfs_exit (unsigned int) ; 
 int cpu_cache_sysfs_init (unsigned int) ; 
 struct device* get_cpu_device (unsigned int) ; 
 int kobject_init_and_add (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  kobject_put (TYPE_1__*) ; 
 int /*<<< orphan*/  kobject_uevent (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cache_add_dev(unsigned int cpu)
{
	struct device *sys_dev = get_cpu_device(cpu);
	unsigned long i, j;
	struct cache_info *this_object;
	int retval = 0;

	if (all_cpu_cache_info[cpu].kobj.parent)
		return 0;


	retval = cpu_cache_sysfs_init(cpu);
	if (unlikely(retval < 0))
		return retval;

	retval = kobject_init_and_add(&all_cpu_cache_info[cpu].kobj,
				      &cache_ktype_percpu_entry, &sys_dev->kobj,
				      "%s", "cache");
	if (unlikely(retval < 0)) {
		cpu_cache_sysfs_exit(cpu);
		return retval;
	}

	for (i = 0; i < all_cpu_cache_info[cpu].num_cache_leaves; i++) {
		this_object = LEAF_KOBJECT_PTR(cpu,i);
		retval = kobject_init_and_add(&(this_object->kobj),
					      &cache_ktype,
					      &all_cpu_cache_info[cpu].kobj,
					      "index%1lu", i);
		if (unlikely(retval)) {
			for (j = 0; j < i; j++) {
				kobject_put(&(LEAF_KOBJECT_PTR(cpu,j)->kobj));
			}
			kobject_put(&all_cpu_cache_info[cpu].kobj);
			cpu_cache_sysfs_exit(cpu);
			return retval;
		}
		kobject_uevent(&(this_object->kobj), KOBJ_ADD);
	}
	kobject_uevent(&all_cpu_cache_info[cpu].kobj, KOBJ_ADD);
	return retval;
}