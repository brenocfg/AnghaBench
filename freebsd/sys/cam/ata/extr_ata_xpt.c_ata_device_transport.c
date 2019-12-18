#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct scsi_inquiry_data {int dummy; } ;
struct TYPE_10__ {int atapi; int /*<<< orphan*/  valid; } ;
struct TYPE_9__ {int atapi; int /*<<< orphan*/  valid; } ;
struct TYPE_11__ {scalar_t__ valid; TYPE_4__ sata; TYPE_3__ ata; } ;
struct TYPE_7__ {scalar_t__ valid; } ;
struct TYPE_12__ {int /*<<< orphan*/  func_code; } ;
struct ccb_trans_settings {scalar_t__ protocol; void* protocol_version; TYPE_5__ xport_specific; TYPE_1__ proto_specific; void* transport_version; int /*<<< orphan*/  transport; int /*<<< orphan*/  type; TYPE_6__ ccb_h; } ;
struct ccb_pathinq {void* protocol_version; void* transport_version; int /*<<< orphan*/  transport; } ;
struct cam_path {TYPE_2__* device; } ;
struct ata_params {int config; int /*<<< orphan*/  version_major; } ;
struct TYPE_8__ {int flags; scalar_t__ protocol; void* protocol_version; int /*<<< orphan*/  transport; void* transport_version; struct ata_params ident_data; struct scsi_inquiry_data inq_data; } ;

/* Variables and functions */
 int ATA_PROTO_ATAPI_12 ; 
 int ATA_PROTO_ATAPI_16 ; 
 int ATA_PROTO_CFA ; 
 int ATA_PROTO_MASK ; 
 int CAM_DEV_IDENTIFY_DATA_VALID ; 
 int CAM_DEV_INQUIRY_DATA_VALID ; 
 int /*<<< orphan*/  CAM_PRIORITY_NONE ; 
 int /*<<< orphan*/  CTS_ATA_VALID_ATAPI ; 
 int /*<<< orphan*/  CTS_SATA_VALID_ATAPI ; 
 int /*<<< orphan*/  CTS_TYPE_CURRENT_SETTINGS ; 
 scalar_t__ PROTO_ATA ; 
 scalar_t__ PROTO_SCSI ; 
 void* SID_ANSI_REV (struct scsi_inquiry_data*) ; 
 int /*<<< orphan*/  XPORT_ATA ; 
 int /*<<< orphan*/  XPT_SET_TRAN_SETTINGS ; 
 void* ata_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_path_inq (struct ccb_pathinq*,struct cam_path*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_6__*,struct cam_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ata_device_transport(struct cam_path *path)
{
	struct ccb_pathinq cpi;
	struct ccb_trans_settings cts;
	struct scsi_inquiry_data *inq_buf = NULL;
	struct ata_params *ident_buf = NULL;

	/* Get transport information from the SIM */
	xpt_path_inq(&cpi, path);

	path->device->transport = cpi.transport;
	if ((path->device->flags & CAM_DEV_INQUIRY_DATA_VALID) != 0)
		inq_buf = &path->device->inq_data;
	if ((path->device->flags & CAM_DEV_IDENTIFY_DATA_VALID) != 0)
		ident_buf = &path->device->ident_data;
	if (path->device->protocol == PROTO_ATA) {
		path->device->protocol_version = ident_buf ?
		    ata_version(ident_buf->version_major) : cpi.protocol_version;
	} else if (path->device->protocol == PROTO_SCSI) {
		path->device->protocol_version = inq_buf ?
		    SID_ANSI_REV(inq_buf) : cpi.protocol_version;
	}
	path->device->transport_version = ident_buf ?
	    ata_version(ident_buf->version_major) : cpi.transport_version;

	/* Tell the controller what we think */
	xpt_setup_ccb(&cts.ccb_h, path, CAM_PRIORITY_NONE);
	cts.ccb_h.func_code = XPT_SET_TRAN_SETTINGS;
	cts.type = CTS_TYPE_CURRENT_SETTINGS;
	cts.transport = path->device->transport;
	cts.transport_version = path->device->transport_version;
	cts.protocol = path->device->protocol;
	cts.protocol_version = path->device->protocol_version;
	cts.proto_specific.valid = 0;
	if (ident_buf) {
		if (path->device->transport == XPORT_ATA) {
			cts.xport_specific.ata.atapi =
			    (ident_buf->config == ATA_PROTO_CFA) ? 0 :
			    ((ident_buf->config & ATA_PROTO_MASK) == ATA_PROTO_ATAPI_16) ? 16 :
			    ((ident_buf->config & ATA_PROTO_MASK) == ATA_PROTO_ATAPI_12) ? 12 : 0;
			cts.xport_specific.ata.valid = CTS_ATA_VALID_ATAPI;
		} else {
			cts.xport_specific.sata.atapi =
			    (ident_buf->config == ATA_PROTO_CFA) ? 0 :
			    ((ident_buf->config & ATA_PROTO_MASK) == ATA_PROTO_ATAPI_16) ? 16 :
			    ((ident_buf->config & ATA_PROTO_MASK) == ATA_PROTO_ATAPI_12) ? 12 : 0;
			cts.xport_specific.sata.valid = CTS_SATA_VALID_ATAPI;
		}
	} else
		cts.xport_specific.valid = 0;
	xpt_action((union ccb *)&cts);
}