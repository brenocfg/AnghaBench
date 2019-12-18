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
struct resource {int /*<<< orphan*/  start; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct dax_region {unsigned long pfn_flags; int id; unsigned int align; int target_node; int /*<<< orphan*/  kref; struct device* dev; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dax_region_attribute_groups ; 
 int /*<<< orphan*/  dax_region_unregister ; 
 int /*<<< orphan*/  dev_WARN (struct device*,char*) ; 
 scalar_t__ dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct dax_region*) ; 
 scalar_t__ devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct dax_region*) ; 
 int /*<<< orphan*/  kfree (struct dax_region*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct dax_region* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct resource*,int) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 scalar_t__ sysfs_create_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct dax_region *alloc_dax_region(struct device *parent, int region_id,
		struct resource *res, int target_node, unsigned int align,
		unsigned long pfn_flags)
{
	struct dax_region *dax_region;

	/*
	 * The DAX core assumes that it can store its private data in
	 * parent->driver_data. This WARN is a reminder / safeguard for
	 * developers of device-dax drivers.
	 */
	if (dev_get_drvdata(parent)) {
		dev_WARN(parent, "dax core failed to setup private data\n");
		return NULL;
	}

	if (!IS_ALIGNED(res->start, align)
			|| !IS_ALIGNED(resource_size(res), align))
		return NULL;

	dax_region = kzalloc(sizeof(*dax_region), GFP_KERNEL);
	if (!dax_region)
		return NULL;

	dev_set_drvdata(parent, dax_region);
	memcpy(&dax_region->res, res, sizeof(*res));
	dax_region->pfn_flags = pfn_flags;
	kref_init(&dax_region->kref);
	dax_region->id = region_id;
	dax_region->align = align;
	dax_region->dev = parent;
	dax_region->target_node = target_node;
	if (sysfs_create_groups(&parent->kobj, dax_region_attribute_groups)) {
		kfree(dax_region);
		return NULL;
	}

	kref_get(&dax_region->kref);
	if (devm_add_action_or_reset(parent, dax_region_unregister, dax_region))
		return NULL;
	return dax_region;
}