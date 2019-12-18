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
typedef  int /*<<< orphan*/  uint32_t ;
struct al_pcie_regs {TYPE_1__* port_regs; } ;
struct al_pcie_port {struct al_pcie_regs* regs; } ;
struct al_pcie_latency_replay_timers {int /*<<< orphan*/  replay_timer_limit; int /*<<< orphan*/  round_trip_lat_limit; } ;
struct TYPE_2__ {int /*<<< orphan*/  ack_lat_rply_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_REG_FIELD_SET (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
al_pcie_port_lat_rply_timers_config(
	struct al_pcie_port *pcie_port,
	const struct al_pcie_latency_replay_timers  *lat_rply_timers)
{
	struct al_pcie_regs *regs = pcie_port->regs;
	uint32_t	reg = 0;

	AL_REG_FIELD_SET(reg, 0xFFFF, 0, lat_rply_timers->round_trip_lat_limit);
	AL_REG_FIELD_SET(reg, 0xFFFF0000, 16, lat_rply_timers->replay_timer_limit);

	al_reg_write32(&regs->port_regs->ack_lat_rply_timer, reg);
	return 0;
}