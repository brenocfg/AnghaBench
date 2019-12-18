#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct of_phandle_args {scalar_t__ np; int* args; } ;
struct TYPE_3__ {scalar_t__ of_node; } ;
struct generic_pm_domain {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_4__ {scalar_t__ managed; } ;

/* Variables and functions */
 int R9A06G032_CLOCK_COUNT ; 
 int create_add_module_clock (struct of_phandle_args*,struct device*) ; 
 int /*<<< orphan*/  of_node_put (scalar_t__) ; 
 int /*<<< orphan*/  of_parse_phandle_with_args (struct device_node*,char*,char*,int,struct of_phandle_args*) ; 
 TYPE_2__* r9a06g032_clocks ; 

__attribute__((used)) static int r9a06g032_attach_dev(struct generic_pm_domain *pd,
				struct device *dev)
{
	struct device_node *np = dev->of_node;
	struct of_phandle_args clkspec;
	int i = 0;
	int error;
	int index;

	while (!of_parse_phandle_with_args(np, "clocks", "#clock-cells", i,
					   &clkspec)) {
		if (clkspec.np != pd->dev.of_node)
			continue;

		index = clkspec.args[0];
		if (index < R9A06G032_CLOCK_COUNT &&
		    r9a06g032_clocks[index].managed) {
			error = create_add_module_clock(&clkspec, dev);
			of_node_put(clkspec.np);
			if (error)
				return error;
		}
		i++;
	}

	return 0;
}