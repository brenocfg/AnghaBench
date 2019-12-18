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
typedef  int u_int32_t ;
struct mvs_channel {scalar_t__ pm_level; int /*<<< orphan*/  sim; int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  SATA_SS ; 
 int SATA_SS_DET_MASK ; 
 int SATA_SS_DET_PHY_ONLINE ; 
 int SATA_SS_IPM_ACTIVE ; 
 int SATA_SS_IPM_MASK ; 
 int SATA_SS_SPD_MASK ; 
 int SATA_SS_SPD_NO_SPEED ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mvs_reset (int /*<<< orphan*/ ) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_rescan (union ccb*) ; 

__attribute__((used)) static void
mvs_phy_check_events(device_t dev, u_int32_t serr)
{
	struct mvs_channel *ch = device_get_softc(dev);

	if (ch->pm_level == 0) {
		u_int32_t status = ATA_INL(ch->r_mem, SATA_SS);
		union ccb *ccb;

		if (bootverbose) {
			if (((status & SATA_SS_DET_MASK) == SATA_SS_DET_PHY_ONLINE) &&
			    ((status & SATA_SS_SPD_MASK) != SATA_SS_SPD_NO_SPEED) &&
			    ((status & SATA_SS_IPM_MASK) == SATA_SS_IPM_ACTIVE)) {
				device_printf(dev, "CONNECT requested\n");
			} else
				device_printf(dev, "DISCONNECT requested\n");
		}
		mvs_reset(dev);
		if ((ccb = xpt_alloc_ccb_nowait()) == NULL)
			return;
		if (xpt_create_path(&ccb->ccb_h.path, NULL,
		    cam_sim_path(ch->sim),
		    CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
			xpt_free_ccb(ccb);
			return;
		}
		xpt_rescan(ccb);
	}
}