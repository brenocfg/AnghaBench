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
struct ata_port {int /*<<< orphan*/  sector_buf; } ;
struct ata_device {int /*<<< orphan*/ * ncq_non_data_cmds; TYPE_1__* link; } ;
struct TYPE_2__ {struct ata_port* ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_LOG_NCQ_NON_DATA ; 
 int /*<<< orphan*/  ATA_LOG_NCQ_NON_DATA_SIZE ; 
 int /*<<< orphan*/  ata_dev_dbg (struct ata_device*,char*,unsigned int) ; 
 int /*<<< orphan*/  ata_dev_warn (struct ata_device*,char*) ; 
 int /*<<< orphan*/  ata_log_supported (struct ata_device*,int /*<<< orphan*/ ) ; 
 unsigned int ata_read_log_page (struct ata_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ata_dev_config_ncq_non_data(struct ata_device *dev)
{
	struct ata_port *ap = dev->link->ap;
	unsigned int err_mask;

	if (!ata_log_supported(dev, ATA_LOG_NCQ_NON_DATA)) {
		ata_dev_warn(dev,
			     "NCQ Send/Recv Log not supported\n");
		return;
	}
	err_mask = ata_read_log_page(dev, ATA_LOG_NCQ_NON_DATA,
				     0, ap->sector_buf, 1);
	if (err_mask) {
		ata_dev_dbg(dev,
			    "failed to get NCQ Non-Data Log Emask 0x%x\n",
			    err_mask);
	} else {
		u8 *cmds = dev->ncq_non_data_cmds;

		memcpy(cmds, ap->sector_buf, ATA_LOG_NCQ_NON_DATA_SIZE);
	}
}