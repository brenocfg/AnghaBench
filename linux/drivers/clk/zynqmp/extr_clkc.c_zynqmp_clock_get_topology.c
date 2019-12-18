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
struct topology_resp {int /*<<< orphan*/  topology; } ;
struct clock_topology {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk_id; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int END_OF_TOPOLOGY_NODE ; 
 int MAX_NODES ; 
 int __zynqmp_clock_get_topology (struct clock_topology*,struct topology_resp*,size_t*) ; 
 TYPE_1__* clock ; 
 int zynqmp_pm_clock_get_topology (int /*<<< orphan*/ ,int,struct topology_resp*) ; 

__attribute__((used)) static int zynqmp_clock_get_topology(u32 clk_id,
				     struct clock_topology *topology,
				     u32 *num_nodes)
{
	int j, ret;
	struct topology_resp response = { };

	*num_nodes = 0;
	for (j = 0; j <= MAX_NODES; j += ARRAY_SIZE(response.topology)) {
		ret = zynqmp_pm_clock_get_topology(clock[clk_id].clk_id, j,
						   &response);
		if (ret)
			return ret;
		ret = __zynqmp_clock_get_topology(topology, &response,
						  num_nodes);
		if (ret == END_OF_TOPOLOGY_NODE)
			return 0;
	}

	return 0;
}