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
struct ata_port {int flags; } ;
struct TYPE_4__ {int flags; } ;
struct ata_eh_context {TYPE_2__ i; } ;
struct ata_device {int horkage; scalar_t__ xfer_shift; int* id; scalar_t__ pio_mode; scalar_t__ dma_mode; scalar_t__ xfer_mode; int /*<<< orphan*/  flags; TYPE_1__* link; } ;
struct TYPE_3__ {struct ata_eh_context eh_context; struct ata_port* ap; } ;

/* Variables and functions */
 unsigned int AC_ERR_DEV ; 
 int /*<<< orphan*/  ATA_DEV_UNKNOWN ; 
 int /*<<< orphan*/  ATA_DFLAG_PIO ; 
 int ATA_EHI_DID_HARDRESET ; 
 int ATA_EHI_POST_SETMODE ; 
 int ATA_EHI_QUIET ; 
 int ATA_FLAG_SATA ; 
 int ATA_HORKAGE_NOSETXFER ; 
 scalar_t__ ATA_SHIFT_MWDMA ; 
 scalar_t__ ATA_SHIFT_PIO ; 
 int /*<<< orphan*/  DPRINTK (char*,scalar_t__,int) ; 
 int EIO ; 
 scalar_t__ XFER_MW_DMA_0 ; 
 scalar_t__ XFER_PIO_2 ; 
 int /*<<< orphan*/  ata_dev_err (struct ata_device*,char*,unsigned int) ; 
 int /*<<< orphan*/  ata_dev_info (struct ata_device*,char*,int /*<<< orphan*/ ,char const*) ; 
 int ata_dev_revalidate (struct ata_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ata_dev_set_xfermode (struct ata_device*) ; 
 int /*<<< orphan*/  ata_dev_warn (struct ata_device*,char*) ; 
 int /*<<< orphan*/  ata_id_has_iordy (int*) ; 
 scalar_t__ ata_id_is_cfa (int*) ; 
 scalar_t__ ata_id_is_sata (int*) ; 
 scalar_t__ ata_id_major_version (int*) ; 
 int /*<<< orphan*/  ata_id_xfermask (int*) ; 
 int /*<<< orphan*/  ata_mode_string (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_xfer_mask2mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_xfer_mode2mask (scalar_t__) ; 

__attribute__((used)) static int ata_dev_set_mode(struct ata_device *dev)
{
	struct ata_port *ap = dev->link->ap;
	struct ata_eh_context *ehc = &dev->link->eh_context;
	const bool nosetxfer = dev->horkage & ATA_HORKAGE_NOSETXFER;
	const char *dev_err_whine = "";
	int ign_dev_err = 0;
	unsigned int err_mask = 0;
	int rc;

	dev->flags &= ~ATA_DFLAG_PIO;
	if (dev->xfer_shift == ATA_SHIFT_PIO)
		dev->flags |= ATA_DFLAG_PIO;

	if (nosetxfer && ap->flags & ATA_FLAG_SATA && ata_id_is_sata(dev->id))
		dev_err_whine = " (SET_XFERMODE skipped)";
	else {
		if (nosetxfer)
			ata_dev_warn(dev,
				     "NOSETXFER but PATA detected - can't "
				     "skip SETXFER, might malfunction\n");
		err_mask = ata_dev_set_xfermode(dev);
	}

	if (err_mask & ~AC_ERR_DEV)
		goto fail;

	/* revalidate */
	ehc->i.flags |= ATA_EHI_POST_SETMODE;
	rc = ata_dev_revalidate(dev, ATA_DEV_UNKNOWN, 0);
	ehc->i.flags &= ~ATA_EHI_POST_SETMODE;
	if (rc)
		return rc;

	if (dev->xfer_shift == ATA_SHIFT_PIO) {
		/* Old CFA may refuse this command, which is just fine */
		if (ata_id_is_cfa(dev->id))
			ign_dev_err = 1;
		/* Catch several broken garbage emulations plus some pre
		   ATA devices */
		if (ata_id_major_version(dev->id) == 0 &&
					dev->pio_mode <= XFER_PIO_2)
			ign_dev_err = 1;
		/* Some very old devices and some bad newer ones fail
		   any kind of SET_XFERMODE request but support PIO0-2
		   timings and no IORDY */
		if (!ata_id_has_iordy(dev->id) && dev->pio_mode <= XFER_PIO_2)
			ign_dev_err = 1;
	}
	/* Early MWDMA devices do DMA but don't allow DMA mode setting.
	   Don't fail an MWDMA0 set IFF the device indicates it is in MWDMA0 */
	if (dev->xfer_shift == ATA_SHIFT_MWDMA &&
	    dev->dma_mode == XFER_MW_DMA_0 &&
	    (dev->id[63] >> 8) & 1)
		ign_dev_err = 1;

	/* if the device is actually configured correctly, ignore dev err */
	if (dev->xfer_mode == ata_xfer_mask2mode(ata_id_xfermask(dev->id)))
		ign_dev_err = 1;

	if (err_mask & AC_ERR_DEV) {
		if (!ign_dev_err)
			goto fail;
		else
			dev_err_whine = " (device error ignored)";
	}

	DPRINTK("xfer_shift=%u, xfer_mode=0x%x\n",
		dev->xfer_shift, (int)dev->xfer_mode);

	if (!(ehc->i.flags & ATA_EHI_QUIET) ||
	    ehc->i.flags & ATA_EHI_DID_HARDRESET)
		ata_dev_info(dev, "configured for %s%s\n",
			     ata_mode_string(ata_xfer_mode2mask(dev->xfer_mode)),
			     dev_err_whine);

	return 0;

 fail:
	ata_dev_err(dev, "failed to set xfermode (err_mask=0x%x)\n", err_mask);
	return -EIO;
}