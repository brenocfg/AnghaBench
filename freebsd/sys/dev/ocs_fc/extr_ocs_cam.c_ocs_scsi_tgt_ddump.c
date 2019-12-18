#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* flags; char* status; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
typedef  int ocs_scsi_ddump_type_e ;
struct TYPE_5__ {scalar_t__ app; int /*<<< orphan*/  state; } ;
struct TYPE_6__ {TYPE_2__ tgt_io; } ;
typedef  TYPE_3__ ocs_io_t ;

/* Variables and functions */
#define  OCS_CAM_IO_COMMAND 137 
#define  OCS_CAM_IO_DATA 136 
#define  OCS_CAM_IO_DATA_DONE 135 
#define  OCS_CAM_IO_FREE 134 
#define  OCS_CAM_IO_RESP 133 
#define  OCS_SCSI_DDUMP_DEVICE 132 
#define  OCS_SCSI_DDUMP_DOMAIN 131 
#define  OCS_SCSI_DDUMP_IO 130 
#define  OCS_SCSI_DDUMP_NODE 129 
#define  OCS_SCSI_DDUMP_SPORT 128 
 int /*<<< orphan*/  ocs_ddump_value (int /*<<< orphan*/ *,char*,char*,char*) ; 

void
ocs_scsi_tgt_ddump(ocs_textbuf_t *textbuf, ocs_scsi_ddump_type_e type, void *obj)
{
	switch(type) {
	case OCS_SCSI_DDUMP_DEVICE: {
		//ocs_t *ocs = obj;
		break;
	}
	case OCS_SCSI_DDUMP_DOMAIN: {
		//ocs_domain_t *domain = obj;
		break;
	}
	case OCS_SCSI_DDUMP_SPORT: {
		//ocs_sport_t *sport = obj;
		break;
	}
	case OCS_SCSI_DDUMP_NODE: {
		//ocs_node_t *node = obj;
		break;
	}
	case OCS_SCSI_DDUMP_IO: {
		ocs_io_t *io = obj;
		char *state_str = NULL;

		switch (io->tgt_io.state) {
		case OCS_CAM_IO_FREE:
			state_str = "FREE";
			break;
		case OCS_CAM_IO_COMMAND:
			state_str = "COMMAND";
			break;
		case OCS_CAM_IO_DATA:
			state_str = "DATA";
			break;
		case OCS_CAM_IO_DATA_DONE:
			state_str = "DATA_DONE";
			break;
		case OCS_CAM_IO_RESP:
			state_str = "RESP";
			break;
		default:
			state_str = "xxx BAD xxx";
		}
		ocs_ddump_value(textbuf, "cam_st", "%s", state_str);
		if (io->tgt_io.app) {
			ocs_ddump_value(textbuf, "cam_flags", "%#x",
				((union ccb *)(io->tgt_io.app))->ccb_h.flags);
			ocs_ddump_value(textbuf, "cam_status", "%#x",
				((union ccb *)(io->tgt_io.app))->ccb_h.status);
		}

		break;
	}
	default: {
		break;
	}
	}
}