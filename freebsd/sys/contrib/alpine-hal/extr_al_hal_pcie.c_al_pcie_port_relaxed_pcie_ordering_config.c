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
struct al_pcie_relaxed_ordering_params {scalar_t__ enable_rx_relaxed_ordering; scalar_t__ enable_tx_relaxed_ordering; } ;
struct TYPE_3__ {int /*<<< orphan*/  pos_cntl; } ;
struct TYPE_4__ {TYPE_1__ ordering; } ;
struct al_pcie_regs {TYPE_2__ axi; } ;
struct al_pcie_port {struct al_pcie_regs* regs; } ;
typedef  enum al_pcie_operating_mode { ____Placeholder_al_pcie_operating_mode } al_pcie_operating_mode ;
typedef  scalar_t__ al_bool ;

/* Variables and functions */
 scalar_t__ AL_FALSE ; 
 int AL_PCIE_OPERATING_MODE_RC ; 
 scalar_t__ AL_TRUE ; 
 int PCIE_AXI_POS_ORDER_BYPASS_CMPL_AFTER_WR_FIX ; 
 int PCIE_AXI_POS_ORDER_EP_CMPL_AFTER_WR_DIS ; 
 int PCIE_AXI_POS_ORDER_EP_CMPL_AFTER_WR_SUPPORT_INTERLV_DIS ; 
 int PCIE_AXI_POS_ORDER_SEGMENT_BUFFER_DONT_WAIT_FOR_P_WRITES ; 
 int al_pcie_operating_mode_get (struct al_pcie_port*) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
al_pcie_port_relaxed_pcie_ordering_config(
	struct al_pcie_port *pcie_port,
	struct al_pcie_relaxed_ordering_params *relaxed_ordering_params)
{
	struct al_pcie_regs *regs = pcie_port->regs;
	enum al_pcie_operating_mode op_mode = al_pcie_operating_mode_get(pcie_port);
	/**
	 * Default:
	 *  - RC: Rx relaxed ordering only
	 *  - EP: TX relaxed ordering only
	 */
	al_bool tx_relaxed_ordering = (op_mode == AL_PCIE_OPERATING_MODE_RC ? AL_FALSE : AL_TRUE);
	al_bool rx_relaxed_ordering = (op_mode == AL_PCIE_OPERATING_MODE_RC ? AL_TRUE : AL_FALSE);

	if (relaxed_ordering_params) {
		tx_relaxed_ordering = relaxed_ordering_params->enable_tx_relaxed_ordering;
		rx_relaxed_ordering = relaxed_ordering_params->enable_rx_relaxed_ordering;
	}

	/** PCIe ordering:
	 *  - disable outbound completion must be stalled behind outbound write
	 *    ordering rule enforcement is disabled for root-port
	 *  - disables read completion on the master port push slave writes for end-point
	 */
	al_reg_write32_masked(
		regs->axi.ordering.pos_cntl,
		PCIE_AXI_POS_ORDER_BYPASS_CMPL_AFTER_WR_FIX |
		PCIE_AXI_POS_ORDER_EP_CMPL_AFTER_WR_DIS |
		PCIE_AXI_POS_ORDER_EP_CMPL_AFTER_WR_SUPPORT_INTERLV_DIS |
		PCIE_AXI_POS_ORDER_SEGMENT_BUFFER_DONT_WAIT_FOR_P_WRITES,
		(tx_relaxed_ordering ?
		(PCIE_AXI_POS_ORDER_BYPASS_CMPL_AFTER_WR_FIX |
		PCIE_AXI_POS_ORDER_SEGMENT_BUFFER_DONT_WAIT_FOR_P_WRITES) : 0) |
		(rx_relaxed_ordering ?
		(PCIE_AXI_POS_ORDER_EP_CMPL_AFTER_WR_DIS |
		PCIE_AXI_POS_ORDER_EP_CMPL_AFTER_WR_SUPPORT_INTERLV_DIS) : 0));
}