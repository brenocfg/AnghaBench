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
typedef  int u8 ;
struct ep93xx_pata_data {int dummy; } ;
struct ata_port {TYPE_2__* ops; TYPE_1__* host; } ;
struct ata_link {struct ata_port* ap; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* sff_dev_select ) (struct ata_port*,int) ;} ;
struct TYPE_3__ {struct ep93xx_pata_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_WAIT_AFTER_RESET ; 
 int ENODEV ; 
 int /*<<< orphan*/  IDECTRL_ADDR_LBAL ; 
 int /*<<< orphan*/  IDECTRL_ADDR_NSECT ; 
 int /*<<< orphan*/  ata_msleep (struct ata_port*,int /*<<< orphan*/ ) ; 
 int ata_sff_wait_ready (struct ata_link*,unsigned long) ; 
 int ep93xx_pata_read_reg (struct ep93xx_pata_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,int) ; 
 int /*<<< orphan*/  stub2 (struct ata_port*,int) ; 
 int /*<<< orphan*/  stub3 (struct ata_port*,int) ; 
 int /*<<< orphan*/  stub4 (struct ata_port*,int) ; 

__attribute__((used)) static int ep93xx_pata_wait_after_reset(struct ata_link *link,
					unsigned int devmask,
					unsigned long deadline)
{
	struct ata_port *ap = link->ap;
	struct ep93xx_pata_data *drv_data = ap->host->private_data;
	unsigned int dev0 = devmask & (1 << 0);
	unsigned int dev1 = devmask & (1 << 1);
	int rc, ret = 0;

	ata_msleep(ap, ATA_WAIT_AFTER_RESET);

	/* always check readiness of the master device */
	rc = ata_sff_wait_ready(link, deadline);
	/*
	 * -ENODEV means the odd clown forgot the D7 pulldown resistor
	 * and TF status is 0xff, bail out on it too.
	 */
	if (rc)
		return rc;

	/*
	 * if device 1 was found in ata_devchk, wait for register
	 * access briefly, then wait for BSY to clear.
	 */
	if (dev1) {
		int i;

		ap->ops->sff_dev_select(ap, 1);

		/*
		 * Wait for register access.  Some ATAPI devices fail
		 * to set nsect/lbal after reset, so don't waste too
		 * much time on it.  We're gonna wait for !BSY anyway.
		 */
		for (i = 0; i < 2; i++) {
			u8 nsect, lbal;

			nsect = ep93xx_pata_read_reg(drv_data,
				IDECTRL_ADDR_NSECT);
			lbal = ep93xx_pata_read_reg(drv_data,
				IDECTRL_ADDR_LBAL);
			if (nsect == 1 && lbal == 1)
				break;
			msleep(50);	/* give drive a breather */
		}

		rc = ata_sff_wait_ready(link, deadline);
		if (rc) {
			if (rc != -ENODEV)
				return rc;
			ret = rc;
		}
	}
	/* is all this really necessary? */
	ap->ops->sff_dev_select(ap, 0);
	if (dev1)
		ap->ops->sff_dev_select(ap, 1);
	if (dev0)
		ap->ops->sff_dev_select(ap, 0);

	return ret;
}