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
typedef  size_t u32 ;
struct device_node {int dummy; } ;
struct clock_topology {size_t type; } ;
struct clock_parent {int flag; char* name; } ;
struct TYPE_2__ {size_t num_parents; struct clock_parent* parent; struct clock_topology* node; } ;

/* Variables and functions */
 int PARENT_CLK_EXTERNAL ; 
 int /*<<< orphan*/ * clk_type_postfix ; 
 TYPE_1__* clock ; 
 int of_property_match_string (struct device_node*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int zynqmp_get_parent_list(struct device_node *np, u32 clk_id,
				  const char **parent_list, u32 *num_parents)
{
	int i = 0, ret;
	u32 total_parents = clock[clk_id].num_parents;
	struct clock_topology *clk_nodes;
	struct clock_parent *parents;

	clk_nodes = clock[clk_id].node;
	parents = clock[clk_id].parent;

	for (i = 0; i < total_parents; i++) {
		if (!parents[i].flag) {
			parent_list[i] = parents[i].name;
		} else if (parents[i].flag == PARENT_CLK_EXTERNAL) {
			ret = of_property_match_string(np, "clock-names",
						       parents[i].name);
			if (ret < 0)
				strcpy(parents[i].name, "dummy_name");
			parent_list[i] = parents[i].name;
		} else {
			strcat(parents[i].name,
			       clk_type_postfix[clk_nodes[parents[i].flag - 1].
			       type]);
			parent_list[i] = parents[i].name;
		}
	}

	*num_parents = total_parents;
	return 0;
}