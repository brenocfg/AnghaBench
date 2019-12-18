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
typedef  void* uint8_t ;
struct TYPE_4__ {int error_code; int extra_len; void* add_sense_code_qual; void* add_sense_code; void* flags; } ;
struct TYPE_3__ {int status; } ;
struct ccb_scsiio {int sense_len; TYPE_2__ sense_data; int /*<<< orphan*/  scsi_status; TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int CAM_AUTOSNS_VALID ; 
 int CAM_SCSI_STATUS_ERROR ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_COND ; 
 int SSD_CURRENT_ERROR ; 
 int SSD_ERRCODE_VALID ; 

void
vhba_fill_sense(struct ccb_scsiio *csio, uint8_t key, uint8_t asc, uint8_t ascq)
{
	csio->ccb_h.status = CAM_SCSI_STATUS_ERROR|CAM_AUTOSNS_VALID;
	csio->scsi_status = SCSI_STATUS_CHECK_COND;
	csio->sense_data.error_code = SSD_ERRCODE_VALID|SSD_CURRENT_ERROR;
	csio->sense_data.flags = key;
	csio->sense_data.extra_len = 10;
	csio->sense_data.add_sense_code = asc;
	csio->sense_data.add_sense_code_qual = ascq;
	csio->sense_len = sizeof (csio->sense_data);
}