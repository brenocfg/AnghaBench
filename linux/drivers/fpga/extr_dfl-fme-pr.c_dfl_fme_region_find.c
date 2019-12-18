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
struct fpga_region {int dummy; } ;
struct dfl_fme_region {TYPE_1__* region; } ;
struct dfl_fme {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct dfl_fme_region* dfl_fme_region_find_by_port_id (struct dfl_fme*,int) ; 
 int /*<<< orphan*/  dfl_fme_region_match ; 
 struct fpga_region* fpga_region_class_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fpga_region *dfl_fme_region_find(struct dfl_fme *fme, int port_id)
{
	struct dfl_fme_region *fme_region;
	struct fpga_region *region;

	fme_region = dfl_fme_region_find_by_port_id(fme, port_id);
	if (!fme_region)
		return NULL;

	region = fpga_region_class_find(NULL, &fme_region->region->dev,
					dfl_fme_region_match);
	if (!region)
		return NULL;

	return region;
}