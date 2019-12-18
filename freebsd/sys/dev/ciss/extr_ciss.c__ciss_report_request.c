#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ciss_request {int /*<<< orphan*/  cr_sc; struct ciss_command* cr_cc; } ;
struct TYPE_7__ {int /*<<< orphan*/  offense_value; int /*<<< orphan*/  offense_offset; int /*<<< orphan*/  offense_size; } ;
struct TYPE_8__ {TYPE_3__ invalid_command; } ;
struct ciss_error_info {int command_status; int scsi_status; TYPE_4__ additional_error_info; } ;
struct TYPE_6__ {int host_tag; } ;
struct TYPE_5__ {scalar_t__* cdb; } ;
struct ciss_command {TYPE_2__ header; TYPE_1__ cdb; int /*<<< orphan*/ * sg; } ;

/* Variables and functions */
 int CISS_CMD_STATUS_DATA_OVERRUN ; 
 int CISS_CMD_STATUS_DATA_UNDERRUN ; 
 int CISS_CMD_STATUS_INVALID_COMMAND ; 
 int CISS_CMD_STATUS_SUCCESS ; 
 int CISS_CMD_STATUS_TARGET_STATUS ; 
 int CISS_HDR_HOST_TAG_ERROR ; 
 scalar_t__ CISS_OPCODE_REPORT_LOGICAL_LUNS ; 
 scalar_t__ CISS_OPCODE_REPORT_PHYSICAL_LUNS ; 
 scalar_t__ INQUIRY ; 
 int SCSI_STATUS_OK ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  ciss_name_command_status (int) ; 
 int /*<<< orphan*/  ciss_print_request (struct ciss_request*) ; 
 int /*<<< orphan*/  ciss_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  debug (int,char*) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static int
_ciss_report_request(struct ciss_request *cr, int *command_status, int *scsi_status, const char *func)
{
    struct ciss_command		*cc;
    struct ciss_error_info	*ce;

    debug_called(2);

    cc = cr->cr_cc;
    ce = (struct ciss_error_info *)&(cc->sg[0]);

    /*
     * We don't consider data under/overrun an error for the Report
     * Logical/Physical LUNs commands.
     */
    if ((cc->header.host_tag & CISS_HDR_HOST_TAG_ERROR) &&
	((ce->command_status == CISS_CMD_STATUS_DATA_OVERRUN) ||
	 (ce->command_status == CISS_CMD_STATUS_DATA_UNDERRUN)) &&
	((cc->cdb.cdb[0] == CISS_OPCODE_REPORT_LOGICAL_LUNS) ||
	 (cc->cdb.cdb[0] == CISS_OPCODE_REPORT_PHYSICAL_LUNS) ||
	 (cc->cdb.cdb[0] == INQUIRY))) {
	cc->header.host_tag &= ~CISS_HDR_HOST_TAG_ERROR;
	debug(2, "ignoring irrelevant under/overrun error");
    }

    /*
     * Check the command's error bit, if clear, there's no status and
     * everything is OK.
     */
    if (!(cc->header.host_tag & CISS_HDR_HOST_TAG_ERROR)) {
	if (scsi_status != NULL)
	    *scsi_status = SCSI_STATUS_OK;
	if (command_status != NULL)
	    *command_status = CISS_CMD_STATUS_SUCCESS;
	return(0);
    } else {
	if (command_status != NULL)
	    *command_status = ce->command_status;
	if (scsi_status != NULL) {
	    if (ce->command_status == CISS_CMD_STATUS_TARGET_STATUS) {
		*scsi_status = ce->scsi_status;
	    } else {
		*scsi_status = -1;
	    }
	}
	if (bootverbose)
	    ciss_printf(cr->cr_sc, "command status 0x%x (%s) scsi status 0x%x\n",
			ce->command_status, ciss_name_command_status(ce->command_status),
			ce->scsi_status);
	if (ce->command_status == CISS_CMD_STATUS_INVALID_COMMAND) {
	    ciss_printf(cr->cr_sc, "invalid command, offense size %d at %d, value 0x%x, function %s\n",
			ce->additional_error_info.invalid_command.offense_size,
			ce->additional_error_info.invalid_command.offense_offset,
			ce->additional_error_info.invalid_command.offense_value,
			func);
	}
    }
#if 0
    ciss_print_request(cr);
#endif
    return(1);
}