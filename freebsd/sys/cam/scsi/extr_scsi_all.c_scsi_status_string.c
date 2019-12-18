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
typedef  int /*<<< orphan*/  unkstr ;
struct ccb_scsiio {int scsi_status; } ;

/* Variables and functions */
#define  SCSI_STATUS_ACA_ACTIVE 137 
#define  SCSI_STATUS_BUSY 136 
#define  SCSI_STATUS_CHECK_COND 135 
#define  SCSI_STATUS_CMD_TERMINATED 134 
#define  SCSI_STATUS_INTERMED 133 
#define  SCSI_STATUS_INTERMED_COND_MET 132 
#define  SCSI_STATUS_OK 131 
#define  SCSI_STATUS_QUEUE_FULL 130 
#define  SCSI_STATUS_RESERV_CONFLICT 129 
#define  SCSI_STATUS_TASK_ABORTED 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

const char *
scsi_status_string(struct ccb_scsiio *csio)
{
	switch(csio->scsi_status) {
	case SCSI_STATUS_OK:
		return("OK");
	case SCSI_STATUS_CHECK_COND:
		return("Check Condition");
	case SCSI_STATUS_BUSY:
		return("Busy");
	case SCSI_STATUS_INTERMED:
		return("Intermediate");
	case SCSI_STATUS_INTERMED_COND_MET:
		return("Intermediate-Condition Met");
	case SCSI_STATUS_RESERV_CONFLICT:
		return("Reservation Conflict");
	case SCSI_STATUS_CMD_TERMINATED:
		return("Command Terminated");
	case SCSI_STATUS_QUEUE_FULL:
		return("Queue Full");
	case SCSI_STATUS_ACA_ACTIVE:
		return("ACA Active");
	case SCSI_STATUS_TASK_ABORTED:
		return("Task Aborted");
	default: {
		static char unkstr[64];
		snprintf(unkstr, sizeof(unkstr), "Unknown %#x",
			 csio->scsi_status);
		return(unkstr);
	}
	}
}