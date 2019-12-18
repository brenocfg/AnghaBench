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
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
typedef  int ocs_scsi_ddump_type_e ;

/* Variables and functions */
#define  OCS_SCSI_DDUMP_DEVICE 132 
#define  OCS_SCSI_DDUMP_DOMAIN 131 
#define  OCS_SCSI_DDUMP_IO 130 
#define  OCS_SCSI_DDUMP_NODE 129 
#define  OCS_SCSI_DDUMP_SPORT 128 

void
ocs_scsi_ini_ddump(ocs_textbuf_t *textbuf, ocs_scsi_ddump_type_e type, void *obj)
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
		//ocs_io_t *io = obj;
		break;
	}
	default: {
		break;
	}
	}
}