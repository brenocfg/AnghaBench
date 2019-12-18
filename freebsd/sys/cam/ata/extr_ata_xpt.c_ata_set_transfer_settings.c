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
typedef  union ccb {int dummy; } ccb ;
struct scsi_inquiry_data {int dummy; } ;
struct ccb_trans_settings_scsi {int flags; int valid; } ;
struct ccb_trans_settings_ata {int flags; int valid; } ;
struct TYPE_4__ {struct ccb_trans_settings_scsi scsi; struct ccb_trans_settings_ata ata; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct ccb_trans_settings {scalar_t__ protocol; scalar_t__ protocol_version; scalar_t__ transport; scalar_t__ transport_version; scalar_t__ type; TYPE_2__ proto_specific; TYPE_1__ ccb_h; } ;
struct ccb_pathinq {int hba_inquiry; } ;
struct cam_path {struct cam_ed* device; } ;
struct ata_params {int satacapabilities; } ;
struct cam_ed {scalar_t__ protocol; scalar_t__ protocol_version; scalar_t__ transport; scalar_t__ transport_version; int queue_flags; scalar_t__ mintags; int flags; int inq_flags; int /*<<< orphan*/  tag_delay_count; struct scsi_inquiry_data inq_data; struct ata_params ident_data; } ;

/* Variables and functions */
 int ATA_SUPPORT_NCQ ; 
 int CAM_DEV_TAG_AFTER_COUNT ; 
 int /*<<< orphan*/  CAM_PATH_INVALID ; 
 int /*<<< orphan*/  CAM_TAG_DELAY_COUNT ; 
 int CTS_ATA_FLAGS_TAG_ENB ; 
 int CTS_ATA_VALID_TQ ; 
 int CTS_SCSI_FLAGS_TAG_ENB ; 
 int CTS_SCSI_VALID_TQ ; 
 scalar_t__ CTS_TYPE_CURRENT_SETTINGS ; 
 int FALSE ; 
 scalar_t__ INQ_DATA_TQ_ENABLED (struct scsi_inquiry_data*) ; 
 int PI_TAG_ABLE ; 
 scalar_t__ PROTO_ATA ; 
 scalar_t__ PROTO_SCSI ; 
 scalar_t__ PROTO_UNKNOWN ; 
 scalar_t__ PROTO_UNSPECIFIED ; 
 scalar_t__ PROTO_VERSION_UNKNOWN ; 
 scalar_t__ PROTO_VERSION_UNSPECIFIED ; 
 int SCP_QUEUE_DQUE ; 
 int SID_CmdQue ; 
 scalar_t__ XPORT_UNKNOWN ; 
 scalar_t__ XPORT_UNSPECIFIED ; 
 scalar_t__ XPORT_VERSION_UNKNOWN ; 
 scalar_t__ XPORT_VERSION_UNSPECIFIED ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  xpt_action_default (union ccb*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_path_inq (struct ccb_pathinq*,struct cam_path*) ; 
 int /*<<< orphan*/  xpt_print (struct cam_path*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xpt_stop_tags (struct cam_path*) ; 

__attribute__((used)) static void
ata_set_transfer_settings(struct ccb_trans_settings *cts, struct cam_path *path,
			   int async_update)
{
	struct	ccb_pathinq cpi;
	struct	ccb_trans_settings_ata *ata;
	struct	ccb_trans_settings_scsi *scsi;
	struct	ata_params *ident_data;
	struct	scsi_inquiry_data *inq_data;
	struct	cam_ed *device;

	if (path == NULL || (device = path->device) == NULL) {
		cts->ccb_h.status = CAM_PATH_INVALID;
		xpt_done((union ccb *)cts);
		return;
	}

	if (cts->protocol == PROTO_UNKNOWN
	 || cts->protocol == PROTO_UNSPECIFIED) {
		cts->protocol = device->protocol;
		cts->protocol_version = device->protocol_version;
	}

	if (cts->protocol_version == PROTO_VERSION_UNKNOWN
	 || cts->protocol_version == PROTO_VERSION_UNSPECIFIED)
		cts->protocol_version = device->protocol_version;

	if (cts->protocol != device->protocol) {
		xpt_print(path, "Uninitialized Protocol %x:%x?\n",
		       cts->protocol, device->protocol);
		cts->protocol = device->protocol;
	}

	if (cts->protocol_version > device->protocol_version) {
		if (bootverbose) {
			xpt_print(path, "Down reving Protocol "
			    "Version from %d to %d?\n", cts->protocol_version,
			    device->protocol_version);
		}
		cts->protocol_version = device->protocol_version;
	}

	if (cts->transport == XPORT_UNKNOWN
	 || cts->transport == XPORT_UNSPECIFIED) {
		cts->transport = device->transport;
		cts->transport_version = device->transport_version;
	}

	if (cts->transport_version == XPORT_VERSION_UNKNOWN
	 || cts->transport_version == XPORT_VERSION_UNSPECIFIED)
		cts->transport_version = device->transport_version;

	if (cts->transport != device->transport) {
		xpt_print(path, "Uninitialized Transport %x:%x?\n",
		    cts->transport, device->transport);
		cts->transport = device->transport;
	}

	if (cts->transport_version > device->transport_version) {
		if (bootverbose) {
			xpt_print(path, "Down reving Transport "
			    "Version from %d to %d?\n", cts->transport_version,
			    device->transport_version);
		}
		cts->transport_version = device->transport_version;
	}

	ident_data = &device->ident_data;
	inq_data = &device->inq_data;
	if (cts->protocol == PROTO_ATA)
		ata = &cts->proto_specific.ata;
	else
		ata = NULL;
	if (cts->protocol == PROTO_SCSI)
		scsi = &cts->proto_specific.scsi;
	else
		scsi = NULL;
	xpt_path_inq(&cpi, path);

	/* Sanity checking */
	if ((cpi.hba_inquiry & PI_TAG_ABLE) == 0
	 || (ata && (ident_data->satacapabilities & ATA_SUPPORT_NCQ) == 0)
	 || (scsi && (INQ_DATA_TQ_ENABLED(inq_data)) == 0)
	 || (device->queue_flags & SCP_QUEUE_DQUE) != 0
	 || (device->mintags == 0)) {
		/*
		 * Can't tag on hardware that doesn't support tags,
		 * doesn't have it enabled, or has broken tag support.
		 */
		if (ata)
			ata->flags &= ~CTS_ATA_FLAGS_TAG_ENB;
		if (scsi)
			scsi->flags &= ~CTS_SCSI_FLAGS_TAG_ENB;
	}

	/* Start/stop tags use. */
	if (cts->type == CTS_TYPE_CURRENT_SETTINGS &&
	    ((ata && (ata->valid & CTS_ATA_VALID_TQ) != 0) ||
	     (scsi && (scsi->valid & CTS_SCSI_VALID_TQ) != 0))) {
		int nowt, newt = 0;

		nowt = ((device->flags & CAM_DEV_TAG_AFTER_COUNT) != 0 ||
			(device->inq_flags & SID_CmdQue) != 0);
		if (ata)
			newt = (ata->flags & CTS_ATA_FLAGS_TAG_ENB) != 0;
		if (scsi)
			newt = (scsi->flags & CTS_SCSI_FLAGS_TAG_ENB) != 0;

		if (newt && !nowt) {
			/*
			 * Delay change to use tags until after a
			 * few commands have gone to this device so
			 * the controller has time to perform transfer
			 * negotiations without tagged messages getting
			 * in the way.
			 */
			device->tag_delay_count = CAM_TAG_DELAY_COUNT;
			device->flags |= CAM_DEV_TAG_AFTER_COUNT;
		} else if (nowt && !newt)
			xpt_stop_tags(path);
	}

	if (async_update == FALSE)
		xpt_action_default((union ccb *)cts);
}