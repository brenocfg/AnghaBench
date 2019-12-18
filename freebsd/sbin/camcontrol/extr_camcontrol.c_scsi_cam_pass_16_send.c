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
struct TYPE_8__ {int status; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  timeout; } ;
struct TYPE_5__ {scalar_t__ cdb_bytes; } ;
struct TYPE_7__ {TYPE_2__ ccb_h; TYPE_1__ cdb_io; } ;
union ccb {TYPE_4__ ccb_h; TYPE_3__ csio; } ;
struct cam_device {int dummy; } ;
struct ata_pass_16 {int flags; int /*<<< orphan*/  features; int /*<<< orphan*/  control; int /*<<< orphan*/  command; } ;
struct ata_cmd {int /*<<< orphan*/  features; int /*<<< orphan*/  control; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int AP_FLAG_CHK_COND ; 
 int CAM_ARG_ERR_RECOVER ; 
 int CAM_ARG_VERBOSE ; 
 int /*<<< orphan*/  CAM_DEV_QFRZDIS ; 
 int /*<<< orphan*/  CAM_EPF_ALL ; 
 int /*<<< orphan*/  CAM_ESF_ALL ; 
 int /*<<< orphan*/  CAM_PASS_ERR_RECOVER ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 int arglist ; 
 int /*<<< orphan*/  ata_op_string (struct ata_cmd*) ; 
 int /*<<< orphan*/  cam_error_print (struct cam_device*,union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cam_send_ccb (struct cam_device*,union ccb*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
scsi_cam_pass_16_send(struct cam_device *device, union ccb *ccb)
{
	struct ata_pass_16 *ata_pass_16;
	struct ata_cmd ata_cmd;

	ata_pass_16 = (struct ata_pass_16 *)ccb->csio.cdb_io.cdb_bytes;
	ata_cmd.command = ata_pass_16->command;
	ata_cmd.control = ata_pass_16->control;
	ata_cmd.features = ata_pass_16->features;

	if (arglist & CAM_ARG_VERBOSE) {
		warnx("sending ATA %s via pass_16 with timeout of %u msecs",
		      ata_op_string(&ata_cmd),
		      ccb->csio.ccb_h.timeout);
	}

	/* Disable freezing the device queue */
	ccb->ccb_h.flags |= CAM_DEV_QFRZDIS;

	if (arglist & CAM_ARG_ERR_RECOVER)
		ccb->ccb_h.flags |= CAM_PASS_ERR_RECOVER;

	if (cam_send_ccb(device, ccb) < 0) {
		warn("error sending ATA %s via pass_16", ata_op_string(&ata_cmd));
		return (1);
	}

	/*
	 * Consider any non-CAM_REQ_CMP status as error and report it here,
	 * unless caller set AP_FLAG_CHK_COND, in which case it is reponsible.
	 */
	if (!(ata_pass_16->flags & AP_FLAG_CHK_COND) &&
	    (ccb->ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP) {
		warnx("ATA %s via pass_16 failed", ata_op_string(&ata_cmd));
		if (arglist & CAM_ARG_VERBOSE) {
			cam_error_print(device, ccb, CAM_ESF_ALL,
					CAM_EPF_ALL, stderr);
		}
		return (1);
	}

	return (0);
}