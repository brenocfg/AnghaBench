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
struct ahci_channel {scalar_t__ pm_level; int /*<<< orphan*/  sim; int /*<<< orphan*/  dev; int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_P_CMD ; 
 int AHCI_P_CMD_CPD ; 
 int AHCI_P_CMD_CPS ; 
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  ahci_reset (struct ahci_channel*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_rescan (union ccb*) ; 

__attribute__((used)) static void
ahci_cpd_check_events(struct ahci_channel *ch)
{
	u_int32_t status;
	union ccb *ccb;
	device_t dev;

	if (ch->pm_level == 0)
		return;

	status = ATA_INL(ch->r_mem, AHCI_P_CMD);
	if ((status & AHCI_P_CMD_CPD) == 0)
		return;

	if (bootverbose) {
		dev = ch->dev;
		if (status & AHCI_P_CMD_CPS) {
			device_printf(dev, "COLD CONNECT requested\n");
		} else
			device_printf(dev, "COLD DISCONNECT requested\n");
	}
	ahci_reset(ch);
	if ((ccb = xpt_alloc_ccb_nowait()) == NULL)
		return;
	if (xpt_create_path(&ccb->ccb_h.path, NULL, cam_sim_path(ch->sim),
	    CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		xpt_free_ccb(ccb);
		return;
	}
	xpt_rescan(ccb);
}