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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ata_timing {int udma; int setup; int act8b; int rec8b; int active; int recover; } ;
struct ata_port {int port_no; TYPE_1__* host; } ;
struct ata_device {int devno; int dma_mode; int pio_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_TIMING_8BIT ; 
 int XFER_UDMA_5 ; 
 int XFER_UDMA_6 ; 
 struct ata_device* ata_dev_pair (struct ata_device*) ; 
 scalar_t__ ata_timing_compute (struct ata_device*,int,struct ata_timing*,int,int) ; 
 int /*<<< orphan*/  ata_timing_merge (struct ata_timing*,struct ata_timing*,struct ata_timing*,int /*<<< orphan*/ ) ; 
 size_t clamp_val (int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timing_setup(struct ata_port *ap, struct ata_device *adev, int offset, int speed, int clock)
{
	static const unsigned char amd_cyc2udma[] = {
		6, 6, 5, 4, 0, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 7
	};

	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	struct ata_device *peer = ata_dev_pair(adev);
	int dn = ap->port_no * 2 + adev->devno;
	struct ata_timing at, apeer;
	int T, UT;
	const int amd_clock = 33333;	/* KHz. */
	u8 t;

	T = 1000000000 / amd_clock;
	UT = T;
	if (clock >= 2)
		UT = T / 2;

	if (ata_timing_compute(adev, speed, &at, T, UT) < 0) {
		dev_err(&pdev->dev, "unknown mode %d\n", speed);
		return;
	}

	if (peer) {
		/* This may be over conservative */
		if (peer->dma_mode) {
			ata_timing_compute(peer, peer->dma_mode, &apeer, T, UT);
			ata_timing_merge(&apeer, &at, &at, ATA_TIMING_8BIT);
		}
		ata_timing_compute(peer, peer->pio_mode, &apeer, T, UT);
		ata_timing_merge(&apeer, &at, &at, ATA_TIMING_8BIT);
	}

	if (speed == XFER_UDMA_5 && amd_clock <= 33333) at.udma = 1;
	if (speed == XFER_UDMA_6 && amd_clock <= 33333) at.udma = 15;

	/*
	 *	Now do the setup work
	 */

	/* Configure the address set up timing */
	pci_read_config_byte(pdev, offset + 0x0C, &t);
	t = (t & ~(3 << ((3 - dn) << 1))) | ((clamp_val(at.setup, 1, 4) - 1) << ((3 - dn) << 1));
	pci_write_config_byte(pdev, offset + 0x0C , t);

	/* Configure the 8bit I/O timing */
	pci_write_config_byte(pdev, offset + 0x0E + (1 - (dn >> 1)),
		((clamp_val(at.act8b, 1, 16) - 1) << 4) | (clamp_val(at.rec8b, 1, 16) - 1));

	/* Drive timing */
	pci_write_config_byte(pdev, offset + 0x08 + (3 - dn),
		((clamp_val(at.active, 1, 16) - 1) << 4) | (clamp_val(at.recover, 1, 16) - 1));

	switch (clock) {
		case 1:
		t = at.udma ? (0xc0 | (clamp_val(at.udma, 2, 5) - 2)) : 0x03;
		break;

		case 2:
		t = at.udma ? (0xc0 | amd_cyc2udma[clamp_val(at.udma, 2, 10)]) : 0x03;
		break;

		case 3:
		t = at.udma ? (0xc0 | amd_cyc2udma[clamp_val(at.udma, 1, 10)]) : 0x03;
		break;

		case 4:
		t = at.udma ? (0xc0 | amd_cyc2udma[clamp_val(at.udma, 1, 15)]) : 0x03;
		break;

		default:
			return;
	}

	/* UDMA timing */
	if (at.udma)
		pci_write_config_byte(pdev, offset + 0x10 + (3 - dn), t);
}