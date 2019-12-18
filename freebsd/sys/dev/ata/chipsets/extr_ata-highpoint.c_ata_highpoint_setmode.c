#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int member_0; int member_1; int member_2; int member_3; } ;
typedef  TYPE_2__ uint32_t ;
struct ata_pci_controller {TYPE_1__* chip; } ;
struct ata_channel {int unit; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {size_t cfg1; int /*<<< orphan*/  max_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_UDMA5 ; 
 int ata_highpoint_check_80pin (int /*<<< orphan*/ ,int) ; 
 size_t ata_mode2idx (int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,TYPE_2__ const,int) ; 

__attribute__((used)) static int
ata_highpoint_setmode(device_t dev, int target, int mode)
{
	device_t parent = device_get_parent(dev);
	struct ata_pci_controller *ctlr = device_get_softc(parent);
	struct ata_channel *ch = device_get_softc(dev);
	int devno = (ch->unit << 1) + target;
	static const uint32_t timings33[][4] = {
	/*    HPT366      HPT370      HPT372      HPT374           mode */
	{ 0x40d0a7aa, 0x06914e57, 0x0d029d5e, 0x0ac1f48a },     /* PIO 0 */
	{ 0x40d0a7a3, 0x06914e43, 0x0d029d26, 0x0ac1f465 },     /* PIO 1 */
	{ 0x40d0a753, 0x06514e33, 0x0c829ca6, 0x0a81f454 },     /* PIO 2 */
	{ 0x40c8a742, 0x06514e22, 0x0c829c84, 0x0a81f443 },     /* PIO 3 */
	{ 0x40c8a731, 0x06514e21, 0x0c829c62, 0x0a81f442 },     /* PIO 4 */
	{ 0x20c8a797, 0x26514e97, 0x2c82922e, 0x228082ea },     /* MWDMA 0 */
	{ 0x20c8a732, 0x26514e33, 0x2c829266, 0x22808254 },     /* MWDMA 1 */
	{ 0x20c8a731, 0x26514e21, 0x2c829262, 0x22808242 },     /* MWDMA 2 */
	{ 0x10c8a731, 0x16514e31, 0x1c829c62, 0x121882ea },     /* UDMA 0 */
	{ 0x10cba731, 0x164d4e31, 0x1c9a9c62, 0x12148254 },     /* UDMA 1 */
	{ 0x10caa731, 0x16494e31, 0x1c929c62, 0x120c8242 },     /* UDMA 2 */
	{ 0x10cfa731, 0x166d4e31, 0x1c8e9c62, 0x128c8242 },     /* UDMA 3 */
	{ 0x10c9a731, 0x16454e31, 0x1c8a9c62, 0x12ac8242 },     /* UDMA 4 */
	{ 0,          0x16454e31, 0x1c8a9c62, 0x12848242 },     /* UDMA 5 */
	{ 0,          0,          0x1c869c62, 0x12808242 }      /* UDMA 6 */
	};

	mode = min(mode, ctlr->chip->max_dma);
	mode = ata_highpoint_check_80pin(dev, mode);
	/*
	 * most if not all HPT chips cant really handle that the device is
	 * running at ATA_UDMA6/ATA133 speed, so we cheat at set the device to
         * a max of ATA_UDMA5/ATA100 to guard against suboptimal performance
	 */
	mode = min(mode, ATA_UDMA5);
	pci_write_config(parent, 0x40 + (devno << 2),
			 timings33[ata_mode2idx(mode)][ctlr->chip->cfg1], 4);
	return (mode);
}