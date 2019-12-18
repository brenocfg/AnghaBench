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
struct fpga_bridge {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fpga_bridge_free (struct fpga_bridge*) ; 

__attribute__((used)) static void devm_fpga_bridge_release(struct device *dev, void *res)
{
	struct fpga_bridge *bridge = *(struct fpga_bridge **)res;

	fpga_bridge_free(bridge);
}