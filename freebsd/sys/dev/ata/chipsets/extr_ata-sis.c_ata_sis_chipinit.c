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
struct ata_pci_controller {int /*<<< orphan*/  setmode; int /*<<< orphan*/  getrev; int /*<<< orphan*/  reset; int /*<<< orphan*/  ch_detach; int /*<<< orphan*/  ch_attach; int /*<<< orphan*/  r_rid2; int /*<<< orphan*/  r_type2; int /*<<< orphan*/  r_res2; TYPE_1__* chip; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int cfg1; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
#define  SIS_100NEW 134 
#define  SIS_100OLD 133 
#define  SIS_133NEW 132 
#define  SIS_133OLD 131 
#define  SIS_33 130 
#define  SIS_66 129 
#define  SIS_SATA 128 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  ata_generic_intr ; 
 int /*<<< orphan*/  ata_pci_ch_detach ; 
 int /*<<< orphan*/  ata_sata_getrev ; 
 int /*<<< orphan*/  ata_sata_setmode ; 
 scalar_t__ ata_setup_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_sis_ch_attach ; 
 int /*<<< orphan*/  ata_sis_reset ; 
 int /*<<< orphan*/  ata_sis_setmode ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
ata_sis_chipinit(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(dev);

    if (ata_setup_interrupt(dev, ata_generic_intr))
	return ENXIO;
    
    switch (ctlr->chip->cfg1) {
    case SIS_33:
	break;
    case SIS_66:
    case SIS_100OLD:
	pci_write_config(dev, 0x52, pci_read_config(dev, 0x52, 1) & ~0x04, 1);
	break;
    case SIS_100NEW:
    case SIS_133OLD:
	pci_write_config(dev, 0x49, pci_read_config(dev, 0x49, 1) & ~0x01, 1);
	break;
    case SIS_133NEW:
	pci_write_config(dev, 0x50, pci_read_config(dev, 0x50, 2) | 0x0008, 2);
	pci_write_config(dev, 0x52, pci_read_config(dev, 0x52, 2) | 0x0008, 2);
	break;
    case SIS_SATA:
	ctlr->r_type2 = SYS_RES_IOPORT;
	ctlr->r_rid2 = PCIR_BAR(5);
	if ((ctlr->r_res2 = bus_alloc_resource_any(dev, ctlr->r_type2,
						   &ctlr->r_rid2, RF_ACTIVE))) {
	    ctlr->ch_attach = ata_sis_ch_attach;
	    ctlr->ch_detach = ata_pci_ch_detach;
	    ctlr->reset = ata_sis_reset;
	}
	ctlr->setmode = ata_sata_setmode;
	ctlr->getrev = ata_sata_getrev;
	return 0;
    default:
	return ENXIO;
    }
    ctlr->setmode = ata_sis_setmode;
    return 0;
}