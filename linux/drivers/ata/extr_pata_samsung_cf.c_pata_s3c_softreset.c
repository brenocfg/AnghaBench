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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * device; } ;
struct ata_port {TYPE_1__ link; } ;
struct ata_link {struct ata_port* ap; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ata_link_err (struct ata_link*,char*,int) ; 
 unsigned int ata_sff_dev_classify (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int pata_s3c_bus_softreset (struct ata_port*,unsigned long) ; 
 int /*<<< orphan*/  pata_s3c_dev_select (struct ata_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ pata_s3c_devchk (struct ata_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pata_s3c_softreset(struct ata_link *link, unsigned int *classes,
			 unsigned long deadline)
{
	struct ata_port *ap = link->ap;
	unsigned int devmask = 0;
	int rc;
	u8 err;

	/* determine if device 0 is present */
	if (pata_s3c_devchk(ap, 0))
		devmask |= (1 << 0);

	/* select device 0 again */
	pata_s3c_dev_select(ap, 0);

	/* issue bus reset */
	rc = pata_s3c_bus_softreset(ap, deadline);
	/* if link is occupied, -ENODEV too is an error */
	if (rc && rc != -ENODEV) {
		ata_link_err(link, "SRST failed (errno=%d)\n", rc);
		return rc;
	}

	/* determine by signature whether we have ATA or ATAPI devices */
	classes[0] = ata_sff_dev_classify(&ap->link.device[0],
					  devmask & (1 << 0), &err);

	return 0;
}