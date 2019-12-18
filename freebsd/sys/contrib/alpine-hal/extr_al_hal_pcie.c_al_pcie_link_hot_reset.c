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
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * events_gen; } ;
struct TYPE_4__ {TYPE_1__ global_ctrl; } ;
struct al_pcie_regs {TYPE_2__ app; } ;
struct al_pcie_port {int /*<<< orphan*/  port_id; struct al_pcie_regs* regs; } ;
typedef  enum al_pcie_operating_mode { ____Placeholder_al_pcie_operating_mode } al_pcie_operating_mode ;
typedef  int al_bool ;

/* Variables and functions */
 int AL_PCIE_OPERATING_MODE_RC ; 
 int EINVAL ; 
 int PCIE_W_GLOBAL_CTRL_EVENTS_GEN_APP_RST_INIT ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_pcie_is_link_started (struct al_pcie_port*) ; 
 int al_pcie_operating_mode_get (struct al_pcie_port*) ; 
 int al_reg_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ ,int,int) ; 

int
al_pcie_link_hot_reset(struct al_pcie_port *pcie_port, al_bool enable)
{
	struct al_pcie_regs *regs = pcie_port->regs;
	uint32_t events_gen;
	al_bool app_reset_state;
	enum al_pcie_operating_mode op_mode = al_pcie_operating_mode_get(pcie_port);

	if (op_mode != AL_PCIE_OPERATING_MODE_RC) {
		al_err("PCIe %d: hot-reset is applicable only for RC mode\n", pcie_port->port_id);
		return -EINVAL;
	}

	if (!al_pcie_is_link_started(pcie_port)) {
		al_err("PCIe %d: link not started, cannot trigger hot-reset\n", pcie_port->port_id);
		return -EINVAL;
	}

	events_gen = al_reg_read32(regs->app.global_ctrl.events_gen[0]);
	app_reset_state = events_gen & PCIE_W_GLOBAL_CTRL_EVENTS_GEN_APP_RST_INIT;

	if (enable && app_reset_state) {
		al_err("PCIe %d: link is already in hot-reset state\n", pcie_port->port_id);
		return -EINVAL;
	} else if ((!enable) && (!(app_reset_state))) {
		al_err("PCIe %d: link is already in non-hot-reset state\n", pcie_port->port_id);
		return -EINVAL;
	} else {
		al_dbg("PCIe %d: %s hot-reset\n", pcie_port->port_id,
			(enable ? "enabling" : "disabling"));
		/* hot-reset functionality is implemented only for function 0 */
		al_reg_write32_masked(regs->app.global_ctrl.events_gen[0],
			PCIE_W_GLOBAL_CTRL_EVENTS_GEN_APP_RST_INIT,
			(enable ? PCIE_W_GLOBAL_CTRL_EVENTS_GEN_APP_RST_INIT
				: ~PCIE_W_GLOBAL_CTRL_EVENTS_GEN_APP_RST_INIT));
		return 0;
	}
}