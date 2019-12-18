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
struct TYPE_2__ {int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct ata_channel {int /*<<< orphan*/  state_mtx; int /*<<< orphan*/ * sim; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  ata_reinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_rescan (union ccb*) ; 

__attribute__((used)) static void
ata_conn_event(void *context, int dummy)
{
	device_t dev = (device_t)context;
	struct ata_channel *ch = device_get_softc(dev);
	union ccb *ccb;

	mtx_lock(&ch->state_mtx);
	if (ch->sim == NULL) {
		mtx_unlock(&ch->state_mtx);
		return;
	}
	ata_reinit(dev);
	if ((ccb = xpt_alloc_ccb_nowait()) == NULL)
		return;
	if (xpt_create_path(&ccb->ccb_h.path, NULL,
	    cam_sim_path(ch->sim),
	    CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		xpt_free_ccb(ccb);
		return;
	}
	xpt_rescan(ccb);
	mtx_unlock(&ch->state_mtx);
}