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
typedef  int /*<<< orphan*/  u16 ;
struct ata_device {unsigned int class; int /*<<< orphan*/  id; TYPE_2__* link; } ;
typedef  int /*<<< orphan*/  id ;
struct TYPE_4__ {TYPE_1__* ap; } ;
struct TYPE_3__ {scalar_t__ sector_buf; } ;

/* Variables and functions */
 int ATA_ID_WORDS ; 
 int ENODEV ; 
 int ata_dev_read_id (struct ata_device*,unsigned int*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ata_dev_same_device (struct ata_device*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int ata_dev_reread_id(struct ata_device *dev, unsigned int readid_flags)
{
	unsigned int class = dev->class;
	u16 *id = (void *)dev->link->ap->sector_buf;
	int rc;

	/* read ID data */
	rc = ata_dev_read_id(dev, &class, readid_flags, id);
	if (rc)
		return rc;

	/* is the device still there? */
	if (!ata_dev_same_device(dev, class, id))
		return -ENODEV;

	memcpy(dev->id, id, sizeof(id[0]) * ATA_ID_WORDS);
	return 0;
}