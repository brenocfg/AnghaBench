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
typedef  int u32 ;
struct zynqmp_eemi_ops {int /*<<< orphan*/  (* fpga_get_status ) (int*) ;} ;
struct fpga_manager {int dummy; } ;
typedef  enum fpga_mgr_states { ____Placeholder_fpga_mgr_states } fpga_mgr_states ;

/* Variables and functions */
 int FPGA_MGR_STATE_OPERATING ; 
 int FPGA_MGR_STATE_UNKNOWN ; 
 scalar_t__ IS_ERR_OR_NULL (struct zynqmp_eemi_ops const*) ; 
 int IXR_FPGA_DONE_MASK ; 
 int /*<<< orphan*/  stub1 (int*) ; 
 struct zynqmp_eemi_ops* zynqmp_pm_get_eemi_ops () ; 

__attribute__((used)) static enum fpga_mgr_states zynqmp_fpga_ops_state(struct fpga_manager *mgr)
{
	const struct zynqmp_eemi_ops *eemi_ops = zynqmp_pm_get_eemi_ops();
	u32 status;

	if (IS_ERR_OR_NULL(eemi_ops) || !eemi_ops->fpga_get_status)
		return FPGA_MGR_STATE_UNKNOWN;

	eemi_ops->fpga_get_status(&status);
	if (status & IXR_FPGA_DONE_MASK)
		return FPGA_MGR_STATE_OPERATING;

	return FPGA_MGR_STATE_UNKNOWN;
}