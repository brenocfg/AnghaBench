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
typedef  int u_int32_t ;
struct ata_pci_controller {int /*<<< orphan*/  r_res2; } ;
struct ata_channel {int unit; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_COMMAND ; 
 int /*<<< orphan*/  ATA_COUNT ; 
 int /*<<< orphan*/  ATA_CYL_LSB ; 
 int /*<<< orphan*/  ATA_CYL_MSB ; 
 int /*<<< orphan*/  ATA_DRIVE ; 
 int /*<<< orphan*/  ATA_ERROR ; 
 int ATA_E_ABORT ; 
 int /*<<< orphan*/  ATA_FEATURE ; 
 int ATA_IDX_INB (struct ata_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_IDX_OUTB (struct ata_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATA_IDX_OUTL (struct ata_channel*,int,int) ; 
 int /*<<< orphan*/  ATA_OUTB (int /*<<< orphan*/ ,int,int) ; 
 int ATA_PM ; 
#define  ATA_SCONTROL 130 
 int /*<<< orphan*/  ATA_SECTOR ; 
#define  ATA_SERROR 129 
#define  ATA_SSTATUS 128 
 int /*<<< orphan*/  ATA_STATUS ; 
 int ATA_S_BUSY ; 
 int ATA_WRITE_PM ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_promise_mio_pm_write(device_t dev, int port, int reg, u_int32_t value)
{
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);
    int timeout = 0;

    if (port < 0) {
	ATA_IDX_OUTL(ch, reg, value);
	return (0);
    }
    if (port < ATA_PM) {
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
    }
    /* set portmultiplier port */
    ATA_OUTB(ctlr->r_res2, 0x4e8 + (ch->unit << 8), 0x0f);

    ATA_IDX_OUTB(ch, ATA_FEATURE, reg);
    ATA_IDX_OUTB(ch, ATA_DRIVE, port);
    ATA_IDX_OUTB(ch, ATA_COUNT, value & 0xff);
    ATA_IDX_OUTB(ch, ATA_SECTOR, (value >> 8) & 0xff);
    ATA_IDX_OUTB(ch, ATA_CYL_LSB, (value >> 16) & 0xff);
    ATA_IDX_OUTB(ch, ATA_CYL_MSB, (value >> 24) & 0xff);

    ATA_IDX_OUTB(ch, ATA_COMMAND, ATA_WRITE_PM);

    while (timeout < 1000000) {
	u_int8_t status = ATA_IDX_INB(ch, ATA_STATUS);
	if (!(status & ATA_S_BUSY))
	    break;
	timeout += 1000;
	DELAY(1000);
    }
    if (timeout >= 1000000)
	return ATA_E_ABORT;

    return ATA_IDX_INB(ch, ATA_ERROR);
}