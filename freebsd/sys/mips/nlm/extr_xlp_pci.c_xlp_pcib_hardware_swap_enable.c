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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ BRIDGE_PCIEIO_BASE0 ; 
 scalar_t__ BRIDGE_PCIEIO_LIMIT0 ; 
 scalar_t__ BRIDGE_PCIEMEM_BASE0 ; 
 scalar_t__ BRIDGE_PCIEMEM_LIMIT0 ; 
 int /*<<< orphan*/  PCIE_BYTE_SWAP_IO_BASE ; 
 int /*<<< orphan*/  PCIE_BYTE_SWAP_IO_LIM ; 
 int /*<<< orphan*/  PCIE_BYTE_SWAP_MEM_BASE ; 
 int /*<<< orphan*/  PCIE_BYTE_SWAP_MEM_LIM ; 
 int XLP_IO_PCIE_OFFSET (int,int) ; 
 int /*<<< orphan*/  nlm_dev_exists (int) ; 
 int /*<<< orphan*/  nlm_get_bridge_regbase (int) ; 
 int /*<<< orphan*/  nlm_pcicfg_base (int) ; 
 int nlm_read_bridge_reg (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nlm_write_pci_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
xlp_pcib_hardware_swap_enable(int node, int link)
{
#if BYTE_ORDER == BIG_ENDIAN
	uint64_t bbase, linkpcibase;
	uint32_t bar;
	int pcieoffset;

	pcieoffset = XLP_IO_PCIE_OFFSET(node, link);
	if (!nlm_dev_exists(pcieoffset))
		return;

	bbase = nlm_get_bridge_regbase(node);
	linkpcibase = nlm_pcicfg_base(pcieoffset);
	bar = nlm_read_bridge_reg(bbase, BRIDGE_PCIEMEM_BASE0 + link);
	nlm_write_pci_reg(linkpcibase, PCIE_BYTE_SWAP_MEM_BASE, bar);

	bar = nlm_read_bridge_reg(bbase, BRIDGE_PCIEMEM_LIMIT0 + link);
	nlm_write_pci_reg(linkpcibase, PCIE_BYTE_SWAP_MEM_LIM, bar | 0xFFF);

	bar = nlm_read_bridge_reg(bbase, BRIDGE_PCIEIO_BASE0 + link);
	nlm_write_pci_reg(linkpcibase, PCIE_BYTE_SWAP_IO_BASE, bar);

	bar = nlm_read_bridge_reg(bbase, BRIDGE_PCIEIO_LIMIT0 + link);
	nlm_write_pci_reg(linkpcibase, PCIE_BYTE_SWAP_IO_LIM, bar | 0xFFF);
#endif
}