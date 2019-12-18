#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct kobject {int dummy; } ;
struct device {int dummy; } ;
struct cpumask {int dummy; } ;
struct cacheinfo {int attributes; scalar_t__ physical_line_partition; scalar_t__ size; scalar_t__ number_of_sets; scalar_t__ coherency_line_size; scalar_t__ level; scalar_t__ type; struct cpumask shared_cpu_map; } ;
struct attribute {int /*<<< orphan*/  mode; } ;
struct TYPE_24__ {struct attribute attr; } ;
struct TYPE_23__ {struct attribute attr; } ;
struct TYPE_22__ {struct attribute attr; } ;
struct TYPE_21__ {struct attribute attr; } ;
struct TYPE_20__ {struct attribute attr; } ;
struct TYPE_19__ {struct attribute attr; } ;
struct TYPE_18__ {struct attribute attr; } ;
struct TYPE_17__ {struct attribute attr; } ;
struct TYPE_16__ {struct attribute attr; } ;
struct TYPE_15__ {struct attribute attr; } ;
struct TYPE_14__ {struct attribute attr; } ;
struct TYPE_13__ {struct attribute attr; } ;

/* Variables and functions */
 int CACHE_ALLOCATE_POLICY_MASK ; 
 int CACHE_ID ; 
 int CACHE_WRITE_POLICY_MASK ; 
 int /*<<< orphan*/  cpumask_empty (struct cpumask const*) ; 
 TYPE_12__ dev_attr_allocation_policy ; 
 TYPE_11__ dev_attr_coherency_line_size ; 
 TYPE_10__ dev_attr_id ; 
 TYPE_9__ dev_attr_level ; 
 TYPE_8__ dev_attr_number_of_sets ; 
 TYPE_7__ dev_attr_physical_line_partition ; 
 TYPE_6__ dev_attr_shared_cpu_list ; 
 TYPE_5__ dev_attr_shared_cpu_map ; 
 TYPE_4__ dev_attr_size ; 
 TYPE_3__ dev_attr_type ; 
 TYPE_2__ dev_attr_ways_of_associativity ; 
 TYPE_1__ dev_attr_write_policy ; 
 struct cacheinfo* dev_get_drvdata (struct device*) ; 
 struct device* kobj_to_dev (struct kobject*) ; 

__attribute__((used)) static umode_t
cache_default_attrs_is_visible(struct kobject *kobj,
			       struct attribute *attr, int unused)
{
	struct device *dev = kobj_to_dev(kobj);
	struct cacheinfo *this_leaf = dev_get_drvdata(dev);
	const struct cpumask *mask = &this_leaf->shared_cpu_map;
	umode_t mode = attr->mode;

	if ((attr == &dev_attr_id.attr) && (this_leaf->attributes & CACHE_ID))
		return mode;
	if ((attr == &dev_attr_type.attr) && this_leaf->type)
		return mode;
	if ((attr == &dev_attr_level.attr) && this_leaf->level)
		return mode;
	if ((attr == &dev_attr_shared_cpu_map.attr) && !cpumask_empty(mask))
		return mode;
	if ((attr == &dev_attr_shared_cpu_list.attr) && !cpumask_empty(mask))
		return mode;
	if ((attr == &dev_attr_coherency_line_size.attr) &&
	    this_leaf->coherency_line_size)
		return mode;
	if ((attr == &dev_attr_ways_of_associativity.attr) &&
	    this_leaf->size) /* allow 0 = full associativity */
		return mode;
	if ((attr == &dev_attr_number_of_sets.attr) &&
	    this_leaf->number_of_sets)
		return mode;
	if ((attr == &dev_attr_size.attr) && this_leaf->size)
		return mode;
	if ((attr == &dev_attr_write_policy.attr) &&
	    (this_leaf->attributes & CACHE_WRITE_POLICY_MASK))
		return mode;
	if ((attr == &dev_attr_allocation_policy.attr) &&
	    (this_leaf->attributes & CACHE_ALLOCATE_POLICY_MASK))
		return mode;
	if ((attr == &dev_attr_physical_line_partition.attr) &&
	    this_leaf->physical_line_partition)
		return mode;

	return 0;
}