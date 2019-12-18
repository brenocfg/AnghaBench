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
struct sbuf {int dummy; } ;
struct ccb_trans_settings_nvme {int valid; int /*<<< orphan*/  max_speed; int /*<<< orphan*/  speed; int /*<<< orphan*/  max_lanes; int /*<<< orphan*/  lanes; int /*<<< orphan*/  spec; } ;
struct TYPE_3__ {struct ccb_trans_settings_nvme nvme; } ;
struct TYPE_4__ {int status; int /*<<< orphan*/  func_code; } ;
struct ccb_trans_settings {TYPE_1__ xport_specific; TYPE_2__ ccb_h; int /*<<< orphan*/  type; } ;
struct ccb_pathinq {int dummy; } ;
struct cam_periph {int /*<<< orphan*/  unit_number; int /*<<< orphan*/  periph_name; struct cam_path* path; } ;
struct cam_path {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 int CTS_NVME_VALID_LINK ; 
 int /*<<< orphan*/  CTS_TYPE_CURRENT_SETTINGS ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  NVME_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVME_MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 int /*<<< orphan*/  XPT_GET_TRAN_SETTINGS ; 
 int /*<<< orphan*/  cam_periph_assert (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 
 int /*<<< orphan*/  sbuf_putbuf (struct sbuf*) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_path_inq (struct ccb_pathinq*,struct cam_path*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_2__*,struct cam_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvme_announce_periph(struct cam_periph *periph)
{
	struct	ccb_pathinq cpi;
	struct	ccb_trans_settings cts;
	struct	cam_path *path = periph->path;
	struct ccb_trans_settings_nvme	*nvmex;
	struct sbuf	sb;
	char		buffer[120];

	cam_periph_assert(periph, MA_OWNED);

	/* Ask the SIM for connection details */
	xpt_setup_ccb(&cts.ccb_h, path, CAM_PRIORITY_NORMAL);
	cts.ccb_h.func_code = XPT_GET_TRAN_SETTINGS;
	cts.type = CTS_TYPE_CURRENT_SETTINGS;
	xpt_action((union ccb*)&cts);
	if ((cts.ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP)
		return;
	nvmex = &cts.xport_specific.nvme;

	/* Ask the SIM for its base transfer speed */
	xpt_path_inq(&cpi, periph->path);
	sbuf_new(&sb, buffer, sizeof(buffer), SBUF_FIXEDLEN);
	sbuf_printf(&sb, "%s%d: nvme version %d.%d",
	    periph->periph_name, periph->unit_number,
	    NVME_MAJOR(nvmex->spec),
	    NVME_MINOR(nvmex->spec));
	if (nvmex->valid & CTS_NVME_VALID_LINK)
		sbuf_printf(&sb, " x%d (max x%d) lanes PCIe Gen%d (max Gen%d) link",
		    nvmex->lanes, nvmex->max_lanes,
		    nvmex->speed, nvmex->max_speed);
	sbuf_printf(&sb, "\n");
	sbuf_finish(&sb);
	sbuf_putbuf(&sb);
}