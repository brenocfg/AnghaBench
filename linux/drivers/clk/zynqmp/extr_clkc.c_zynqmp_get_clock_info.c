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
typedef  scalar_t__ u32 ;
struct name_resp {int /*<<< orphan*/  name; } ;
struct attr_resp {int /*<<< orphan*/ * attr; } ;
struct TYPE_2__ {int clk_id; int /*<<< orphan*/  num_parents; int /*<<< orphan*/  parent; int /*<<< orphan*/  num_nodes; int /*<<< orphan*/  node; int /*<<< orphan*/  clk_name; scalar_t__ type; scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_ATTR_NODE_CLASS ; 
 int /*<<< orphan*/  CLK_ATTR_NODE_INDEX ; 
 int /*<<< orphan*/  CLK_ATTR_NODE_SUBCLASS ; 
 int /*<<< orphan*/  CLK_ATTR_NODE_TYPE ; 
 int /*<<< orphan*/  CLK_ATTR_TYPE ; 
 int /*<<< orphan*/  CLK_ATTR_VALID ; 
 scalar_t__ CLK_TYPE_EXTERNAL ; 
 scalar_t__ CLK_TYPE_OUTPUT ; 
 scalar_t__ FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAX_NAME_LEN ; 
 int /*<<< orphan*/  RESERVED_CLK_NAME ; 
 TYPE_1__* clock ; 
 int clock_max_idx ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zynqmp_clock_get_parents (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zynqmp_clock_get_topology (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zynqmp_get_clock_type (int,scalar_t__*) ; 
 int zynqmp_pm_clock_get_attributes (int,struct attr_resp*) ; 
 int /*<<< orphan*/  zynqmp_pm_clock_get_name (int,struct name_resp*) ; 

__attribute__((used)) static void zynqmp_get_clock_info(void)
{
	int i, ret;
	u32 type = 0;
	u32 nodetype, subclass, class;
	struct attr_resp attr;
	struct name_resp name;

	for (i = 0; i < clock_max_idx; i++) {
		ret = zynqmp_pm_clock_get_attributes(i, &attr);
		if (ret)
			continue;

		clock[i].valid = FIELD_GET(CLK_ATTR_VALID, attr.attr[0]);
		clock[i].type = FIELD_GET(CLK_ATTR_TYPE, attr.attr[0]) ?
			CLK_TYPE_EXTERNAL : CLK_TYPE_OUTPUT;

		nodetype = FIELD_GET(CLK_ATTR_NODE_TYPE, attr.attr[0]);
		subclass = FIELD_GET(CLK_ATTR_NODE_SUBCLASS, attr.attr[0]);
		class = FIELD_GET(CLK_ATTR_NODE_CLASS, attr.attr[0]);

		clock[i].clk_id = FIELD_PREP(CLK_ATTR_NODE_CLASS, class) |
				  FIELD_PREP(CLK_ATTR_NODE_SUBCLASS, subclass) |
				  FIELD_PREP(CLK_ATTR_NODE_TYPE, nodetype) |
				  FIELD_PREP(CLK_ATTR_NODE_INDEX, i);

		zynqmp_pm_clock_get_name(clock[i].clk_id, &name);
		if (!strcmp(name.name, RESERVED_CLK_NAME))
			continue;
		strncpy(clock[i].clk_name, name.name, MAX_NAME_LEN);
	}

	/* Get topology of all clock */
	for (i = 0; i < clock_max_idx; i++) {
		ret = zynqmp_get_clock_type(i, &type);
		if (ret || type != CLK_TYPE_OUTPUT)
			continue;

		ret = zynqmp_clock_get_topology(i, clock[i].node,
						&clock[i].num_nodes);
		if (ret)
			continue;

		ret = zynqmp_clock_get_parents(i, clock[i].parent,
					       &clock[i].num_parents);
		if (ret)
			continue;
	}
}