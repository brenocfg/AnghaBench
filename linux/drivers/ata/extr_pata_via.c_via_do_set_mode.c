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
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct ata_timing {scalar_t__ udma; scalar_t__ recover; scalar_t__ active; scalar_t__ rec8b; scalar_t__ act8b; scalar_t__ setup; } ;
struct ata_port {int port_no; TYPE_1__* host; } ;
struct ata_device {int devno; int pio_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_TIMING_8BIT ; 
#define  ATA_UDMA2 131 
#define  ATA_UDMA4 130 
#define  ATA_UDMA5 129 
#define  ATA_UDMA6 128 
 struct ata_device* ata_dev_pair (struct ata_device*) ; 
 int /*<<< orphan*/  ata_timing_compute (struct ata_device*,int,struct ata_timing*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ata_timing_merge (struct ata_timing*,struct ata_timing*,struct ata_timing*,int /*<<< orphan*/ ) ; 
 int clamp_val (scalar_t__,int,int) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void via_do_set_mode(struct ata_port *ap, struct ata_device *adev,
			    int mode, int set_ast, int udma_type)
{
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	struct ata_device *peer = ata_dev_pair(adev);
	struct ata_timing t, p;
	static int via_clock = 33333;	/* Bus clock in kHZ */
	unsigned long T =  1000000000 / via_clock;
	unsigned long UT = T;
	int ut;
	int offset = 3 - (2*ap->port_no) - adev->devno;

	switch (udma_type) {
	case ATA_UDMA4:
		UT = T / 2; break;
	case ATA_UDMA5:
		UT = T / 3; break;
	case ATA_UDMA6:
		UT = T / 4; break;
	}

	/* Calculate the timing values we require */
	ata_timing_compute(adev, mode, &t, T, UT);

	/* We share 8bit timing so we must merge the constraints */
	if (peer) {
		if (peer->pio_mode) {
			ata_timing_compute(peer, peer->pio_mode, &p, T, UT);
			ata_timing_merge(&p, &t, &t, ATA_TIMING_8BIT);
		}
	}

	/* Address setup is programmable but breaks on UDMA133 setups */
	if (set_ast) {
		u8 setup;	/* 2 bits per drive */
		int shift = 2 * offset;

		pci_read_config_byte(pdev, 0x4C, &setup);
		setup &= ~(3 << shift);
		setup |= (clamp_val(t.setup, 1, 4) - 1) << shift;
		pci_write_config_byte(pdev, 0x4C, setup);
	}

	/* Load the PIO mode bits */
	pci_write_config_byte(pdev, 0x4F - ap->port_no,
		((clamp_val(t.act8b, 1, 16) - 1) << 4) | (clamp_val(t.rec8b, 1, 16) - 1));
	pci_write_config_byte(pdev, 0x48 + offset,
		((clamp_val(t.active, 1, 16) - 1) << 4) | (clamp_val(t.recover, 1, 16) - 1));

	/* Load the UDMA bits according to type */
	switch (udma_type) {
	case ATA_UDMA2:
	default:
		ut = t.udma ? (0xe0 | (clamp_val(t.udma, 2, 5) - 2)) : 0x03;
		break;
	case ATA_UDMA4:
		ut = t.udma ? (0xe8 | (clamp_val(t.udma, 2, 9) - 2)) : 0x0f;
		break;
	case ATA_UDMA5:
		ut = t.udma ? (0xe0 | (clamp_val(t.udma, 2, 9) - 2)) : 0x07;
		break;
	case ATA_UDMA6:
		ut = t.udma ? (0xe0 | (clamp_val(t.udma, 2, 9) - 2)) : 0x07;
		break;
	}

	/* Set UDMA unless device is not UDMA capable */
	if (udma_type) {
		u8 udma_etc;

		pci_read_config_byte(pdev, 0x50 + offset, &udma_etc);

		/* clear transfer mode bit */
		udma_etc &= ~0x20;

		if (t.udma) {
			/* preserve 80-wire cable detection bit */
			udma_etc &= 0x10;
			udma_etc |= ut;
		}

		pci_write_config_byte(pdev, 0x50 + offset, udma_etc);
	}
}