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
typedef  union ccb {int dummy; } ccb ;
struct vtscsi_softc {int /*<<< orphan*/  vtscsi_sim; int /*<<< orphan*/  vtscsi_path; } ;
struct TYPE_2__ {int /*<<< orphan*/  func_code; } ;
struct ccb_setasync {int /*<<< orphan*/  callback_arg; int /*<<< orphan*/  callback; scalar_t__ event_enable; TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPT_SASYNC_CB ; 
 int /*<<< orphan*/  vtscsi_cam_async ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vtscsi_deregister_async(struct vtscsi_softc *sc)
{
	struct ccb_setasync csa;

	xpt_setup_ccb(&csa.ccb_h, sc->vtscsi_path, 5);
	csa.ccb_h.func_code = XPT_SASYNC_CB;
	csa.event_enable = 0;
	csa.callback = vtscsi_cam_async;
	csa.callback_arg = sc->vtscsi_sim;

	xpt_action((union ccb *) &csa);
}