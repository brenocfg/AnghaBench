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
struct platform_device {int dummy; } ;
struct fpga_region {struct fpga_manager* mgr; } ;
struct fpga_manager {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fpga_mgr_put (struct fpga_manager*) ; 
 int /*<<< orphan*/  fpga_region_unregister (struct fpga_region*) ; 
 struct fpga_region* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int fme_region_remove(struct platform_device *pdev)
{
	struct fpga_region *region = platform_get_drvdata(pdev);
	struct fpga_manager *mgr = region->mgr;

	fpga_region_unregister(region);
	fpga_mgr_put(mgr);

	return 0;
}