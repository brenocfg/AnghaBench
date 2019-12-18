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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct scsi_write_buffer {int dummy; } ;
struct scsi_report_supported_opcodes_timeout {int /*<<< orphan*/  recommended_time; } ;
struct scsi_report_supported_opcodes_one {int support; int /*<<< orphan*/  cdb_length; } ;
struct fw_vendor {scalar_t__ timeout_type; int timeout_ms; } ;
struct cam_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ FW_TIMEOUT_DEV_REPORTED ; 
 scalar_t__ FW_TIMEOUT_NO_PROBE ; 
 scalar_t__ FW_TIMEOUT_USER_SPEC ; 
 int RSO_ONE_SUP_MASK ; 
 int RSO_ONE_SUP_NOT_SUP ; 
 int /*<<< orphan*/  WRITE_BUFFER ; 
 int scsi_2btoul (int /*<<< orphan*/ ) ; 
 int scsi_4btoul (int /*<<< orphan*/ ) ; 
 int scsigetopcodes (struct cam_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
fw_get_timeout(struct cam_device *cam_dev, struct fw_vendor *vp,
	       int task_attr, int retry_count, int timeout)
{
	struct scsi_report_supported_opcodes_one *one;
	struct scsi_report_supported_opcodes_timeout *td;
	uint8_t *buf = NULL;
	uint32_t fill_len = 0, cdb_len = 0, rec_timeout = 0;
	int retval = 0;

	/*
	 * If the user has specified a timeout on the command line, we let
	 * him override any default or probed value.
	 */
	if (timeout != 0) {
		vp->timeout_type = FW_TIMEOUT_USER_SPEC;
		vp->timeout_ms = timeout;
		goto bailout;
	}

	/*
	 * Check to see whether we should probe for a timeout for this
	 * device.
	 */
	if (vp->timeout_type == FW_TIMEOUT_NO_PROBE)
		goto bailout;

	retval = scsigetopcodes(/*device*/ cam_dev,
				/*opcode_set*/ 1,
				/*opcode*/ WRITE_BUFFER,
				/*show_sa_errors*/ 1,
				/*sa_set*/ 0,
				/*service_action*/ 0,
				/*timeout_desc*/ 1,
				/*task_attr*/ task_attr,
				/*retry_count*/ retry_count,
				/*timeout*/ 10000,
				/*verbose*/ 0,
				/*fill_len*/ &fill_len,
				/*data_ptr*/ &buf);
	/*
	 * It isn't an error if we can't get a timeout descriptor.  We just
	 * continue on with the default timeout.
	 */
	if (retval != 0) {
		retval = 0;
		goto bailout;
	}

	/*
	 * Even if the drive didn't return a SCSI error, if we don't have
	 * enough data to contain the one opcode descriptor, the CDB
	 * structure and a timeout descriptor, we don't have the timeout
	 * value we're looking for.  So we'll just fall back to the
	 * default value.
	 */
	if (fill_len < (sizeof(*one) + sizeof(struct scsi_write_buffer) +
	    sizeof(*td)))
		goto bailout;

	one = (struct scsi_report_supported_opcodes_one *)buf;

	/*
	 * If the drive claims to not support the WRITE BUFFER command...
	 * fall back to the default timeout value and let things fail on
	 * the actual firmware download.
	 */
	if ((one->support & RSO_ONE_SUP_MASK) == RSO_ONE_SUP_NOT_SUP)
		goto bailout;

	cdb_len = scsi_2btoul(one->cdb_length);
	td = (struct scsi_report_supported_opcodes_timeout *)
	    &buf[sizeof(*one) + cdb_len];

	rec_timeout = scsi_4btoul(td->recommended_time);
	/*
	 * If the recommended timeout is 0, then the device has probably
	 * returned a bogus value.
	 */
	if (rec_timeout == 0)
		goto bailout;

	/* CAM timeouts are in ms */
	rec_timeout *= 1000;

	vp->timeout_ms = rec_timeout;
	vp->timeout_type = FW_TIMEOUT_DEV_REPORTED;

bailout:
	return (retval);
}