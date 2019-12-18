#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct targ_softc {int state; int /*<<< orphan*/  path; } ;
typedef  scalar_t__ cam_status ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_PERIPH ; 
 scalar_t__ CAM_REQ_CMP ; 
 int TARG_STATE_LUN_ENABLED ; 
 int /*<<< orphan*/  abort_all_pending (struct targ_softc*) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 scalar_t__ targendislun (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static cam_status
targdisable(struct targ_softc *softc)
{
	cam_status status;

	if ((softc->state & TARG_STATE_LUN_ENABLED) == 0)
		return (CAM_REQ_CMP);

	CAM_DEBUG(softc->path, CAM_DEBUG_PERIPH, ("targdisable\n"));

	/* Abort any ccbs pending on the controller */
	abort_all_pending(softc);

	/* Disable this lun */
	status = targendislun(softc->path, /*enable*/0,
			      /*grp6_len*/0, /*grp7_len*/0);
	if (status == CAM_REQ_CMP)
		softc->state &= ~TARG_STATE_LUN_ENABLED;
	else
		printf("Disable lun failed, status %#x\n", status);

	return (status);
}