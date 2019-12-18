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
struct al_pcie_port {TYPE_2__* regs; } ;
typedef  scalar_t__ al_bool ;
struct TYPE_4__ {TYPE_1__* port_regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  rd_only_wr_en; } ;

/* Variables and functions */
 scalar_t__ AL_FALSE ; 
 scalar_t__ AL_TRUE ; 
 int /*<<< orphan*/  al_local_data_memory_barrier () ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
al_pcie_port_wr_to_ro_set(struct al_pcie_port *pcie_port, al_bool enable)
{
	/* when disabling writes to RO, make sure any previous writes to
	 * config space were committed
	 */
	if (enable == AL_FALSE)
		al_local_data_memory_barrier();

	al_reg_write32(&pcie_port->regs->port_regs->rd_only_wr_en,
		       (enable == AL_TRUE) ? 1 : 0);

	/* when enabling writes to RO, make sure it is committed before trying
	 * to write to RO config space
	 */
	if (enable == AL_TRUE)
		al_local_data_memory_barrier();
}