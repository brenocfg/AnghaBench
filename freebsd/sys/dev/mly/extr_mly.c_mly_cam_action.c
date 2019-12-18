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
struct TYPE_8__ {int func_code; void* status; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; } ;
struct TYPE_11__ {int target_id; void* status; } ;
struct ccb_trans_settings_spi {int valid; int sync_period; int /*<<< orphan*/  flags; int /*<<< orphan*/  bus_width; } ;
struct TYPE_10__ {struct ccb_trans_settings_spi spi; } ;
struct ccb_trans_settings_scsi {int /*<<< orphan*/  valid; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {struct ccb_trans_settings_scsi scsi; } ;
struct ccb_trans_settings {int transport_version; TYPE_5__ ccb_h; void* transport; void* protocol_version; void* protocol; TYPE_4__ xport_specific; TYPE_3__ proto_specific; } ;
struct ccb_pathinq {int version_num; int base_transfer_speed; int transport_version; void* protocol_version; void* protocol; void* transport; void* bus_id; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  hba_vid; int /*<<< orphan*/  sim_vid; int /*<<< orphan*/  initiator_id; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  max_target; int /*<<< orphan*/  hba_misc; int /*<<< orphan*/  target_sprt; int /*<<< orphan*/  hba_inquiry; } ;
struct ccb_calc_geometry {int heads; int secs_per_track; int cylinders; int volume_size; } ;
union ccb {TYPE_2__ ccb_h; struct ccb_trans_settings cts; struct ccb_pathinq cpi; struct ccb_calc_geometry ccg; int /*<<< orphan*/  csio; } ;
typedef  int u_int32_t ;
struct mly_softc {TYPE_6__** mly_btl; TYPE_1__* mly_controllerparam; } ;
struct ccb_scsiio {int dummy; } ;
struct cam_sim {int dummy; } ;
struct TYPE_12__ {int mb_flags; int mb_speed; int /*<<< orphan*/  mb_width; } ;
struct TYPE_7__ {int /*<<< orphan*/  initiator_id; int /*<<< orphan*/  bios_geometry; } ;

/* Variables and functions */
 void* CAM_REQ_CMP ; 
 void* CAM_REQ_CMP_ERR ; 
 void* CAM_REQ_INVALID ; 
 int /*<<< orphan*/  CTS_SCSI_FLAGS_TAG_ENB ; 
 int /*<<< orphan*/  CTS_SCSI_VALID_TQ ; 
 int /*<<< orphan*/  CTS_SPI_FLAGS_DISC_ENB ; 
 int CTS_SPI_VALID_BUS_WIDTH ; 
 int CTS_SPI_VALID_DISC ; 
 int CTS_SPI_VALID_SYNC_RATE ; 
 int /*<<< orphan*/  DEV_IDLEN ; 
 int /*<<< orphan*/  HBA_IDLEN ; 
 int /*<<< orphan*/  MLY_ASSERT_LOCKED (struct mly_softc*) ; 
 int /*<<< orphan*/  MLY_BIOSGEOM_8G ; 
 int MLY_BTL_LOGICAL ; 
 int MLY_BTL_PHYSICAL ; 
 int /*<<< orphan*/  MLY_MAX_LUNS ; 
 int /*<<< orphan*/  MLY_MAX_TARGETS ; 
 int /*<<< orphan*/  MSG_EXT_WDTR_BUS_16_BIT ; 
 int /*<<< orphan*/  MSG_EXT_WDTR_BUS_32_BIT ; 
 int /*<<< orphan*/  MSG_EXT_WDTR_BUS_8_BIT ; 
 int /*<<< orphan*/  PI_TAG_ABLE ; 
 void* PROTO_SCSI ; 
 void* SCSI_REV_2 ; 
 int /*<<< orphan*/  SIM_IDLEN ; 
 void* XPORT_SPI ; 
#define  XPT_CALC_GEOMETRY 131 
#define  XPT_GET_TRAN_SETTINGS 130 
#define  XPT_PATH_INQ 129 
#define  XPT_SCSI_IO 128 
 void* cam_sim_bus (struct cam_sim*) ; 
 char* cam_sim_name (struct cam_sim*) ; 
 struct mly_softc* cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  cam_sim_unit (struct cam_sim*) ; 
 int /*<<< orphan*/  debug (int,char*,int,...) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  mly_cam_action_io (struct cam_sim*,struct ccb_scsiio*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
mly_cam_action(struct cam_sim *sim, union ccb *ccb)
{
    struct mly_softc	*sc = cam_sim_softc(sim);

    debug_called(2);
    MLY_ASSERT_LOCKED(sc);

    switch (ccb->ccb_h.func_code) {

	/* perform SCSI I/O */
    case XPT_SCSI_IO:
	if (!mly_cam_action_io(sim, (struct ccb_scsiio *)&ccb->csio))
	    return;
	break;

	/* perform geometry calculations */
    case XPT_CALC_GEOMETRY:
    {
	struct ccb_calc_geometry	*ccg = &ccb->ccg;
        u_int32_t			secs_per_cylinder;

	debug(2, "XPT_CALC_GEOMETRY %d:%d:%d", cam_sim_bus(sim), ccb->ccb_h.target_id, ccb->ccb_h.target_lun);

	if (sc->mly_controllerparam->bios_geometry == MLY_BIOSGEOM_8G) {
	    ccg->heads = 255;
            ccg->secs_per_track = 63;
	} else {				/* MLY_BIOSGEOM_2G */
	    ccg->heads = 128;
            ccg->secs_per_track = 32;
	}
	secs_per_cylinder = ccg->heads * ccg->secs_per_track;
        ccg->cylinders = ccg->volume_size / secs_per_cylinder;
        ccb->ccb_h.status = CAM_REQ_CMP;
        break;
    }

	/* handle path attribute inquiry */
    case XPT_PATH_INQ:
    {
	struct ccb_pathinq	*cpi = &ccb->cpi;

	debug(2, "XPT_PATH_INQ %d:%d:%d", cam_sim_bus(sim), ccb->ccb_h.target_id, ccb->ccb_h.target_lun);

	cpi->version_num = 1;
	cpi->hba_inquiry = PI_TAG_ABLE;		/* XXX extra flags for physical channels? */
	cpi->target_sprt = 0;
	cpi->hba_misc = 0;
	cpi->max_target = MLY_MAX_TARGETS - 1;
	cpi->max_lun = MLY_MAX_LUNS - 1;
	cpi->initiator_id = sc->mly_controllerparam->initiator_id;
	strlcpy(cpi->sim_vid, "FreeBSD", SIM_IDLEN);
	strlcpy(cpi->hba_vid, "Mylex", HBA_IDLEN);
	strlcpy(cpi->dev_name, cam_sim_name(sim), DEV_IDLEN);
	cpi->unit_number = cam_sim_unit(sim);
	cpi->bus_id = cam_sim_bus(sim);
	cpi->base_transfer_speed = 132 * 1024;	/* XXX what to set this to? */
	cpi->transport = XPORT_SPI;
	cpi->transport_version = 2;
	cpi->protocol = PROTO_SCSI;
	cpi->protocol_version = SCSI_REV_2;
	ccb->ccb_h.status = CAM_REQ_CMP;
	break;
    }

    case XPT_GET_TRAN_SETTINGS:
    {
	struct ccb_trans_settings	*cts = &ccb->cts;
	int				bus, target;
	struct ccb_trans_settings_scsi *scsi = &cts->proto_specific.scsi;
	struct ccb_trans_settings_spi *spi = &cts->xport_specific.spi;

	cts->protocol = PROTO_SCSI;
	cts->protocol_version = SCSI_REV_2;
	cts->transport = XPORT_SPI;
	cts->transport_version = 2;

	scsi->flags = 0;
	scsi->valid = 0;
	spi->flags = 0;
	spi->valid = 0;

	bus = cam_sim_bus(sim);
	target = cts->ccb_h.target_id;
	debug(2, "XPT_GET_TRAN_SETTINGS %d:%d", bus, target);
	/* logical device? */
	if (sc->mly_btl[bus][target].mb_flags & MLY_BTL_LOGICAL) {
	    /* nothing special for these */
	/* physical device? */
	} else if (sc->mly_btl[bus][target].mb_flags & MLY_BTL_PHYSICAL) {
	    /* allow CAM to try tagged transactions */
	    scsi->flags |= CTS_SCSI_FLAGS_TAG_ENB;
	    scsi->valid |= CTS_SCSI_VALID_TQ;

	    /* convert speed (MHz) to usec */
	    if (sc->mly_btl[bus][target].mb_speed == 0) {
		spi->sync_period = 1000000 / 5;
	    } else {
		spi->sync_period = 1000000 / sc->mly_btl[bus][target].mb_speed;
	    }

	    /* convert bus width to CAM internal encoding */
	    switch (sc->mly_btl[bus][target].mb_width) {
	    case 32:
		spi->bus_width = MSG_EXT_WDTR_BUS_32_BIT;
		break;
	    case 16:
		spi->bus_width = MSG_EXT_WDTR_BUS_16_BIT;
		break;
	    case 8:
	    default:
		spi->bus_width = MSG_EXT_WDTR_BUS_8_BIT;
		break;
	    }
	    spi->valid |= CTS_SPI_VALID_SYNC_RATE | CTS_SPI_VALID_BUS_WIDTH;

	    /* not a device, bail out */
	} else {
	    cts->ccb_h.status = CAM_REQ_CMP_ERR;
	    break;
	}

	/* disconnect always OK */
	spi->flags |= CTS_SPI_FLAGS_DISC_ENB;
	spi->valid |= CTS_SPI_VALID_DISC;

	cts->ccb_h.status = CAM_REQ_CMP;
	break;
    }

    default:		/* we can't do this */
	debug(2, "unspported func_code = 0x%x", ccb->ccb_h.func_code);
	ccb->ccb_h.status = CAM_REQ_INVALID;
	break;
    }

    xpt_done(ccb);
}