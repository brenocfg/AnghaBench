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
typedef  int u_int8_t ;
struct ata_pci_controller {TYPE_1__* chip; } ;
struct ata_channel {scalar_t__ unit; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ cfg1; } ;

/* Variables and functions */
 int ATA_UDMA2 ; 
 scalar_t__ HPT_374 ; 
 scalar_t__ ata_dma_check_80pin ; 
 int /*<<< orphan*/  ata_print_cable (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_get_function (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
ata_highpoint_check_80pin(device_t dev, int mode)
{
    device_t parent = device_get_parent(dev);
    struct ata_pci_controller *ctlr = device_get_softc(parent);
    struct ata_channel *ch = device_get_softc(dev);
    u_int8_t reg, val, res;

    if (ctlr->chip->cfg1 == HPT_374 && pci_get_function(parent) == 1) {
	reg = ch->unit ? 0x57 : 0x53;
	val = pci_read_config(parent, reg, 1);
	pci_write_config(parent, reg, val | 0x80, 1);
    }
    else {
	reg = 0x5b;
	val = pci_read_config(parent, reg, 1);
	pci_write_config(parent, reg, val & 0xfe, 1);
    }
    res = pci_read_config(parent, 0x5a, 1) & (ch->unit ? 0x1:0x2);
    pci_write_config(parent, reg, val, 1);

    if (ata_dma_check_80pin && mode > ATA_UDMA2 && res) {
	ata_print_cable(dev, "controller");
	mode = ATA_UDMA2;
    }
    return mode;
}