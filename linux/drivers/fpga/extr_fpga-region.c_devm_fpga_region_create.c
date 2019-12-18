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
struct fpga_region {int dummy; } ;
struct fpga_manager {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_fpga_region_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct fpga_region**) ; 
 struct fpga_region** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct fpga_region**) ; 
 struct fpga_region* fpga_region_create (struct device*,struct fpga_manager*,int (*) (struct fpga_region*)) ; 

struct fpga_region
*devm_fpga_region_create(struct device *dev,
			 struct fpga_manager *mgr,
			 int (*get_bridges)(struct fpga_region *))
{
	struct fpga_region **ptr, *region;

	ptr = devres_alloc(devm_fpga_region_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return NULL;

	region = fpga_region_create(dev, mgr, get_bridges);
	if (!region) {
		devres_free(ptr);
	} else {
		*ptr = region;
		devres_add(dev, ptr);
	}

	return region;
}