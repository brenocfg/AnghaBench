#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct ata_promise_sx4 {int /*<<< orphan*/  mtx; int /*<<< orphan*/  busy; } ;
struct ata_pci_controller {int /*<<< orphan*/  r_res2; TYPE_1__* chip; struct ata_promise_sx4* chipset_data; } ;
struct TYPE_4__ {int (* softreset ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct ata_channel {int unit; int devices; TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int cfg2; } ;

/* Variables and functions */
 int ATA_ATAPI_MASTER ; 
 void* ATA_ATA_MASTER ; 
 int ATA_INL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ATA_PM ; 
 int ATA_PORTMULTIPLIER ; 
 int /*<<< orphan*/  DELAY (int) ; 
#define  PR_CMBO 133 
#define  PR_CMBO2 132 
#define  PR_PATA 131 
#define  PR_SATA 130 
#define  PR_SATA2 129 
#define  PR_SX4X 128 
 int /*<<< orphan*/  ata_generic_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_pm_identify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_sata_phy_reset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ata_udelay (int) ; 
 int bootverbose ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ata_promise_mio_reset(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);
    struct ata_promise_sx4 *hpktp;

    switch (ctlr->chip->cfg2) {
    case PR_SX4X:

	/* softreset channel ATA module */
	hpktp = ctlr->chipset_data;
	ATA_OUTL(ctlr->r_res2, 0xc0260 + (ch->unit << 7), ch->unit + 1);
	ata_udelay(1000);
	ATA_OUTL(ctlr->r_res2, 0xc0260 + (ch->unit << 7),
		 (ATA_INL(ctlr->r_res2, 0xc0260 + (ch->unit << 7)) &
		  ~0x00003f9f) | (ch->unit + 1));

	/* softreset HOST module */ /* XXX SOS what about other outstandings */
	mtx_lock(&hpktp->mtx);
	ATA_OUTL(ctlr->r_res2, 0xc012c,
		 (ATA_INL(ctlr->r_res2, 0xc012c) & ~0x00000f9f) | (1 << 11));
	DELAY(10);
	ATA_OUTL(ctlr->r_res2, 0xc012c,
		 (ATA_INL(ctlr->r_res2, 0xc012c) & ~0x00000f9f));
	hpktp->busy = 0;
	mtx_unlock(&hpktp->mtx);
	ata_generic_reset(dev);
	break;

    case PR_PATA:
    case PR_CMBO:
    case PR_SATA:
	if ((ctlr->chip->cfg2 == PR_SATA) ||
	    ((ctlr->chip->cfg2 == PR_CMBO) && (ch->unit < 2))) {

	    /* mask plug/unplug intr */
	    ATA_OUTL(ctlr->r_res2, 0x06c, (0x00110000 << ch->unit));
	}

	/* softreset channels ATA module */
	ATA_OUTL(ctlr->r_res2, 0x0260 + (ch->unit << 7), (1 << 11));
	ata_udelay(10000);
	ATA_OUTL(ctlr->r_res2, 0x0260 + (ch->unit << 7),
		 (ATA_INL(ctlr->r_res2, 0x0260 + (ch->unit << 7)) &
		  ~0x00003f9f) | (ch->unit + 1));

	if ((ctlr->chip->cfg2 == PR_SATA) ||
	    ((ctlr->chip->cfg2 == PR_CMBO) && (ch->unit < 2))) {

	    if (ata_sata_phy_reset(dev, -1, 1))
		ata_generic_reset(dev);
	    else
		ch->devices = 0;

	    /* reset and enable plug/unplug intr */
	    ATA_OUTL(ctlr->r_res2, 0x06c, (0x00000011 << ch->unit));
	}
	else
	    ata_generic_reset(dev);
	break;

    case PR_CMBO2:
    case PR_SATA2:
	if ((ctlr->chip->cfg2 == PR_SATA2) ||
	    ((ctlr->chip->cfg2 == PR_CMBO2) && (ch->unit < 2))) {
	    /* set portmultiplier port */
	    //ATA_OUTL(ctlr->r_res2, 0x4e8 + (ch->unit << 8), 0x0f);

	    /* mask plug/unplug intr */
	    ATA_OUTL(ctlr->r_res2, 0x060, (0x00110000 << ch->unit));
	}

	/* softreset channels ATA module */
	ATA_OUTL(ctlr->r_res2, 0x0260 + (ch->unit << 7), (1 << 11));
	ata_udelay(10000);
	ATA_OUTL(ctlr->r_res2, 0x0260 + (ch->unit << 7),
		 (ATA_INL(ctlr->r_res2, 0x0260 + (ch->unit << 7)) &
		  ~0x00003f9f) | (ch->unit + 1));

	if ((ctlr->chip->cfg2 == PR_SATA2) ||
	    ((ctlr->chip->cfg2 == PR_CMBO2) && (ch->unit < 2))) {

	    /* set PHY mode to "improved" */
	    ATA_OUTL(ctlr->r_res2, 0x414 + (ch->unit << 8),
		     (ATA_INL(ctlr->r_res2, 0x414 + (ch->unit << 8)) &
		     ~0x00000003) | 0x00000001);

	    if (ata_sata_phy_reset(dev, -1, 1)) {
		u_int32_t signature = ch->hw.softreset(dev, ATA_PM);

		if (1 | bootverbose)
        	    device_printf(dev, "SIGNATURE: %08x\n", signature);

		switch (signature >> 16) {
		case 0x0000:
		    ch->devices = ATA_ATA_MASTER;
		    break;
		case 0x9669:
		    ch->devices = ATA_PORTMULTIPLIER;
		    ata_pm_identify(dev);
		    break;
		case 0xeb14:
		    ch->devices = ATA_ATAPI_MASTER;
		    break;
		default: /* SOS XXX */
		    if (bootverbose)
			device_printf(dev,
				      "No signature, assuming disk device\n");
		    ch->devices = ATA_ATA_MASTER;
		}
		if (bootverbose)
		    device_printf(dev, "promise_mio_reset devices=%08x\n",
		    		  ch->devices);

	    } else
		ch->devices = 0;

	    /* reset and enable plug/unplug intr */
	    ATA_OUTL(ctlr->r_res2, 0x060, (0x00000011 << ch->unit));

	    ///* set portmultiplier port */
	    ATA_OUTL(ctlr->r_res2, 0x4e8 + (ch->unit << 8), 0x00);
	}
	else
	    ata_generic_reset(dev);
	break;

    }
}