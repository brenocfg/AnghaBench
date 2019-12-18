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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_int ;
struct ccb_trans_settings_spi {int valid; int flags; scalar_t__ bus_width; scalar_t__ sync_offset; int /*<<< orphan*/  ppr_options; scalar_t__ sync_period; } ;
struct ccb_trans_settings_scsi {int valid; int flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  status; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; } ;
struct TYPE_8__ {struct ccb_trans_settings_spi spi; } ;
struct TYPE_7__ {struct ccb_trans_settings_scsi scsi; } ;
struct ccb_trans_settings {scalar_t__ type; TYPE_4__ ccb_h; int /*<<< orphan*/  transport_version; int /*<<< orphan*/  protocol_version; TYPE_2__ xport_specific; TYPE_1__ proto_specific; } ;
struct ahd_tmode_tstate {int discenable; int tagenable; } ;
struct ahd_softc {int user_discenable; int user_tagenable; } ;
struct TYPE_12__ {scalar_t__ offset; scalar_t__ period; int /*<<< orphan*/  ppr_options; int /*<<< orphan*/  transport_version; int /*<<< orphan*/  protocol_version; } ;
struct TYPE_11__ {scalar_t__ offset; scalar_t__ period; int /*<<< orphan*/  ppr_options; int /*<<< orphan*/  transport_version; int /*<<< orphan*/  protocol_version; } ;
struct TYPE_9__ {int /*<<< orphan*/  transport_version; int /*<<< orphan*/  protocol_version; } ;
struct ahd_initiator_tinfo {TYPE_6__ goal; TYPE_5__ user; TYPE_3__ curr; } ;
struct ahd_devinfo {int target_mask; int /*<<< orphan*/  target; int /*<<< orphan*/  our_scsiid; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_SYNCRATE_MAX ; 
 int /*<<< orphan*/  AHD_TRANS_GOAL ; 
 int /*<<< orphan*/  AHD_TRANS_USER ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_INVALID ; 
 int CTS_SCSI_FLAGS_TAG_ENB ; 
 int CTS_SCSI_VALID_TQ ; 
 int CTS_SPI_FLAGS_DISC_ENB ; 
 int CTS_SPI_VALID_BUS_WIDTH ; 
 int CTS_SPI_VALID_DISC ; 
 int CTS_SPI_VALID_PPR_OPTIONS ; 
 int CTS_SPI_VALID_SYNC_OFFSET ; 
 int CTS_SPI_VALID_SYNC_RATE ; 
 scalar_t__ CTS_TYPE_CURRENT_SETTINGS ; 
 scalar_t__ CTS_TYPE_USER_SETTINGS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_EXT_PPR_DT_REQ ; 
 int /*<<< orphan*/  MSG_EXT_PPR_IU_REQ ; 
 scalar_t__ MSG_EXT_WDTR_BUS_16_BIT ; 
 int /*<<< orphan*/  ROLE_UNKNOWN ; 
 int /*<<< orphan*/  SIM_CHANNEL (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIM_SCSI_ID (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_compile_devinfo (struct ahd_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ahd_initiator_tinfo* ahd_fetch_transinfo (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ahd_tmode_tstate**) ; 
 int /*<<< orphan*/  ahd_find_syncrate (struct ahd_softc*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_syncrate (struct ahd_softc*,struct ahd_devinfo*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_width (struct ahd_softc*,struct ahd_devinfo*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_validate_offset (struct ahd_softc*,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_validate_width (struct ahd_softc*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sim ; 

__attribute__((used)) static void
ahd_set_tran_settings(struct ahd_softc *ahd, int our_id, char channel,
		      struct ccb_trans_settings *cts)
{
	struct	  ahd_devinfo devinfo;
	struct	  ccb_trans_settings_scsi *scsi;
	struct	  ccb_trans_settings_spi *spi;
	struct	  ahd_initiator_tinfo *tinfo;
	struct	  ahd_tmode_tstate *tstate;
	uint16_t *discenable;
	uint16_t *tagenable;
	u_int	  update_type;

	scsi = &cts->proto_specific.scsi;
	spi = &cts->xport_specific.spi;
	ahd_compile_devinfo(&devinfo, SIM_SCSI_ID(ahd, sim),
			    cts->ccb_h.target_id,
			    cts->ccb_h.target_lun,
			    SIM_CHANNEL(ahd, sim),
			    ROLE_UNKNOWN);
	tinfo = ahd_fetch_transinfo(ahd, devinfo.channel,
				    devinfo.our_scsiid,
				    devinfo.target, &tstate);
	update_type = 0;
	if (cts->type == CTS_TYPE_CURRENT_SETTINGS) {
		update_type |= AHD_TRANS_GOAL;
		discenable = &tstate->discenable;
		tagenable = &tstate->tagenable;
		tinfo->curr.protocol_version = cts->protocol_version;
		tinfo->curr.transport_version = cts->transport_version;
		tinfo->goal.protocol_version = cts->protocol_version;
		tinfo->goal.transport_version = cts->transport_version;
	} else if (cts->type == CTS_TYPE_USER_SETTINGS) {
		update_type |= AHD_TRANS_USER;
		discenable = &ahd->user_discenable;
		tagenable = &ahd->user_tagenable;
		tinfo->user.protocol_version = cts->protocol_version;
		tinfo->user.transport_version = cts->transport_version;
	} else {
		cts->ccb_h.status = CAM_REQ_INVALID;
		return;
	}
	
	if ((spi->valid & CTS_SPI_VALID_DISC) != 0) {
		if ((spi->flags & CTS_SPI_FLAGS_DISC_ENB) != 0)
			*discenable |= devinfo.target_mask;
		else
			*discenable &= ~devinfo.target_mask;
	}
	
	if ((scsi->valid & CTS_SCSI_VALID_TQ) != 0) {
		if ((scsi->flags & CTS_SCSI_FLAGS_TAG_ENB) != 0)
			*tagenable |= devinfo.target_mask;
		else
			*tagenable &= ~devinfo.target_mask;
	}	

	if ((spi->valid & CTS_SPI_VALID_BUS_WIDTH) != 0) {
		ahd_validate_width(ahd, /*tinfo limit*/NULL,
				   &spi->bus_width, ROLE_UNKNOWN);
		ahd_set_width(ahd, &devinfo, spi->bus_width,
			      update_type, /*paused*/FALSE);
	}

	if ((spi->valid & CTS_SPI_VALID_PPR_OPTIONS) == 0) {
		if (update_type == AHD_TRANS_USER)
			spi->ppr_options = tinfo->user.ppr_options;
		else
			spi->ppr_options = tinfo->goal.ppr_options;
	}

	if ((spi->valid & CTS_SPI_VALID_SYNC_OFFSET) == 0) {
		if (update_type == AHD_TRANS_USER)
			spi->sync_offset = tinfo->user.offset;
		else
			spi->sync_offset = tinfo->goal.offset;
	}

	if ((spi->valid & CTS_SPI_VALID_SYNC_RATE) == 0) {
		if (update_type == AHD_TRANS_USER)
			spi->sync_period = tinfo->user.period;
		else
			spi->sync_period = tinfo->goal.period;
	}

	if (((spi->valid & CTS_SPI_VALID_SYNC_RATE) != 0)
	 || ((spi->valid & CTS_SPI_VALID_SYNC_OFFSET) != 0)) {
		u_int	maxsync;

		maxsync = AHD_SYNCRATE_MAX;

		if (spi->bus_width != MSG_EXT_WDTR_BUS_16_BIT)
			spi->ppr_options &= ~MSG_EXT_PPR_DT_REQ;

		if ((*discenable & devinfo.target_mask) == 0)
			spi->ppr_options &= ~MSG_EXT_PPR_IU_REQ;

		ahd_find_syncrate(ahd, &spi->sync_period,
				  &spi->ppr_options, maxsync);
		ahd_validate_offset(ahd, /*tinfo limit*/NULL,
				    spi->sync_period, &spi->sync_offset,
				    spi->bus_width, ROLE_UNKNOWN);

		/* We use a period of 0 to represent async */
		if (spi->sync_offset == 0) {
			spi->sync_period = 0;
			spi->ppr_options = 0;
		}

		ahd_set_syncrate(ahd, &devinfo, spi->sync_period,
				 spi->sync_offset, spi->ppr_options,
				 update_type, /*paused*/FALSE);
	}
	cts->ccb_h.status = CAM_REQ_CMP;
}