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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fpga_region_free (struct fpga_region*) ; 

__attribute__((used)) static void devm_fpga_region_release(struct device *dev, void *res)
{
	struct fpga_region *region = *(struct fpga_region **)res;

	fpga_region_free(region);
}