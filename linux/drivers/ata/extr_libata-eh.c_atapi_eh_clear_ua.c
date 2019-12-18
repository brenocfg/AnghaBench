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
typedef  scalar_t__ u8 ;
struct ata_device {TYPE_2__* link; } ;
struct TYPE_4__ {TYPE_1__* ap; } ;
struct TYPE_3__ {scalar_t__* sector_buf; } ;

/* Variables and functions */
 unsigned int AC_ERR_DEV ; 
 int ATA_EH_UA_TRIES ; 
 int EIO ; 
 scalar_t__ UNIT_ATTENTION ; 
 int /*<<< orphan*/  ata_dev_warn (struct ata_device*,char*,int) ; 
 unsigned int atapi_eh_request_sense (struct ata_device*,scalar_t__*,scalar_t__) ; 
 unsigned int atapi_eh_tur (struct ata_device*,scalar_t__*) ; 

__attribute__((used)) static int atapi_eh_clear_ua(struct ata_device *dev)
{
	int i;

	for (i = 0; i < ATA_EH_UA_TRIES; i++) {
		u8 *sense_buffer = dev->link->ap->sector_buf;
		u8 sense_key = 0;
		unsigned int err_mask;

		err_mask = atapi_eh_tur(dev, &sense_key);
		if (err_mask != 0 && err_mask != AC_ERR_DEV) {
			ata_dev_warn(dev,
				     "TEST_UNIT_READY failed (err_mask=0x%x)\n",
				     err_mask);
			return -EIO;
		}

		if (!err_mask || sense_key != UNIT_ATTENTION)
			return 0;

		err_mask = atapi_eh_request_sense(dev, sense_buffer, sense_key);
		if (err_mask) {
			ata_dev_warn(dev, "failed to clear "
				"UNIT ATTENTION (err_mask=0x%x)\n", err_mask);
			return -EIO;
		}
	}

	ata_dev_warn(dev, "UNIT ATTENTION persists after %d tries\n",
		     ATA_EH_UA_TRIES);

	return 0;
}