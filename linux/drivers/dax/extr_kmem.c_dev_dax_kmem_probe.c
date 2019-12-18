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
struct resource {int start; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;
struct device {int dummy; } ;
struct dev_dax {int target_node; struct resource* dax_kmem_res; TYPE_1__* region; } ;
typedef  int resource_size_t ;
struct TYPE_2__ {struct resource res; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_SYSTEM_RAM ; 
 int add_memory (int,int,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int /*<<< orphan*/  kfree (struct resource*) ; 
 int memory_block_size_bytes () ; 
 int /*<<< orphan*/  release_resource (struct resource*) ; 
 struct resource* request_mem_region (int,int,int /*<<< orphan*/ ) ; 
 int resource_size (struct resource*) ; 
 struct dev_dax* to_dev_dax (struct device*) ; 

int dev_dax_kmem_probe(struct device *dev)
{
	struct dev_dax *dev_dax = to_dev_dax(dev);
	struct resource *res = &dev_dax->region->res;
	resource_size_t kmem_start;
	resource_size_t kmem_size;
	resource_size_t kmem_end;
	struct resource *new_res;
	int numa_node;
	int rc;

	/*
	 * Ensure good NUMA information for the persistent memory.
	 * Without this check, there is a risk that slow memory
	 * could be mixed in a node with faster memory, causing
	 * unavoidable performance issues.
	 */
	numa_node = dev_dax->target_node;
	if (numa_node < 0) {
		dev_warn(dev, "rejecting DAX region %pR with invalid node: %d\n",
			 res, numa_node);
		return -EINVAL;
	}

	/* Hotplug starting at the beginning of the next block: */
	kmem_start = ALIGN(res->start, memory_block_size_bytes());

	kmem_size = resource_size(res);
	/* Adjust the size down to compensate for moving up kmem_start: */
	kmem_size -= kmem_start - res->start;
	/* Align the size down to cover only complete blocks: */
	kmem_size &= ~(memory_block_size_bytes() - 1);
	kmem_end = kmem_start + kmem_size;

	/* Region is permanently reserved.  Hot-remove not yet implemented. */
	new_res = request_mem_region(kmem_start, kmem_size, dev_name(dev));
	if (!new_res) {
		dev_warn(dev, "could not reserve region [%pa-%pa]\n",
			 &kmem_start, &kmem_end);
		return -EBUSY;
	}

	/*
	 * Set flags appropriate for System RAM.  Leave ..._BUSY clear
	 * so that add_memory() can add a child resource.  Do not
	 * inherit flags from the parent since it may set new flags
	 * unknown to us that will break add_memory() below.
	 */
	new_res->flags = IORESOURCE_SYSTEM_RAM;
	new_res->name = dev_name(dev);

	rc = add_memory(numa_node, new_res->start, resource_size(new_res));
	if (rc) {
		release_resource(new_res);
		kfree(new_res);
		return rc;
	}
	dev_dax->dax_kmem_res = new_res;

	return 0;
}