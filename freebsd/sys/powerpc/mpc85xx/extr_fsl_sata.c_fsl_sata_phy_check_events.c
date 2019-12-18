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
struct fsl_sata_channel {scalar_t__ pm_level; int /*<<< orphan*/  sim; int /*<<< orphan*/  path; int /*<<< orphan*/  dev; int /*<<< orphan*/  r_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_BUS_RESET ; 
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ATA_SE_EXCHANGED ; 
 int ATA_SE_PHY_CHANGED ; 
 int ATA_SS_DET_MASK ; 
 int ATA_SS_DET_NO_DEVICE ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  FSL_SATA_P_SSTS ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_rescan (union ccb*) ; 

__attribute__((used)) static int
fsl_sata_phy_check_events(struct fsl_sata_channel *ch, u_int32_t serr)
{

	if (((ch->pm_level == 0) && (serr & ATA_SE_PHY_CHANGED)) ||
	    ((ch->pm_level != 0) && (serr & ATA_SE_EXCHANGED))) {
		u_int32_t status = ATA_INL(ch->r_mem, FSL_SATA_P_SSTS);
		union ccb *ccb;

		if (bootverbose) {
			if ((status & ATA_SS_DET_MASK) != ATA_SS_DET_NO_DEVICE)
				device_printf(ch->dev, "CONNECT requested\n");
			else
				device_printf(ch->dev, "DISCONNECT requested\n");
		}
		/* Issue soft reset */
		xpt_async(AC_BUS_RESET, ch->path, NULL);
		if ((ccb = xpt_alloc_ccb_nowait()) == NULL)
			return (0);
		if (xpt_create_path(&ccb->ccb_h.path, NULL,
		    cam_sim_path(ch->sim),
		    CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
			xpt_free_ccb(ccb);
			return (0);
		}
		xpt_rescan(ccb);
		return (1);
	}
	return (0);
}