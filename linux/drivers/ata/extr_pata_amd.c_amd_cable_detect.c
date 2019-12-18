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
typedef  int const u8 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct ata_port {size_t port_no; TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ATA_CBL_PATA40 ; 
 int ATA_CBL_PATA80 ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int const*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amd_cable_detect(struct ata_port *ap)
{
	static const u32 bitmask[2] = {0x03, 0x0C};
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 ata66;

	pci_read_config_byte(pdev, 0x42, &ata66);
	if (ata66 & bitmask[ap->port_no])
		return ATA_CBL_PATA80;
	return ATA_CBL_PATA40;
}