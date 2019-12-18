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
struct ata_scsi_args {TYPE_1__* cmd; struct ata_device* dev; } ;
struct ata_device {int flags; int /*<<< orphan*/  class; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int* cmnd; } ;

/* Variables and functions */
#define  ATA_12 158 
#define  ATA_16 157 
 int /*<<< orphan*/  ATA_DEV_ZAC ; 
 int ATA_DFLAG_TRUSTED ; 
#define  INQUIRY 156 
#define  MAINTENANCE_IN 155 
#define  MODE_SELECT 154 
#define  MODE_SELECT_10 153 
#define  MODE_SENSE 152 
#define  MODE_SENSE_10 151 
#define  READ_10 150 
#define  READ_16 149 
#define  READ_6 148 
#define  READ_CAPACITY 147 
#define  REPORT_LUNS 146 
#define  REQUEST_SENSE 145 
#define  REZERO_UNIT 144 
#define  SECURITY_PROTOCOL_IN 143 
#define  SECURITY_PROTOCOL_OUT 142 
#define  SEEK_10 141 
#define  SEEK_6 140 
#define  SEND_DIAGNOSTIC 139 
#define  SERVICE_ACTION_IN_16 138 
#define  START_STOP 137 
#define  SYNCHRONIZE_CACHE 136 
#define  TEST_UNIT_READY 135 
#define  VERIFY 134 
#define  VERIFY_16 133 
#define  WRITE_10 132 
#define  WRITE_16 131 
#define  WRITE_6 130 
#define  ZBC_IN 129 
#define  ZBC_OUT 128 
 int /*<<< orphan*/  ata_dev_warn (struct ata_device*,char*,int) ; 
 int /*<<< orphan*/  ata_id_zoned_cap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ata_scsiop_maint_in(struct ata_scsi_args *args, u8 *rbuf)
{
	struct ata_device *dev = args->dev;
	u8 *cdb = args->cmd->cmnd;
	u8 supported = 0;
	unsigned int err = 0;

	if (cdb[2] != 1) {
		ata_dev_warn(dev, "invalid command format %d\n", cdb[2]);
		err = 2;
		goto out;
	}
	switch (cdb[3]) {
	case INQUIRY:
	case MODE_SENSE:
	case MODE_SENSE_10:
	case READ_CAPACITY:
	case SERVICE_ACTION_IN_16:
	case REPORT_LUNS:
	case REQUEST_SENSE:
	case SYNCHRONIZE_CACHE:
	case REZERO_UNIT:
	case SEEK_6:
	case SEEK_10:
	case TEST_UNIT_READY:
	case SEND_DIAGNOSTIC:
	case MAINTENANCE_IN:
	case READ_6:
	case READ_10:
	case READ_16:
	case WRITE_6:
	case WRITE_10:
	case WRITE_16:
	case ATA_12:
	case ATA_16:
	case VERIFY:
	case VERIFY_16:
	case MODE_SELECT:
	case MODE_SELECT_10:
	case START_STOP:
		supported = 3;
		break;
	case ZBC_IN:
	case ZBC_OUT:
		if (ata_id_zoned_cap(dev->id) ||
		    dev->class == ATA_DEV_ZAC)
			supported = 3;
		break;
	case SECURITY_PROTOCOL_IN:
	case SECURITY_PROTOCOL_OUT:
		if (dev->flags & ATA_DFLAG_TRUSTED)
			supported = 3;
		break;
	default:
		break;
	}
out:
	rbuf[1] = supported; /* supported */
	return err;
}