#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct ata_pci_controller {TYPE_3__* chip; int /*<<< orphan*/  setmode; scalar_t__ r_res2; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; int /*<<< orphan*/ * pm_write; int /*<<< orphan*/  pm_read; } ;
struct ata_channel {int flags; int unit; TYPE_2__ hw; TYPE_1__* r_io; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {scalar_t__ max_dma; int cfg1; scalar_t__ chipid; } ;
struct TYPE_4__ {int offset; scalar_t__ res; } ;

/* Variables and functions */
 int ATA_ALWAYS_DMASTAT ; 
 int ATA_CHECKS_CABLE ; 
 size_t ATA_IDX_ADDR ; 
 size_t ATA_IDX_DATA ; 
 int* ATA_INTEL_SMAP (struct ata_pci_controller*,struct ata_channel*) ; 
 scalar_t__ ATA_ISCH ; 
 int ATA_NO_SLAVE ; 
 int ATA_PERIODIC_POLL ; 
 scalar_t__ ATA_SA150 ; 
 scalar_t__ ATA_SA600 ; 
 int ATA_SATA ; 
 int /*<<< orphan*/  ATA_SERROR ; 
 int ATA_USE_16BIT ; 
 int ENXIO ; 
 int INTEL_6CH2 ; 
 int INTEL_ICH5 ; 
 int INTEL_ICH7 ; 
 int /*<<< orphan*/  ata_intel_new_setmode ; 
 int /*<<< orphan*/  ata_intel_sata_ahci_read ; 
 int /*<<< orphan*/ * ata_intel_sata_ahci_write ; 
 int /*<<< orphan*/  ata_intel_sata_cscr_read ; 
 int /*<<< orphan*/ * ata_intel_sata_cscr_write ; 
 int /*<<< orphan*/  ata_intel_sata_sidpr_read ; 
 scalar_t__ ata_intel_sata_sidpr_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ata_intel_sata_sidpr_write ; 
 int /*<<< orphan*/  ata_intel_sata_status ; 
 scalar_t__ ata_pci_ch_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_sata_scr_write (struct ata_channel*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
ata_intel_ch_attach(device_t dev)
{
	struct ata_pci_controller *ctlr;
	struct ata_channel *ch;
	u_char *smap;
	u_int map;

	/* setup the usual register normal pci style */
	if (ata_pci_ch_attach(dev))
		return (ENXIO);

	ctlr = device_get_softc(device_get_parent(dev));
	ch = device_get_softc(dev);

	/* if r_res2 is valid it points to SATA interface registers */
	if (ctlr->r_res2) {
		ch->r_io[ATA_IDX_ADDR].res = ctlr->r_res2;
		ch->r_io[ATA_IDX_ADDR].offset = 0x00;
		ch->r_io[ATA_IDX_DATA].res = ctlr->r_res2;
		ch->r_io[ATA_IDX_DATA].offset = 0x04;
	}

	ch->flags |= ATA_ALWAYS_DMASTAT;
	if (ctlr->chip->max_dma >= ATA_SA150) {
		smap = ATA_INTEL_SMAP(ctlr, ch);
		map = pci_read_config(device_get_parent(dev), 0x90, 1);
		if (ctlr->chip->cfg1 & INTEL_ICH5) {
			map &= 0x07;
			if ((map & 0x04) == 0) {
				ch->flags |= ATA_SATA;
				ch->flags |= ATA_NO_SLAVE;
				smap[0] = (map & 0x01) ^ ch->unit;
				smap[1] = 0;
			} else if ((map & 0x02) == 0 && ch->unit == 0) {
				ch->flags |= ATA_SATA;
				smap[0] = (map & 0x01) ? 1 : 0;
				smap[1] = (map & 0x01) ? 0 : 1;
			} else if ((map & 0x02) != 0 && ch->unit == 1) {
				ch->flags |= ATA_SATA;
				smap[0] = (map & 0x01) ? 1 : 0;
				smap[1] = (map & 0x01) ? 0 : 1;
			}
		} else if (ctlr->chip->cfg1 & INTEL_6CH2) {
			ch->flags |= ATA_SATA;
			ch->flags |= ATA_NO_SLAVE;
			smap[0] = (ch->unit == 0) ? 0 : 1;
			smap[1] = 0;
		} else {
			map &= 0x03;
			if (map == 0x00) {
				ch->flags |= ATA_SATA;
				smap[0] = (ch->unit == 0) ? 0 : 1;
				smap[1] = (ch->unit == 0) ? 2 : 3;
			} else if (map == 0x02 && ch->unit == 0) {
				ch->flags |= ATA_SATA;
				smap[0] = 0;
				smap[1] = 2;
			} else if (map == 0x01 && ch->unit == 1) {
				ch->flags |= ATA_SATA;
				smap[0] = 1;
				smap[1] = 3;
			}
		}
		if (ch->flags & ATA_SATA) {
			if ((ctlr->chip->cfg1 & INTEL_ICH5)) {
				ch->hw.pm_read = ata_intel_sata_cscr_read;
				ch->hw.pm_write = ata_intel_sata_cscr_write;
			} else if (ctlr->r_res2) {
				if ((ctlr->chip->cfg1 & INTEL_ICH7)) {
					ch->hw.pm_read = ata_intel_sata_ahci_read;
					ch->hw.pm_write = ata_intel_sata_ahci_write;
				} else if (ata_intel_sata_sidpr_test(dev)) {
					ch->hw.pm_read = ata_intel_sata_sidpr_read;
					ch->hw.pm_write = ata_intel_sata_sidpr_write;
				}
			}
			if (ch->hw.pm_write != NULL) {
				ch->flags |= ATA_PERIODIC_POLL;
				ch->hw.status = ata_intel_sata_status;
				ata_sata_scr_write(ch, 0,
				    ATA_SERROR, 0xffffffff);
				if ((ch->flags & ATA_NO_SLAVE) == 0) {
					ata_sata_scr_write(ch, 1,
					    ATA_SERROR, 0xffffffff);
				}
			}
		} else
			ctlr->setmode = ata_intel_new_setmode;
		if (ctlr->chip->max_dma >= ATA_SA600)
			ch->flags |= ATA_USE_16BIT;
	} else if (ctlr->chip->chipid != ATA_ISCH)
		ch->flags |= ATA_CHECKS_CABLE;
	return (0);
}