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
struct dev_dax {struct dax_region* region; } ;
struct dax_region {int target_node; } ;

/* Variables and functions */

__attribute__((used)) static int dev_dax_target_node(struct dev_dax *dev_dax)
{
	struct dax_region *dax_region = dev_dax->region;

	return dax_region->target_node;
}