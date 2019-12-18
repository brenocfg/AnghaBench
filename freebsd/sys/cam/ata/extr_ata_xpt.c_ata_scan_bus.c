#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  priority; } ;
struct TYPE_16__ {int func_code; int status; void (* cbfcnp ) (struct cam_periph*,union ccb*) ;TYPE_6__* ppriv_ptr0; int /*<<< orphan*/  flags; TYPE_3__ pinfo; int /*<<< orphan*/  path_id; struct cam_path* path; } ;
struct TYPE_13__ {int /*<<< orphan*/  flags; } ;
struct TYPE_17__ {int hba_inquiry; int hba_misc; int max_target; } ;
union ccb {TYPE_7__ ccb_h; TYPE_4__ crcn; TYPE_8__ cpi; } ;
struct mtx {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  valid; int /*<<< orphan*/  pm_present; } ;
struct TYPE_11__ {TYPE_1__ sata; } ;
struct ccb_trans_settings {TYPE_2__ xport_specific; int /*<<< orphan*/  type; TYPE_7__ ccb_h; } ;
struct cam_periph {int dummy; } ;
struct cam_path {TYPE_5__* bus; } ;
typedef  int /*<<< orphan*/  cts ;
typedef  int cam_status ;
struct TYPE_15__ {int counter; union ccb* request_ccb; TYPE_8__* cpi; } ;
typedef  TYPE_6__ ata_scan_bus_info ;
struct TYPE_14__ {int /*<<< orphan*/  last_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (struct cam_path*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  CAM_PRIORITY_NONE ; 
 int CAM_REQ_CMP ; 
 void* CAM_RESRC_UNAVAIL ; 
 int /*<<< orphan*/  CAM_UNLOCKED ; 
 int /*<<< orphan*/  CTS_SATA_VALID_PM ; 
 int /*<<< orphan*/  CTS_TYPE_CURRENT_SETTINGS ; 
 int /*<<< orphan*/  M_CAMXPT ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int PIM_NOBUSRESET ; 
 int PI_SATAPM ; 
 int PI_SDTR_ABLE ; 
 int PI_WIDE_16 ; 
 int PI_WIDE_32 ; 
 int XPT_RESET_BUS ; 
#define  XPT_SCAN_BUS 130 
#define  XPT_SCAN_LUN 129 
#define  XPT_SCAN_TGT 128 
 int const XPT_SET_TRAN_SETTINGS ; 
 int /*<<< orphan*/  bzero (struct ccb_trans_settings*,int) ; 
 int /*<<< orphan*/  free (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  timevalisset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 int xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_inq (TYPE_8__*,struct cam_path*) ; 
 struct mtx* xpt_path_mtx (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_7__*,struct cam_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ata_scan_bus(struct cam_periph *periph, union ccb *request_ccb)
{
	struct	cam_path *path;
	ata_scan_bus_info *scan_info;
	union	ccb *work_ccb, *reset_ccb;
	struct mtx *mtx;
	cam_status status;

	CAM_DEBUG(request_ccb->ccb_h.path, CAM_DEBUG_TRACE,
		  ("xpt_scan_bus\n"));
	switch (request_ccb->ccb_h.func_code) {
	case XPT_SCAN_BUS:
	case XPT_SCAN_TGT:
		/* Find out the characteristics of the bus */
		work_ccb = xpt_alloc_ccb_nowait();
		if (work_ccb == NULL) {
			request_ccb->ccb_h.status = CAM_RESRC_UNAVAIL;
			xpt_done(request_ccb);
			return;
		}
		xpt_path_inq(&work_ccb->cpi, request_ccb->ccb_h.path);
		if (work_ccb->ccb_h.status != CAM_REQ_CMP) {
			request_ccb->ccb_h.status = work_ccb->ccb_h.status;
			xpt_free_ccb(work_ccb);
			xpt_done(request_ccb);
			return;
		}

		/* We may need to reset bus first, if we haven't done it yet. */
		if ((work_ccb->cpi.hba_inquiry &
		    (PI_WIDE_32|PI_WIDE_16|PI_SDTR_ABLE)) &&
		    !(work_ccb->cpi.hba_misc & PIM_NOBUSRESET) &&
		    !timevalisset(&request_ccb->ccb_h.path->bus->last_reset)) {
			reset_ccb = xpt_alloc_ccb_nowait();
			if (reset_ccb == NULL) {
				request_ccb->ccb_h.status = CAM_RESRC_UNAVAIL;
				xpt_free_ccb(work_ccb);
				xpt_done(request_ccb);
				return;
			}
			xpt_setup_ccb(&reset_ccb->ccb_h, request_ccb->ccb_h.path,
			      CAM_PRIORITY_NONE);
			reset_ccb->ccb_h.func_code = XPT_RESET_BUS;
			xpt_action(reset_ccb);
			if (reset_ccb->ccb_h.status != CAM_REQ_CMP) {
				request_ccb->ccb_h.status = reset_ccb->ccb_h.status;
				xpt_free_ccb(reset_ccb);
				xpt_free_ccb(work_ccb);
				xpt_done(request_ccb);
				return;
			}
			xpt_free_ccb(reset_ccb);
		}

		/* Save some state for use while we probe for devices */
		scan_info = (ata_scan_bus_info *)
		    malloc(sizeof(ata_scan_bus_info), M_CAMXPT, M_NOWAIT);
		if (scan_info == NULL) {
			request_ccb->ccb_h.status = CAM_RESRC_UNAVAIL;
			xpt_free_ccb(work_ccb);
			xpt_done(request_ccb);
			return;
		}
		scan_info->request_ccb = request_ccb;
		scan_info->cpi = &work_ccb->cpi;
		/* If PM supported, probe it first. */
		if (scan_info->cpi->hba_inquiry & PI_SATAPM)
			scan_info->counter = scan_info->cpi->max_target;
		else
			scan_info->counter = 0;

		work_ccb = xpt_alloc_ccb_nowait();
		if (work_ccb == NULL) {
			free(scan_info, M_CAMXPT);
			request_ccb->ccb_h.status = CAM_RESRC_UNAVAIL;
			xpt_done(request_ccb);
			break;
		}
		mtx = xpt_path_mtx(scan_info->request_ccb->ccb_h.path);
		goto scan_next;
	case XPT_SCAN_LUN:
		work_ccb = request_ccb;
		/* Reuse the same CCB to query if a device was really found */
		scan_info = (ata_scan_bus_info *)work_ccb->ccb_h.ppriv_ptr0;
		mtx = xpt_path_mtx(scan_info->request_ccb->ccb_h.path);
		mtx_lock(mtx);
		/* If there is PMP... */
		if ((scan_info->cpi->hba_inquiry & PI_SATAPM) &&
		    (scan_info->counter == scan_info->cpi->max_target)) {
			if (work_ccb->ccb_h.status == CAM_REQ_CMP) {
				/* everything else will be probed by it */
				/* Free the current request path- we're done with it. */
				xpt_free_path(work_ccb->ccb_h.path);
				goto done;
			} else {
				struct ccb_trans_settings cts;

				/* Report SIM that PM is absent. */
				bzero(&cts, sizeof(cts));
				xpt_setup_ccb(&cts.ccb_h,
				    work_ccb->ccb_h.path, CAM_PRIORITY_NONE);
				cts.ccb_h.func_code = XPT_SET_TRAN_SETTINGS;
				cts.type = CTS_TYPE_CURRENT_SETTINGS;
				cts.xport_specific.sata.pm_present = 0;
				cts.xport_specific.sata.valid = CTS_SATA_VALID_PM;
				xpt_action((union ccb *)&cts);
			}
		}
		/* Free the current request path- we're done with it. */
		xpt_free_path(work_ccb->ccb_h.path);
		if (scan_info->counter ==
		    ((scan_info->cpi->hba_inquiry & PI_SATAPM) ?
		    0 : scan_info->cpi->max_target)) {
done:
			mtx_unlock(mtx);
			xpt_free_ccb(work_ccb);
			xpt_free_ccb((union ccb *)scan_info->cpi);
			request_ccb = scan_info->request_ccb;
			free(scan_info, M_CAMXPT);
			request_ccb->ccb_h.status = CAM_REQ_CMP;
			xpt_done(request_ccb);
			break;
		}
		/* Take next device. Wrap from max (PMP) to 0. */
		scan_info->counter = (scan_info->counter + 1 ) %
		    (scan_info->cpi->max_target + 1);
scan_next:
		status = xpt_create_path(&path, NULL,
		    scan_info->request_ccb->ccb_h.path_id,
		    scan_info->counter, 0);
		if (status != CAM_REQ_CMP) {
			if (request_ccb->ccb_h.func_code == XPT_SCAN_LUN)
				mtx_unlock(mtx);
			printf("xpt_scan_bus: xpt_create_path failed"
			    " with status %#x, bus scan halted\n",
			    status);
			xpt_free_ccb(work_ccb);
			xpt_free_ccb((union ccb *)scan_info->cpi);
			request_ccb = scan_info->request_ccb;
			free(scan_info, M_CAMXPT);
			request_ccb->ccb_h.status = status;
			xpt_done(request_ccb);
			break;
		}
		xpt_setup_ccb(&work_ccb->ccb_h, path,
		    scan_info->request_ccb->ccb_h.pinfo.priority);
		work_ccb->ccb_h.func_code = XPT_SCAN_LUN;
		work_ccb->ccb_h.cbfcnp = ata_scan_bus;
		work_ccb->ccb_h.flags |= CAM_UNLOCKED;
		work_ccb->ccb_h.ppriv_ptr0 = scan_info;
		work_ccb->crcn.flags = scan_info->request_ccb->crcn.flags;
		mtx_unlock(mtx);
		if (request_ccb->ccb_h.func_code == XPT_SCAN_LUN)
			mtx = NULL;
		xpt_action(work_ccb);
		if (mtx != NULL)
			mtx_lock(mtx);
		break;
	default:
		break;
	}
}