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
typedef  int /*<<< orphan*/  u32 ;
struct ata_port {scalar_t__ sector_buf; } ;
struct ata_link {struct ata_port* ap; } ;
struct ata_device {int /*<<< orphan*/  gscr; struct ata_link* link; } ;
typedef  int /*<<< orphan*/  gscr ;

/* Variables and functions */
 unsigned int ATA_DEV_PMP ; 
 int /*<<< orphan*/  ATA_EH_REVALIDATE ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int ENODEV ; 
 int SATA_PMP_GSCR_DWORDS ; 
 scalar_t__ ata_class_enabled (unsigned int) ; 
 int /*<<< orphan*/  ata_dev_enabled (struct ata_device*) ; 
 int /*<<< orphan*/  ata_dev_err (struct ata_device*,char*,int) ; 
 int /*<<< orphan*/  ata_eh_about_to_do (struct ata_link*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_eh_done (struct ata_link*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int sata_pmp_configure (struct ata_device*,int /*<<< orphan*/ ) ; 
 int sata_pmp_read_gscr (struct ata_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sata_pmp_same_pmp (struct ata_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sata_pmp_revalidate(struct ata_device *dev, unsigned int new_class)
{
	struct ata_link *link = dev->link;
	struct ata_port *ap = link->ap;
	u32 *gscr = (void *)ap->sector_buf;
	int rc;

	DPRINTK("ENTER\n");

	ata_eh_about_to_do(link, NULL, ATA_EH_REVALIDATE);

	if (!ata_dev_enabled(dev)) {
		rc = -ENODEV;
		goto fail;
	}

	/* wrong class? */
	if (ata_class_enabled(new_class) && new_class != ATA_DEV_PMP) {
		rc = -ENODEV;
		goto fail;
	}

	/* read GSCR */
	rc = sata_pmp_read_gscr(dev, gscr);
	if (rc)
		goto fail;

	/* is the pmp still there? */
	if (!sata_pmp_same_pmp(dev, gscr)) {
		rc = -ENODEV;
		goto fail;
	}

	memcpy(dev->gscr, gscr, sizeof(gscr[0]) * SATA_PMP_GSCR_DWORDS);

	rc = sata_pmp_configure(dev, 0);
	if (rc)
		goto fail;

	ata_eh_done(link, NULL, ATA_EH_REVALIDATE);

	DPRINTK("EXIT, rc=0\n");
	return 0;

 fail:
	ata_dev_err(dev, "PMP revalidation failed (errno=%d)\n", rc);
	DPRINTK("EXIT, rc=%d\n", rc);
	return rc;
}