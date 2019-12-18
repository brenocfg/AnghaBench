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
typedef  int u32 ;
struct via_isa_bridge {int flags; scalar_t__ udma_mask; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ ATA_UDMA4 ; 
 int VIA_BAD_CLK66 ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  via_config_fifo (struct pci_dev*,int) ; 

__attribute__((used)) static void via_fixup(struct pci_dev *pdev, const struct via_isa_bridge *config)
{
	u32 timing;

	/* Initialise the FIFO for the enabled channels. */
	via_config_fifo(pdev, config->flags);

	if (config->udma_mask == ATA_UDMA4) {
		/* The 66 MHz devices require we enable the clock */
		pci_read_config_dword(pdev, 0x50, &timing);
		timing |= 0x80008;
		pci_write_config_dword(pdev, 0x50, timing);
	}
	if (config->flags & VIA_BAD_CLK66) {
		/* Disable the 66MHz clock on problem devices */
		pci_read_config_dword(pdev, 0x50, &timing);
		timing &= ~0x80008;
		pci_write_config_dword(pdev, 0x50, timing);
	}
}