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
typedef  int u_int8_t ;
struct ata_channel {int flags; int devices; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATAPI_MAGIC_LSB ; 
 int ATAPI_MAGIC_MSB ; 
 int ATA_ATAPI_MASTER ; 
 int ATA_ATAPI_SLAVE ; 
 int ATA_ATA_MASTER ; 
 int ATA_ATA_SLAVE ; 
 int ATA_A_IDS ; 
 int ATA_A_RESET ; 
 int /*<<< orphan*/  ATA_CONTROL ; 
 int /*<<< orphan*/  ATA_CYL_LSB ; 
 int /*<<< orphan*/  ATA_CYL_MSB ; 
 int ATA_DEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_DRIVE ; 
 int ATA_D_IBM ; 
 int ATA_D_LBA ; 
 int /*<<< orphan*/  ATA_ERROR ; 
 int ATA_E_ILI ; 
 int ATA_IDX_INB (struct ata_channel*,int /*<<< orphan*/ ) ; 
 int ATA_IDX_INL (struct ata_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_IDX_OUTB (struct ata_channel*,int /*<<< orphan*/ ,int) ; 
 int ATA_KNOWN_PRESENCE ; 
 int /*<<< orphan*/  ATA_MASTER ; 
 int ATA_NO_SLAVE ; 
 int /*<<< orphan*/  ATA_SLAVE ; 
 int /*<<< orphan*/  ATA_STATUS ; 
 int ATA_STATUS_IS_LONG ; 
 int ATA_S_BUSY ; 
 int ATA_S_READY ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ata_udelay (int) ; 
 scalar_t__ bootverbose ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int,...) ; 

void
ata_generic_reset(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);

    u_int8_t ostat0 = 0, stat0 = 0, ostat1 = 0, stat1 = 0;
    u_int8_t err = 0, lsb = 0, msb = 0;
    int mask = 0, timeout;

    /* do we have any signs of ATA/ATAPI HW being present ? */
    ATA_IDX_OUTB(ch, ATA_DRIVE, ATA_D_IBM | ATA_D_LBA | ATA_DEV(ATA_MASTER));
    DELAY(10);
    ostat0 = ATA_IDX_INB(ch, ATA_STATUS);
    if (((ostat0 & 0xf8) != 0xf8 || (ch->flags & ATA_KNOWN_PRESENCE)) &&
	    ostat0 != 0xa5) {
	stat0 = ATA_S_BUSY;
	mask |= 0x01;
    }

    /* in some setups we dont want to test for a slave */
    if (!(ch->flags & ATA_NO_SLAVE)) {
	ATA_IDX_OUTB(ch, ATA_DRIVE, ATA_D_IBM | ATA_D_LBA | ATA_DEV(ATA_SLAVE));
	DELAY(10);      
	ostat1 = ATA_IDX_INB(ch, ATA_STATUS);
	if (((ostat1 & 0xf8) != 0xf8 || (ch->flags & ATA_KNOWN_PRESENCE)) &&
		ostat1 != 0xa5) {
	    stat1 = ATA_S_BUSY;
	    mask |= 0x02;
	}
    }

    if (bootverbose)
	device_printf(dev, "reset tp1 mask=%02x ostat0=%02x ostat1=%02x\n",
		      mask, ostat0, ostat1);

    /* if nothing showed up there is no need to get any further */
    /* XXX SOS is that too strong?, we just might lose devices here */
    ch->devices = 0;
    if (!mask)
	return;

    /* reset (both) devices on this channel */
    ATA_IDX_OUTB(ch, ATA_DRIVE, ATA_D_IBM | ATA_D_LBA | ATA_DEV(ATA_MASTER));
    DELAY(10);
    ATA_IDX_OUTB(ch, ATA_CONTROL, ATA_A_IDS | ATA_A_RESET);
    ata_udelay(10000); 
    ATA_IDX_OUTB(ch, ATA_CONTROL, ATA_A_IDS);
    ata_udelay(100000);
    ATA_IDX_INB(ch, ATA_ERROR);

    /* wait for BUSY to go inactive */
    for (timeout = 0; timeout < 310; timeout++) {
	if ((mask & 0x01) && (stat0 & ATA_S_BUSY)) {
	    ATA_IDX_OUTB(ch, ATA_DRIVE, ATA_D_IBM | ATA_DEV(ATA_MASTER));
	    DELAY(10);
	    if (ch->flags & ATA_STATUS_IS_LONG)
		    stat0 = ATA_IDX_INL(ch, ATA_STATUS) & 0xff;
	    else
		    stat0 = ATA_IDX_INB(ch, ATA_STATUS);
	    err = ATA_IDX_INB(ch, ATA_ERROR);
	    lsb = ATA_IDX_INB(ch, ATA_CYL_LSB);
	    msb = ATA_IDX_INB(ch, ATA_CYL_MSB);
	    if (bootverbose)
		device_printf(dev,
			      "stat0=0x%02x err=0x%02x lsb=0x%02x msb=0x%02x\n",
			      stat0, err, lsb, msb);
	    if (stat0 == err && lsb == err && msb == err &&
		timeout > (stat0 & ATA_S_BUSY ? 100 : 10))
		mask &= ~0x01;
	    if (!(stat0 & ATA_S_BUSY)) {
		if ((err & 0x7f) == ATA_E_ILI) {
		    if (lsb == ATAPI_MAGIC_LSB && msb == ATAPI_MAGIC_MSB) {
			ch->devices |= ATA_ATAPI_MASTER;
		    }
		    else if (lsb == 0 && msb == 0 && (stat0 & ATA_S_READY)) {
			ch->devices |= ATA_ATA_MASTER;
		    }
		}
		else if ((stat0 & 0x0f) && err == lsb && err == msb) {
		    stat0 |= ATA_S_BUSY;
		}
	    }
	}

	if ((mask & 0x02) && (stat1 & ATA_S_BUSY) &&
	    !((mask & 0x01) && (stat0 & ATA_S_BUSY))) {
	    ATA_IDX_OUTB(ch, ATA_DRIVE, ATA_D_IBM | ATA_DEV(ATA_SLAVE));
	    DELAY(10);
	    if (ch->flags & ATA_STATUS_IS_LONG)
		    stat1 = ATA_IDX_INL(ch, ATA_STATUS) & 0xff;
	    else
		    stat1 = ATA_IDX_INB(ch, ATA_STATUS);
	    err = ATA_IDX_INB(ch, ATA_ERROR);
	    lsb = ATA_IDX_INB(ch, ATA_CYL_LSB);
	    msb = ATA_IDX_INB(ch, ATA_CYL_MSB);
	    if (bootverbose)
		device_printf(dev,
			      "stat1=0x%02x err=0x%02x lsb=0x%02x msb=0x%02x\n",
			      stat1, err, lsb, msb);
	    if (stat1 == err && lsb == err && msb == err &&
		timeout > (stat1 & ATA_S_BUSY ? 100 : 10))
		mask &= ~0x02;
	    if (!(stat1 & ATA_S_BUSY)) {
		if ((err & 0x7f) == ATA_E_ILI) {
		    if (lsb == ATAPI_MAGIC_LSB && msb == ATAPI_MAGIC_MSB) {
			ch->devices |= ATA_ATAPI_SLAVE;
		    }
		    else if (lsb == 0 && msb == 0 && (stat1 & ATA_S_READY)) {
			ch->devices |= ATA_ATA_SLAVE;
		    }
		}
		else if ((stat1 & 0x0f) && err == lsb && err == msb) {
		    stat1 |= ATA_S_BUSY;
		}
	    }
	}

	if ((ch->flags & ATA_KNOWN_PRESENCE) == 0 &&
	    timeout > ((mask == 0x03) ? 20 : 10)) {
		if ((mask & 0x01) && stat0 == 0xff)
			mask &= ~0x01;
		if ((mask & 0x02) && stat1 == 0xff)
			mask &= ~0x02;
	}
	if (((mask & 0x01) == 0 || !(stat0 & ATA_S_BUSY)) &&
	    ((mask & 0x02) == 0 || !(stat1 & ATA_S_BUSY)))
		break;
	ata_udelay(100000);
    }

    if (bootverbose)
	device_printf(dev, "reset tp2 stat0=%02x stat1=%02x devices=0x%x\n",
		      stat0, stat1, ch->devices);
}