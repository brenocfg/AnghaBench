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
struct al_pcie_port {int /*<<< orphan*/  port_id; } ;
struct al_pcie_pf_config_params {int /*<<< orphan*/  pf_num; struct al_pcie_port* pcie_port; } ;
typedef  struct al_pcie_pf {int /*<<< orphan*/  pf_num; struct al_pcie_port* pcie_port; } const al_pcie_pf ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  al_assert (struct al_pcie_pf_config_params const*) ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_pcie_port_is_enabled (struct al_pcie_port*) ; 
 int al_pcie_port_pf_params_config (struct al_pcie_pf_config_params const*,struct al_pcie_pf_config_params const*) ; 

int
al_pcie_pf_config(
	struct al_pcie_pf *pcie_pf,
	const struct al_pcie_pf_config_params *params)
{
	struct al_pcie_port *pcie_port;
	int status = 0;

	al_assert(pcie_pf);
	al_assert(params);

	pcie_port = pcie_pf->pcie_port;

	if (!al_pcie_port_is_enabled(pcie_port)) {
		al_err("PCIe %d: port not enabled, cannot configure port\n", pcie_port->port_id);
		return -EINVAL;
	}

	al_dbg("PCIe %d: pf %d config\n", pcie_port->port_id, pcie_pf->pf_num);

	if (params)
		status = al_pcie_port_pf_params_config(pcie_pf, params);
	if (status)
		goto done;

done:
	al_dbg("PCIe %d: pf %d config %s\n",
		pcie_port->port_id, pcie_pf->pf_num, status ? "failed" : "done");

	return status;
}