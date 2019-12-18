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
struct ata_pci_controller {int /*<<< orphan*/  setmode; int /*<<< orphan*/  ch_attach; TYPE_1__* chip; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int cfg1; } ;

/* Variables and functions */
 int AMD_BUG ; 
 int ENXIO ; 
 int /*<<< orphan*/  ata_amd_ch_attach ; 
 int /*<<< orphan*/  ata_amd_setmode ; 
 int /*<<< orphan*/  ata_generic_intr ; 
 scalar_t__ ata_setup_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
ata_amd_chipinit(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(dev);

    if (ata_setup_interrupt(dev, ata_generic_intr))
	return ENXIO;

    /* disable/set prefetch, postwrite */
    if (ctlr->chip->cfg1 & AMD_BUG)
	pci_write_config(dev, 0x41, pci_read_config(dev, 0x41, 1) & 0x0f, 1);
    else
	pci_write_config(dev, 0x41, pci_read_config(dev, 0x41, 1) | 0xf0, 1);

    ctlr->ch_attach = ata_amd_ch_attach;
    ctlr->setmode = ata_amd_setmode;
    return 0;
}