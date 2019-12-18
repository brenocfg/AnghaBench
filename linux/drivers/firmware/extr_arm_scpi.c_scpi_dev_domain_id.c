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
struct of_phandle_args {int* args; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ of_parse_phandle_with_args (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,struct of_phandle_args*) ; 

__attribute__((used)) static int scpi_dev_domain_id(struct device *dev)
{
	struct of_phandle_args clkspec;

	if (of_parse_phandle_with_args(dev->of_node, "clocks", "#clock-cells",
				       0, &clkspec))
		return -EINVAL;

	return clkspec.args[0];
}