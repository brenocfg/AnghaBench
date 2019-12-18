#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  size_t target_id_t ;
struct TYPE_9__ {int Capabilities; } ;
struct mpt_softc {scalar_t__ phydisk_sim; int mpt_disc_enable; int mpt_tag_enable; TYPE_3__ mpt_port_page0; TYPE_5__* mpt_dev_page0; } ;
struct ccb_trans_settings_spi {int sync_offset; int sync_period; int /*<<< orphan*/  flags; int /*<<< orphan*/  valid; int /*<<< orphan*/  bus_width; } ;
struct ccb_trans_settings_scsi {int /*<<< orphan*/  flags; scalar_t__ valid; } ;
struct TYPE_10__ {size_t target_id; scalar_t__ target_lun; int /*<<< orphan*/  path; } ;
struct TYPE_8__ {struct ccb_trans_settings_spi spi; } ;
struct TYPE_7__ {struct ccb_trans_settings_scsi scsi; } ;
struct ccb_trans_settings {TYPE_4__ ccb_h; TYPE_2__ xport_specific; TYPE_1__ proto_specific; } ;
struct TYPE_11__ {int NegotiatedParameters; int /*<<< orphan*/  Information; int /*<<< orphan*/  Header; } ;
typedef  TYPE_5__ CONFIG_PAGE_SCSI_DEVICE_0 ;

/* Variables and functions */
 scalar_t__ CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  CTS_SCSI_FLAGS_TAG_ENB ; 
 scalar_t__ CTS_SCSI_VALID_TQ ; 
 int /*<<< orphan*/  CTS_SPI_FLAGS_DISC_ENB ; 
 int /*<<< orphan*/  CTS_SPI_VALID_BUS_WIDTH ; 
 int /*<<< orphan*/  CTS_SPI_VALID_DISC ; 
 int /*<<< orphan*/  CTS_SPI_VALID_SYNC_OFFSET ; 
 int /*<<< orphan*/  CTS_SPI_VALID_SYNC_RATE ; 
 int DP_DISC_DISABL ; 
 int DP_DISC_ENABLE ; 
 int DP_NARROW ; 
 int DP_SYNC ; 
 int DP_TQING_DISABL ; 
 int DP_TQING_ENABLE ; 
 int DP_WIDE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IS_CURRENT_SETTINGS (struct ccb_trans_settings*) ; 
 int MPI_SCSIDEVPAGE0_NP_NEG_SYNC_OFFSET_MASK ; 
 int MPI_SCSIDEVPAGE0_NP_NEG_SYNC_PERIOD_MASK ; 
 int MPI_SCSIDEVPAGE0_NP_SHIFT_SYNC_OFFSET ; 
 int MPI_SCSIDEVPAGE0_NP_SHIFT_SYNC_PERIOD ; 
 int MPI_SCSIDEVPAGE0_NP_WIDE ; 
 int MPI_SCSIPORTPAGE0_CAP_GET_MAX_SYNC_OFFSET (int) ; 
 int MPI_SCSIPORTPAGE0_CAP_GET_MIN_SYNC_PERIOD (int) ; 
 int /*<<< orphan*/  MPT_PRT_DEBUG ; 
 int /*<<< orphan*/  MPT_PRT_NEGOTIATION ; 
 int /*<<< orphan*/  MSG_EXT_WDTR_BUS_16_BIT ; 
 int /*<<< orphan*/  MSG_EXT_WDTR_BUS_8_BIT ; 
 int /*<<< orphan*/  mpt2host_config_page_scsi_device_0 (TYPE_5__*) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*,size_t,...) ; 
 scalar_t__ mpt_map_physdisk (struct mpt_softc*,union ccb*,size_t*) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,size_t) ; 
 int mpt_read_cur_cfg_page (struct mpt_softc*,size_t,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xpt_path_sim (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpt_get_spi_settings(struct mpt_softc *mpt, struct ccb_trans_settings *cts)
{
	struct ccb_trans_settings_scsi *scsi = &cts->proto_specific.scsi;
	struct ccb_trans_settings_spi *spi = &cts->xport_specific.spi;
	target_id_t tgt;
	uint32_t dval, pval, oval;
	int rv;

	if (IS_CURRENT_SETTINGS(cts) == 0) {
		tgt = cts->ccb_h.target_id;
	} else if (xpt_path_sim(cts->ccb_h.path) == mpt->phydisk_sim) {
		if (mpt_map_physdisk(mpt, (union ccb *)cts, &tgt)) {
			return (-1);
		}
	} else {
		tgt = cts->ccb_h.target_id;
	}

	/*
	 * We aren't looking at Port Page 2 BIOS settings here-
	 * sometimes these have been known to be bogus XXX.
	 *
	 * For user settings, we pick the max from port page 0
	 * 
	 * For current settings we read the current settings out from
	 * device page 0 for that target.
	 */
	if (IS_CURRENT_SETTINGS(cts)) {
		CONFIG_PAGE_SCSI_DEVICE_0 tmp;
		dval = 0;

		tmp = mpt->mpt_dev_page0[tgt];
		rv = mpt_read_cur_cfg_page(mpt, tgt, &tmp.Header,
		    sizeof(tmp), FALSE, 5000);
		if (rv) {
			mpt_prt(mpt, "can't get tgt %d config page 0\n", tgt);
			return (rv);
		}
		mpt2host_config_page_scsi_device_0(&tmp);
		
		mpt_lprt(mpt, MPT_PRT_DEBUG,
		    "mpt_get_spi_settings[%d]: current NP %x Info %x\n", tgt,
		    tmp.NegotiatedParameters, tmp.Information);
		dval |= (tmp.NegotiatedParameters & MPI_SCSIDEVPAGE0_NP_WIDE) ?
		    DP_WIDE : DP_NARROW;
		dval |= (mpt->mpt_disc_enable & (1 << tgt)) ?
		    DP_DISC_ENABLE : DP_DISC_DISABL;
		dval |= (mpt->mpt_tag_enable & (1 << tgt)) ?
		    DP_TQING_ENABLE : DP_TQING_DISABL;
		oval = tmp.NegotiatedParameters;
		oval &= MPI_SCSIDEVPAGE0_NP_NEG_SYNC_OFFSET_MASK;
		oval >>= MPI_SCSIDEVPAGE0_NP_SHIFT_SYNC_OFFSET;
		pval = tmp.NegotiatedParameters;
		pval &= MPI_SCSIDEVPAGE0_NP_NEG_SYNC_PERIOD_MASK;
		pval >>= MPI_SCSIDEVPAGE0_NP_SHIFT_SYNC_PERIOD;
		mpt->mpt_dev_page0[tgt] = tmp;
	} else {
		dval = DP_WIDE|DP_DISC_ENABLE|DP_TQING_ENABLE|DP_SYNC;
		oval = mpt->mpt_port_page0.Capabilities;
		oval = MPI_SCSIPORTPAGE0_CAP_GET_MAX_SYNC_OFFSET(oval);
		pval = mpt->mpt_port_page0.Capabilities;
		pval = MPI_SCSIPORTPAGE0_CAP_GET_MIN_SYNC_PERIOD(pval);
	}

	spi->valid = 0;
	scsi->valid = 0;
	spi->flags = 0;
	scsi->flags = 0;
	spi->sync_offset = oval;
	spi->sync_period = pval;
	spi->valid |= CTS_SPI_VALID_SYNC_OFFSET;
	spi->valid |= CTS_SPI_VALID_SYNC_RATE;
	spi->valid |= CTS_SPI_VALID_BUS_WIDTH;
	if (dval & DP_WIDE) {
		spi->bus_width = MSG_EXT_WDTR_BUS_16_BIT;
	} else {
		spi->bus_width = MSG_EXT_WDTR_BUS_8_BIT;
	}
	if (cts->ccb_h.target_lun != CAM_LUN_WILDCARD) {
		scsi->valid = CTS_SCSI_VALID_TQ;
		if (dval & DP_TQING_ENABLE) {
			scsi->flags |= CTS_SCSI_FLAGS_TAG_ENB;
		}
		spi->valid |= CTS_SPI_VALID_DISC;
		if (dval & DP_DISC_ENABLE) {
			spi->flags |= CTS_SPI_FLAGS_DISC_ENB;
		}
	}

	mpt_lprt(mpt, MPT_PRT_NEGOTIATION,
	    "mpt_get_spi_settings[%d]: %s flags 0x%x per 0x%x off=%d\n", tgt,
	    IS_CURRENT_SETTINGS(cts) ? "ACTIVE" : "NVRAM ", dval, pval, oval);
	return (0);
}