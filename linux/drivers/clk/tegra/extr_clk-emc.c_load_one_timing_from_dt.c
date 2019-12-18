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
typedef  void* u32 ;
struct tegra_clk_emc {int dummy; } ;
struct emc_timing {int parent_index; int /*<<< orphan*/  parent; void* parent_rate; void* rate; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clk_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * emc_parent_clk_names ; 
 int /*<<< orphan*/  of_clk_get_by_name (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,void**) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_one_timing_from_dt(struct tegra_clk_emc *tegra,
				   struct emc_timing *timing,
				   struct device_node *node)
{
	int err, i;
	u32 tmp;

	err = of_property_read_u32(node, "clock-frequency", &tmp);
	if (err) {
		pr_err("timing %pOF: failed to read rate\n", node);
		return err;
	}

	timing->rate = tmp;

	err = of_property_read_u32(node, "nvidia,parent-clock-frequency", &tmp);
	if (err) {
		pr_err("timing %pOF: failed to read parent rate\n", node);
		return err;
	}

	timing->parent_rate = tmp;

	timing->parent = of_clk_get_by_name(node, "emc-parent");
	if (IS_ERR(timing->parent)) {
		pr_err("timing %pOF: failed to get parent clock\n", node);
		return PTR_ERR(timing->parent);
	}

	timing->parent_index = 0xff;
	for (i = 0; i < ARRAY_SIZE(emc_parent_clk_names); i++) {
		if (!strcmp(emc_parent_clk_names[i],
			    __clk_get_name(timing->parent))) {
			timing->parent_index = i;
			break;
		}
	}
	if (timing->parent_index == 0xff) {
		pr_err("timing %pOF: %s is not a valid parent\n",
		       node, __clk_get_name(timing->parent));
		clk_put(timing->parent);
		return -EINVAL;
	}

	return 0;
}