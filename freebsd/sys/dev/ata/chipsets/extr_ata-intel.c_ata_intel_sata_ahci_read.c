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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int u_char ;
struct ata_pci_controller {int /*<<< orphan*/  r_res2; } ;
struct ata_channel {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_INL (int /*<<< orphan*/ ,int) ; 
 int* ATA_INTEL_SMAP (struct ata_pci_controller*,struct ata_channel*) ; 
#define  ATA_SCONTROL 130 
#define  ATA_SERROR 129 
#define  ATA_SSTATUS 128 
 int EINVAL ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_intel_sata_ahci_read(device_t dev, int port, int reg, u_int32_t *result)
{
	struct ata_pci_controller *ctlr;
	struct ata_channel *ch;
	device_t parent;
	u_char *smap;
	int offset;

	parent = device_get_parent(dev);
	ctlr = device_get_softc(parent);
	ch = device_get_softc(dev);
	port = (port == 1) ? 1 : 0;
	smap = ATA_INTEL_SMAP(ctlr, ch);
	offset = 0x100 + smap[port] * 0x80;
	switch (reg) {
	case ATA_SSTATUS:
	    reg = 0x28;
	    break;
	case ATA_SCONTROL:
	    reg = 0x2c;
	    break;
	case ATA_SERROR:
	    reg = 0x30;
	    break;
	default:
	    return (EINVAL);
	}
	*result = ATA_INL(ctlr->r_res2, offset + reg);
	return (0);
}