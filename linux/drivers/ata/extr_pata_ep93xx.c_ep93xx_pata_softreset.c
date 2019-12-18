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
struct ata_port {unsigned int flags; TYPE_1__* ops; } ;
struct ata_link {int /*<<< orphan*/ * device; struct ata_port* ap; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sff_dev_select ) (struct ata_port*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 unsigned int ATA_FLAG_SLAVE_POSS ; 
 int ENODEV ; 
 int /*<<< orphan*/  ata_link_err (struct ata_link*,char*,int) ; 
 unsigned int ata_sff_dev_classify (int /*<<< orphan*/ *,unsigned int,int*) ; 
 int ep93xx_pata_bus_softreset (struct ata_port*,unsigned int,unsigned long) ; 
 scalar_t__ ep93xx_pata_device_is_present (struct ata_port*,int) ; 
 scalar_t__ sata_scr_valid (struct ata_link*) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ep93xx_pata_softreset(struct ata_link *al, unsigned int *classes,
				 unsigned long deadline)
{
	struct ata_port *ap = al->ap;
	unsigned int slave_possible = ap->flags & ATA_FLAG_SLAVE_POSS;
	unsigned int devmask = 0;
	int rc;
	u8 err;

	/* determine if device 0/1 are present */
	if (ep93xx_pata_device_is_present(ap, 0))
		devmask |= (1 << 0);
	if (slave_possible && ep93xx_pata_device_is_present(ap, 1))
		devmask |= (1 << 1);

	/* select device 0 again */
	ap->ops->sff_dev_select(al->ap, 0);

	/* issue bus reset */
	rc = ep93xx_pata_bus_softreset(ap, devmask, deadline);
	/* if link is ocuppied, -ENODEV too is an error */
	if (rc && (rc != -ENODEV || sata_scr_valid(al))) {
		ata_link_err(al, "SRST failed (errno=%d)\n", rc);
		return rc;
	}

	/* determine by signature whether we have ATA or ATAPI devices */
	classes[0] = ata_sff_dev_classify(&al->device[0], devmask & (1 << 0),
					  &err);
	if (slave_possible && err != 0x81)
		classes[1] = ata_sff_dev_classify(&al->device[1],
						  devmask & (1 << 1), &err);

	return 0;
}