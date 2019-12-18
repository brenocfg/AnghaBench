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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct zynqmp_pm_query_data {int /*<<< orphan*/  arg1; int /*<<< orphan*/  qid; int /*<<< orphan*/  member_0; } ;
struct clock_topology {int /*<<< orphan*/  flag; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int (* query_data ) (struct zynqmp_pm_query_data,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 struct clk_hw* ERR_PTR (int) ; 
 int PAYLOAD_ARG_CNT ; 
 int /*<<< orphan*/  PM_QID_CLOCK_GET_FIXEDFACTOR_PARAMS ; 
 struct clk_hw* clk_hw_register_fixed_factor (int /*<<< orphan*/ *,char const*,char const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* eemi_ops ; 
 int stub1 (struct zynqmp_pm_query_data,int /*<<< orphan*/ *) ; 

struct clk_hw *zynqmp_clk_register_fixed_factor(const char *name, u32 clk_id,
					const char * const *parents,
					u8 num_parents,
					const struct clock_topology *nodes)
{
	u32 mult, div;
	struct clk_hw *hw;
	struct zynqmp_pm_query_data qdata = {0};
	u32 ret_payload[PAYLOAD_ARG_CNT];
	int ret;

	qdata.qid = PM_QID_CLOCK_GET_FIXEDFACTOR_PARAMS;
	qdata.arg1 = clk_id;

	ret = eemi_ops->query_data(qdata, ret_payload);
	if (ret)
		return ERR_PTR(ret);

	mult = ret_payload[1];
	div = ret_payload[2];

	hw = clk_hw_register_fixed_factor(NULL, name,
					  parents[0],
					  nodes->flag, mult,
					  div);

	return hw;
}