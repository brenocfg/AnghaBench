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
typedef  int uint8_t ;
struct al_pcie_regs {TYPE_2__* port_regs; TYPE_1__* core_space; } ;
struct al_pcie_port {int max_lanes; int /*<<< orphan*/  port_id; struct al_pcie_regs* regs; } ;
struct al_pcie_link_params {int max_payload_size; int /*<<< orphan*/  max_speed; } ;
struct TYPE_4__ {int /*<<< orphan*/  port_link_ctrl; int /*<<< orphan*/  gen2_ctrl; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pcie_dev_ctrl_status; } ;

/* Variables and functions */
 int AL_PCIE_MPS_128 ; 
 int AL_PCIE_MPS_256 ; 
 int AL_PCIE_MPS_DEFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  PCIE_PORT_DEV_CTRL_STATUS_MPS_MASK ; 
 int PCIE_PORT_DEV_CTRL_STATUS_MPS_SHIFT ; 
 int /*<<< orphan*/  PCIE_PORT_GEN2_CTRL_NUM_OF_LANES_MASK ; 
 int PCIE_PORT_GEN2_CTRL_NUM_OF_LANES_SHIFT ; 
 int /*<<< orphan*/  PCIE_PORT_LINK_CTRL_LINK_CAPABLE_MASK ; 
 int PCIE_PORT_LINK_CTRL_LINK_CAPABLE_SHIFT ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  al_pcie_port_link_speed_ctrl_set (struct al_pcie_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
al_pcie_port_link_config(
	struct al_pcie_port *pcie_port,
	const struct al_pcie_link_params *link_params)
{
	struct al_pcie_regs *regs = pcie_port->regs;
	uint8_t max_lanes = pcie_port->max_lanes;

	if ((link_params->max_payload_size != AL_PCIE_MPS_DEFAULT)	&&
	    (link_params->max_payload_size != AL_PCIE_MPS_128)		&&
	    (link_params->max_payload_size != AL_PCIE_MPS_256)) {
		al_err("PCIe %d: unsupported Max Payload Size (%u)\n",
		       pcie_port->port_id, link_params->max_payload_size);
		return -EINVAL;
	}

	al_pcie_port_link_speed_ctrl_set(pcie_port, link_params->max_speed);

	/* Change Max Payload Size, if needed.
	 * The Max Payload Size is only valid for PF0.
	 */
	if (link_params->max_payload_size != AL_PCIE_MPS_DEFAULT)
		al_reg_write32_masked(regs->core_space[0].pcie_dev_ctrl_status,
				      PCIE_PORT_DEV_CTRL_STATUS_MPS_MASK,
				      link_params->max_payload_size <<
					PCIE_PORT_DEV_CTRL_STATUS_MPS_SHIFT);

	/** Snap from PCIe core spec:
	 * Link Mode Enable. Sets the number of lanes in the link that you want
	 * to connect to the link partner. When you have unused lanes in your
	 * system, then you must change the value in this register to reflect
	 * the number of lanes. You must also change the value in the
	 * "Predetermined Number of Lanes" field of the "Link Width and Speed
	 * Change Control Register".
	 * 000001: x1
	 * 000011: x2
	 * 000111: x4
	 * 001111: x8
	 * 011111: x16
	 * 111111: x32 (not supported)
	 */
	al_reg_write32_masked(&regs->port_regs->gen2_ctrl,
				PCIE_PORT_GEN2_CTRL_NUM_OF_LANES_MASK,
				max_lanes << PCIE_PORT_GEN2_CTRL_NUM_OF_LANES_SHIFT);
	al_reg_write32_masked(&regs->port_regs->port_link_ctrl,
				PCIE_PORT_LINK_CTRL_LINK_CAPABLE_MASK,
				(max_lanes + (max_lanes-1))
				<< PCIE_PORT_LINK_CTRL_LINK_CAPABLE_SHIFT);

	return 0;
}