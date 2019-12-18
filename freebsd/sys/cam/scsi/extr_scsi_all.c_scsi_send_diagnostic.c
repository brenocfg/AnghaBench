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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct scsi_send_diag {int byte2; int /*<<< orphan*/  length; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  SEND_DIAGNOSTIC ; 
 int SSD_DEVOFFL ; 
 int SSD_PF ; 
 int SSD_SELFTEST ; 
 int SSD_SELF_TEST_CODE_MASK ; 
 int SSD_SELF_TEST_CODE_NONE ; 
 int SSD_SELF_TEST_CODE_SHIFT ; 
 int SSD_UNITOFFL ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct scsi_send_diag*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_ulto2b (scalar_t__,int /*<<< orphan*/ ) ; 

void
scsi_send_diagnostic(struct ccb_scsiio *csio, u_int32_t retries,
		     void (*cbfcnp)(struct cam_periph *, union ccb *),
		     uint8_t tag_action, int unit_offline, int device_offline,
		     int self_test, int page_format, int self_test_code,
		     uint8_t *data_ptr, uint16_t param_list_length,
		     uint8_t sense_len, uint32_t timeout)
{
	struct scsi_send_diag *scsi_cmd;

	scsi_cmd = (struct scsi_send_diag *)&csio->cdb_io.cdb_bytes;
	memset(scsi_cmd, 0, sizeof(*scsi_cmd));
	scsi_cmd->opcode = SEND_DIAGNOSTIC;

	/*
	 * The default self-test mode control and specific test
	 * control are mutually exclusive.
	 */
	if (self_test)
		self_test_code = SSD_SELF_TEST_CODE_NONE;

	scsi_cmd->byte2 = ((self_test_code << SSD_SELF_TEST_CODE_SHIFT)
			 & SSD_SELF_TEST_CODE_MASK)
			| (unit_offline   ? SSD_UNITOFFL : 0)
			| (device_offline ? SSD_DEVOFFL  : 0)
			| (self_test      ? SSD_SELFTEST : 0)
			| (page_format    ? SSD_PF       : 0);
	scsi_ulto2b(param_list_length, scsi_cmd->length);

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/param_list_length ? CAM_DIR_OUT : CAM_DIR_NONE,
		      tag_action,
		      data_ptr,
		      param_list_length,
		      sense_len,
		      sizeof(*scsi_cmd),
		      timeout);
}