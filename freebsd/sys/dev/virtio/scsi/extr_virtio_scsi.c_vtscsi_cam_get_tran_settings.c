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
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct ccb_trans_settings_scsi {int /*<<< orphan*/  flags; int /*<<< orphan*/  valid; } ;
struct TYPE_4__ {struct ccb_trans_settings_scsi scsi; } ;
struct ccb_trans_settings {scalar_t__ transport_version; int /*<<< orphan*/  transport; int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  protocol; TYPE_2__ proto_specific; } ;
union ccb {TYPE_1__ ccb_h; struct ccb_trans_settings cts; } ;
struct vtscsi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CTS_SCSI_FLAGS_TAG_ENB ; 
 int /*<<< orphan*/  CTS_SCSI_VALID_TQ ; 
 int /*<<< orphan*/  PROTO_SCSI ; 
 int /*<<< orphan*/  SCSI_REV_SPC3 ; 
 int /*<<< orphan*/  XPORT_SAS ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
vtscsi_cam_get_tran_settings(struct vtscsi_softc *sc, union ccb *ccb)
{
	struct ccb_trans_settings *cts;
	struct ccb_trans_settings_scsi *scsi;

	cts = &ccb->cts;
	scsi = &cts->proto_specific.scsi;

	cts->protocol = PROTO_SCSI;
	cts->protocol_version = SCSI_REV_SPC3;
	cts->transport = XPORT_SAS;
	cts->transport_version = 0;

	scsi->valid = CTS_SCSI_VALID_TQ;
	scsi->flags = CTS_SCSI_FLAGS_TAG_ENB;

	ccb->ccb_h.status = CAM_REQ_CMP;
	xpt_done(ccb);
}