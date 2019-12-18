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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {TYPE_1__* debug; } ;
struct al_pcie_regs {TYPE_2__ app; } ;
struct al_pcie_port {int /*<<< orphan*/  port_id; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  al_bool ;
struct TYPE_3__ {int /*<<< orphan*/  info_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_FALSE ; 
 scalar_t__ AL_PCIE_LTSSM_STATE_L0 ; 
 scalar_t__ AL_PCIE_LTSSM_STATE_L0S ; 
 scalar_t__ AL_REG_FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AL_TRUE ; 
 int /*<<< orphan*/  PCIE_W_DEBUG_INFO_0_LTSSM_STATE_MASK ; 
 int /*<<< orphan*/  PCIE_W_DEBUG_INFO_0_LTSSM_STATE_SHIFT ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  al_reg_read32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static al_bool
al_pcie_check_link(
	struct al_pcie_port *pcie_port,
	uint8_t *ltssm_ret)
{
	struct al_pcie_regs *regs = (struct al_pcie_regs *)pcie_port->regs;
	uint32_t info_0;
	uint8_t	ltssm_state;

	info_0 = al_reg_read32(&regs->app.debug->info_0);

	ltssm_state = AL_REG_FIELD_GET(info_0,
			PCIE_W_DEBUG_INFO_0_LTSSM_STATE_MASK,
			PCIE_W_DEBUG_INFO_0_LTSSM_STATE_SHIFT);

	al_dbg("PCIe %d: Port Debug 0: 0x%08x. LTSSM state :0x%x\n",
		pcie_port->port_id, info_0, ltssm_state);

	if (ltssm_ret)
		*ltssm_ret = ltssm_state;

	if ((ltssm_state == AL_PCIE_LTSSM_STATE_L0) ||
			(ltssm_state == AL_PCIE_LTSSM_STATE_L0S))
		return AL_TRUE;
	return AL_FALSE;
}