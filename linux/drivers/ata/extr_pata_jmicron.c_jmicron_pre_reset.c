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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct ata_port {int port_no; void* cbl; TYPE_1__* host; } ;
struct ata_link {struct ata_port* ap; } ;
typedef  int port_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* ATA_CBL_PATA40 ; 
 void* ATA_CBL_PATA80 ; 
 void* ATA_CBL_SATA ; 
 int ENOENT ; 
#define  PORT_PATA0 130 
#define  PORT_PATA1 129 
#define  PORT_SATA 128 
 int ata_sff_prereset (struct ata_link*,unsigned long) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jmicron_pre_reset(struct ata_link *link, unsigned long deadline)
{
	struct ata_port *ap = link->ap;
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 control;
	u32 control5;
	int port_mask = 1<< (4 * ap->port_no);
	int port = ap->port_no;
	port_type port_map[2];

	/* Check if our port is enabled */
	pci_read_config_dword(pdev, 0x40, &control);
	if ((control & port_mask) == 0)
		return -ENOENT;

	/* There are two basic mappings. One has the two SATA ports merged
	   as master/slave and the secondary as PATA, the other has only the
	   SATA port mapped */
	if (control & (1 << 23)) {
		port_map[0] = PORT_SATA;
		port_map[1] = PORT_PATA0;
	} else {
		port_map[0] = PORT_SATA;
		port_map[1] = PORT_SATA;
	}

	/* The 365/366 may have this bit set to map the second PATA port
	   as the internal primary channel */
	pci_read_config_dword(pdev, 0x80, &control5);
	if (control5 & (1<<24))
		port_map[0] = PORT_PATA1;

	/* The two ports may then be logically swapped by the firmware */
	if (control & (1 << 22))
		port = port ^ 1;

	/*
	 *	Now we know which physical port we are talking about we can
	 *	actually do our cable checking etc. Thankfully we don't need
	 *	to do the plumbing for other cases.
	 */
	switch (port_map[port]) {
	case PORT_PATA0:
		if ((control & (1 << 5)) == 0)
			return -ENOENT;
		if (control & (1 << 3))	/* 40/80 pin primary */
			ap->cbl = ATA_CBL_PATA40;
		else
			ap->cbl = ATA_CBL_PATA80;
		break;
	case PORT_PATA1:
		/* Bit 21 is set if the port is enabled */
		if ((control5 & (1 << 21)) == 0)
			return -ENOENT;
		if (control5 & (1 << 19))	/* 40/80 pin secondary */
			ap->cbl = ATA_CBL_PATA40;
		else
			ap->cbl = ATA_CBL_PATA80;
		break;
	case PORT_SATA:
		ap->cbl = ATA_CBL_SATA;
		break;
	}
	return ata_sff_prereset(link, deadline);
}