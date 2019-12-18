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
typedef  int u_int ;
struct ccb_trans_settings_spi {int valid; scalar_t__ sync_offset; int bus_width; int /*<<< orphan*/  sync_period; } ;
struct ccb_trans_settings_sas {int valid; int bitrate; } ;
struct ccb_trans_settings_fc {int valid; int bitrate; } ;
struct TYPE_3__ {struct ccb_trans_settings_sas sas; struct ccb_trans_settings_fc fc; struct ccb_trans_settings_spi spi; } ;
struct TYPE_4__ {scalar_t__ status; int /*<<< orphan*/  func_code; } ;
struct ccb_trans_settings {scalar_t__ transport; TYPE_1__ xport_specific; TYPE_2__ ccb_h; int /*<<< orphan*/  type; } ;
struct ccb_pathinq {int base_transfer_speed; TYPE_2__ ccb_h; } ;
struct cam_periph {struct cam_path* path; } ;
struct cam_path {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 scalar_t__ CAM_REQ_CMP ; 
 int CTS_FC_VALID_SPEED ; 
 int CTS_SAS_VALID_SPEED ; 
 int CTS_SPI_VALID_BUS_WIDTH ; 
 int CTS_SPI_VALID_SYNC_OFFSET ; 
 int /*<<< orphan*/  CTS_TYPE_CURRENT_SETTINGS ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ XPORT_FC ; 
 scalar_t__ XPORT_SAS ; 
 scalar_t__ XPORT_SPI ; 
 int /*<<< orphan*/  XPT_GET_TRAN_SETTINGS ; 
 int /*<<< orphan*/  XPT_PATH_INQ ; 
 scalar_t__ cam_ccb_status (union ccb*) ; 
 int /*<<< orphan*/  cam_periph_assert (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int scsi_calc_syncsrate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_2__*,struct cam_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_scsi_announce_periph(struct cam_periph *periph, u_int *speed, u_int *freq, struct ccb_trans_settings *cts)
{
	struct	ccb_pathinq cpi;
	struct	cam_path *path = periph->path;

	cam_periph_assert(periph, MA_OWNED);

	xpt_setup_ccb(&cts->ccb_h, path, CAM_PRIORITY_NORMAL);
	cts->ccb_h.func_code = XPT_GET_TRAN_SETTINGS;
	cts->type = CTS_TYPE_CURRENT_SETTINGS;
	xpt_action((union ccb*)cts);
	if (cam_ccb_status((union ccb *)cts) != CAM_REQ_CMP)
		return;
	
	/* Ask the SIM for its base transfer speed */
	xpt_setup_ccb(&cpi.ccb_h, path, CAM_PRIORITY_NORMAL);
	cpi.ccb_h.func_code = XPT_PATH_INQ;
	xpt_action((union ccb *)&cpi);

	/* Report connection speed */
	*speed = cpi.base_transfer_speed;
	*freq = 0;

	if (cts->ccb_h.status == CAM_REQ_CMP && cts->transport == XPORT_SPI) {
		struct	ccb_trans_settings_spi *spi =
		    &cts->xport_specific.spi;

		if ((spi->valid & CTS_SPI_VALID_SYNC_OFFSET) != 0
		  && spi->sync_offset != 0) {
			*freq = scsi_calc_syncsrate(spi->sync_period);
			*speed = *freq;
		}
		if ((spi->valid & CTS_SPI_VALID_BUS_WIDTH) != 0)
			*speed *= (0x01 << spi->bus_width);
	}
	if (cts->ccb_h.status == CAM_REQ_CMP && cts->transport == XPORT_FC) {
		struct	ccb_trans_settings_fc *fc =
		    &cts->xport_specific.fc;

		if (fc->valid & CTS_FC_VALID_SPEED)
			*speed = fc->bitrate;
	}
	if (cts->ccb_h.status == CAM_REQ_CMP && cts->transport == XPORT_SAS) {
		struct	ccb_trans_settings_sas *sas =
		    &cts->xport_specific.sas;

		if (sas->valid & CTS_SAS_VALID_SPEED)
			*speed = sas->bitrate;
	}
}