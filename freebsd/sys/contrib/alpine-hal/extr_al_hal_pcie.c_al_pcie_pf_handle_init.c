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
struct al_pcie_port {unsigned int max_num_of_pfs; int /*<<< orphan*/  regs; int /*<<< orphan*/  rev_id; int /*<<< orphan*/  port_id; } ;
struct al_pcie_pf {unsigned int pf_num; struct al_pcie_port* pcie_port; } ;
typedef  enum al_pcie_operating_mode { ____Placeholder_al_pcie_operating_mode } al_pcie_operating_mode ;

/* Variables and functions */
 int AL_PCIE_OPERATING_MODE_EP ; 
 int EINVAL ; 
 int /*<<< orphan*/  al_assert (int) ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ,int) ; 
 int al_pcie_operating_mode_get (struct al_pcie_port*) ; 

int
al_pcie_pf_handle_init(
	struct al_pcie_pf *pcie_pf,
	struct al_pcie_port *pcie_port,
	unsigned int pf_num)
{
	enum al_pcie_operating_mode op_mode = al_pcie_operating_mode_get(pcie_port);
	al_assert(pf_num < pcie_port->max_num_of_pfs);

	if (op_mode != AL_PCIE_OPERATING_MODE_EP) {
		al_err("PCIe %d: can't init PF handle with operating mode [%d]\n",
			pcie_port->port_id, op_mode);
		return -EINVAL;
	}

	pcie_pf->pf_num = pf_num;
	pcie_pf->pcie_port = pcie_port;

	al_dbg("PCIe %d: pf handle initialized. pf number: %d, rev_id %d, regs %p\n",
	       pcie_port->port_id, pcie_pf->pf_num, pcie_port->rev_id,
	       pcie_port->regs);
	return 0;
}