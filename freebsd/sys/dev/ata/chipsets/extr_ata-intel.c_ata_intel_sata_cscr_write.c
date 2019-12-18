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
typedef  int u_int32_t ;
typedef  int u_char ;
struct ata_pci_controller {int dummy; } ;
struct ata_channel {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_INTEL_LOCK (struct ata_pci_controller*) ; 
 int* ATA_INTEL_SMAP (struct ata_pci_controller*,struct ata_channel*) ; 
 int /*<<< orphan*/  ATA_INTEL_UNLOCK (struct ata_pci_controller*) ; 
#define  ATA_SCONTROL 130 
#define  ATA_SERROR 129 
#define  ATA_SSTATUS 128 
 int EINVAL ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
ata_intel_sata_cscr_write(device_t dev, int port, int reg, u_int32_t value)
{
	struct ata_pci_controller *ctlr;
	struct ata_channel *ch;
	device_t parent;
	u_char *smap;

	parent = device_get_parent(dev);
	ctlr = device_get_softc(parent);
	ch = device_get_softc(dev);
	smap = ATA_INTEL_SMAP(ctlr, ch);
	port = (port == 1) ? 1 : 0;
	switch (reg) {
	case ATA_SSTATUS:
	    reg = 0;
	    break;
	case ATA_SERROR:
	    reg = 1;
	    break;
	case ATA_SCONTROL:
	    reg = 2;
	    break;
	default:
	    return (EINVAL);
	}
	ATA_INTEL_LOCK(ctlr);
	pci_write_config(parent, 0xa0,
	    0x50 + smap[port] * 0x10 + reg * 4, 4);
	pci_write_config(parent, 0xa4, value, 4);
	ATA_INTEL_UNLOCK(ctlr);
	return (0);
}