#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct TYPE_7__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct TYPE_6__ {int /*<<< orphan*/  start; int /*<<< orphan*/  end; } ;
struct TYPE_5__ {int /*<<< orphan*/  start; int /*<<< orphan*/  end; } ;
struct oxnas_pcie {scalar_t__ base; int /*<<< orphan*/  pcie_ctrl_offset; int /*<<< orphan*/  sys_ctrl; TYPE_4__ cfg; scalar_t__ outbound_offset; TYPE_3__ io; TYPE_2__ pre_mem; TYPE_1__ non_mem; scalar_t__ inbound; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_IN_ADDR_TRANS ; 
 scalar_t__ IB_ADDR_XLATE_ENABLE ; 
 scalar_t__ PCIE_IN0_MEM_ADDR ; 
 scalar_t__ PCIE_IN0_MEM_LIMIT ; 
 scalar_t__ PCIE_IN1_MEM_ADDR ; 
 scalar_t__ PCIE_IN1_MEM_LIMIT ; 
 scalar_t__ PCIE_IN_CFG0_ADDR ; 
 scalar_t__ PCIE_IN_CFG0_LIMIT ; 
 scalar_t__ PCIE_IN_IO_ADDR ; 
 scalar_t__ PCIE_IN_IO_LIMIT ; 
 int /*<<< orphan*/  PCIE_OBTRANS ; 
 scalar_t__ PCIE_POM0_MEM_ADDR ; 
 scalar_t__ PCIE_POM1_MEM_ADDR ; 
 scalar_t__ PCI_CONFIG_COMMAND_STATUS ; 
 int /*<<< orphan*/  oxnas_register_clear_mask (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void oxnas_pcie_setup_hw(struct oxnas_pcie *pcie)
{
	/* We won't have any inbound address translation. This allows PCI
	 * devices to access anywhere in the AHB address map. Might be regarded
	 * as a bit dangerous, but let's get things working before we worry
	 * about that
	 */
	oxnas_register_clear_mask(pcie->inbound + IB_ADDR_XLATE_ENABLE,
				  ENABLE_IN_ADDR_TRANS);
	wmb();

	/*
	 * Program outbound translation windows
	 *
	 * Outbound window is what is referred to as "PCI client" region in HRM
	 *
	 * Could use the larger alternative address space to get >>64M regions
	 * for graphics cards etc., but will not bother at this point.
	 *
	 * IP bug means that AMBA window size must be a power of 2
	 *
	 * Set mem0 window for first 16MB of outbound window non-prefetchable
	 * Set mem1 window for second 16MB of outbound window prefetchable
	 * Set io window for next 16MB of outbound window
	 * Set cfg0 for final 1MB of outbound window
	 *
	 * Ignore mem1, cfg1 and msg windows for now as no obvious use cases for
	 * 820 that would need them
	 *
	 * Probably ideally want no offset between mem0 window start as seen by
	 * ARM and as seen on PCI bus and get Linux to assign memory regions to
	 * PCI devices using the same "PCI client" region start address as seen
	 * by ARM
	 */

	/* Set PCIeA mem0 region to be 1st 16MB of the 64MB PCIeA window */
	regmap_write(pcie->sys_ctrl, pcie->outbound_offset + PCIE_IN0_MEM_ADDR, pcie->non_mem.start);
	regmap_write(pcie->sys_ctrl, pcie->outbound_offset + PCIE_IN0_MEM_LIMIT, pcie->non_mem.end);
	regmap_write(pcie->sys_ctrl, pcie->outbound_offset + PCIE_POM0_MEM_ADDR, pcie->non_mem.start);

	/* Set PCIeA mem1 region to be 2nd 16MB of the 64MB PCIeA window */
	regmap_write(pcie->sys_ctrl, pcie->outbound_offset + PCIE_IN1_MEM_ADDR, pcie->pre_mem.start);
	regmap_write(pcie->sys_ctrl, pcie->outbound_offset + PCIE_IN1_MEM_LIMIT, pcie->pre_mem.end);
	regmap_write(pcie->sys_ctrl, pcie->outbound_offset + PCIE_POM1_MEM_ADDR, pcie->pre_mem.start);

	/* Set PCIeA io to be third 16M region of the 64MB PCIeA window*/
	regmap_write(pcie->sys_ctrl, pcie->outbound_offset + PCIE_IN_IO_ADDR, pcie->io.start);
	regmap_write(pcie->sys_ctrl, pcie->outbound_offset + PCIE_IN_IO_LIMIT, pcie->io.end);


	/* Set PCIeA cgf0 to be last 16M region of the 64MB PCIeA window*/
	regmap_write(pcie->sys_ctrl, pcie->outbound_offset + PCIE_IN_CFG0_ADDR, pcie->cfg.start);
	regmap_write(pcie->sys_ctrl, pcie->outbound_offset + PCIE_IN_CFG0_LIMIT, pcie->cfg.end);
	wmb();

	/* Enable outbound address translation */
	regmap_write_bits(pcie->sys_ctrl, pcie->pcie_ctrl_offset, PCIE_OBTRANS, PCIE_OBTRANS);
	wmb();

	/*
	 * Program PCIe command register for core to:
	 *  enable memory space
	 *  enable bus master
	 *  enable io
	 */
	writel_relaxed(7, pcie->base + PCI_CONFIG_COMMAND_STATUS);
	/* which is which */
	wmb();
}