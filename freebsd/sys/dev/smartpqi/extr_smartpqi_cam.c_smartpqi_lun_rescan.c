#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  cbfcnp; int /*<<< orphan*/  func_code; } ;
union ccb {TYPE_2__ crcn; TYPE_3__ ccb_h; } ;
struct TYPE_4__ {int /*<<< orphan*/  sim; } ;
struct pqisrc_softstate {TYPE_1__ os_specific; } ;
struct cam_path {int dummy; } ;
typedef  scalar_t__ cam_status ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_FLAG_NONE ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  DBG_ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  XPT_SCAN_LUN ; 
 int /*<<< orphan*/  bzero (union ccb*,int) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smartpqi_lunrescan_cb ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 scalar_t__ xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_3__*,struct cam_path*,int) ; 

__attribute__((used)) static void smartpqi_lun_rescan(struct pqisrc_softstate *softs, int target, 
			int lun)
{
	union ccb   *ccb = NULL;
	cam_status  status = 0;
	struct cam_path     *path = NULL;	

	DBG_FUNC("IN\n");

	ccb = xpt_alloc_ccb_nowait();
	status = xpt_create_path(&path, NULL,
				cam_sim_path(softs->os_specific.sim), target, lun);
	if (status != CAM_REQ_CMP) {
		DBG_ERR("xpt_create_path status(%d) != CAM_REQ_CMP \n",
				 status);
		xpt_free_ccb(ccb);
		return;
	}

	bzero(ccb, sizeof(union ccb));
	xpt_setup_ccb(&ccb->ccb_h, path, 5);
	ccb->ccb_h.func_code = XPT_SCAN_LUN;
	ccb->ccb_h.cbfcnp = smartpqi_lunrescan_cb;
	ccb->crcn.flags = CAM_FLAG_NONE;

	xpt_action(ccb);

	DBG_FUNC("OUT\n");
}