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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct ccb_pathinq {int version_num; int hba_misc; int base_transfer_speed; int maxio; int /*<<< orphan*/  hba_subdevice; int /*<<< orphan*/  hba_subvendor; int /*<<< orphan*/  hba_device; int /*<<< orphan*/  hba_vendor; scalar_t__ transport_version; int /*<<< orphan*/  transport; int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  protocol; int /*<<< orphan*/  bus_id; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  hba_vid; int /*<<< orphan*/  sim_vid; int /*<<< orphan*/  initiator_id; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  max_target; scalar_t__ hba_eng_cnt; scalar_t__ target_sprt; int /*<<< orphan*/  hba_inquiry; } ;
union ccb {TYPE_1__ ccb_h; struct ccb_pathinq cpi; } ;
struct vtscsi_softc {int vtscsi_max_nsegs; int /*<<< orphan*/  vtscsi_max_lun; int /*<<< orphan*/  vtscsi_max_target; int /*<<< orphan*/  vtscsi_dev; } ;
struct cam_sim {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  DEV_IDLEN ; 
 int /*<<< orphan*/  HBA_IDLEN ; 
 int PAGE_SIZE ; 
 int PIM_NOBUSRESET ; 
 int PIM_SEQSCAN ; 
 int PIM_UNMAPPED ; 
 int /*<<< orphan*/  PI_TAG_ABLE ; 
 int /*<<< orphan*/  PROTO_SCSI ; 
 int /*<<< orphan*/  SCSI_REV_SPC3 ; 
 int /*<<< orphan*/  SIM_IDLEN ; 
 int /*<<< orphan*/  VTSCSI_INITIATOR_ID ; 
 int VTSCSI_MIN_SEGMENTS ; 
 int /*<<< orphan*/  VTSCSI_TRACE ; 
 int /*<<< orphan*/  XPORT_SAS ; 
 int /*<<< orphan*/  cam_sim_bus (struct cam_sim*) ; 
 char* cam_sim_name (struct cam_sim*) ; 
 int /*<<< orphan*/  cam_sim_unit (struct cam_sim*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_get_subdevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_get_subvendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_get_vendor (int /*<<< orphan*/ ) ; 
 scalar_t__ vtscsi_bus_reset_disable ; 
 int /*<<< orphan*/  vtscsi_dprintf (struct vtscsi_softc*,int /*<<< orphan*/ ,char*,struct cam_sim*,union ccb*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
vtscsi_cam_path_inquiry(struct vtscsi_softc *sc, struct cam_sim *sim,
    union ccb *ccb)
{
	device_t dev;
	struct ccb_pathinq *cpi;

	dev = sc->vtscsi_dev;
	cpi = &ccb->cpi;

	vtscsi_dprintf(sc, VTSCSI_TRACE, "sim=%p ccb=%p\n", sim, ccb);

	cpi->version_num = 1;
	cpi->hba_inquiry = PI_TAG_ABLE;
	cpi->target_sprt = 0;
	cpi->hba_misc = PIM_SEQSCAN | PIM_UNMAPPED;
	if (vtscsi_bus_reset_disable != 0)
		cpi->hba_misc |= PIM_NOBUSRESET;
	cpi->hba_eng_cnt = 0;

	cpi->max_target = sc->vtscsi_max_target;
	cpi->max_lun = sc->vtscsi_max_lun;
	cpi->initiator_id = VTSCSI_INITIATOR_ID;

	strlcpy(cpi->sim_vid, "FreeBSD", SIM_IDLEN);
	strlcpy(cpi->hba_vid, "VirtIO", HBA_IDLEN);
	strlcpy(cpi->dev_name, cam_sim_name(sim), DEV_IDLEN);

	cpi->unit_number = cam_sim_unit(sim);
	cpi->bus_id = cam_sim_bus(sim);

	cpi->base_transfer_speed = 300000;

	cpi->protocol = PROTO_SCSI;
	cpi->protocol_version = SCSI_REV_SPC3;
	cpi->transport = XPORT_SAS;
	cpi->transport_version = 0;

	cpi->maxio = (sc->vtscsi_max_nsegs - VTSCSI_MIN_SEGMENTS - 1) *
	    PAGE_SIZE;

	cpi->hba_vendor = virtio_get_vendor(dev);
	cpi->hba_device = virtio_get_device(dev);
	cpi->hba_subvendor = virtio_get_subvendor(dev);
	cpi->hba_subdevice = virtio_get_subdevice(dev);

	ccb->ccb_h.status = CAM_REQ_CMP;
	xpt_done(ccb);
}