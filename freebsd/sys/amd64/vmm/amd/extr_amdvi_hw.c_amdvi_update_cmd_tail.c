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
struct amdvi_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  total_cmd; int /*<<< orphan*/  cmd_max; struct amdvi_ctrl* ctrl; int /*<<< orphan*/ * cmd; } ;
struct amdvi_ctrl {int /*<<< orphan*/  cmd_head; int /*<<< orphan*/  cmd_tail; } ;
struct amdvi_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MOD_INC (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
amdvi_update_cmd_tail(struct amdvi_softc *softc)
{
	struct amdvi_ctrl *ctrl;
	int size;

	size = sizeof(struct amdvi_cmd);
	KASSERT(softc->cmd != NULL, ("cmd is NULL"));

	ctrl = softc->ctrl;
	KASSERT(ctrl != NULL, ("ctrl is NULL"));

	ctrl->cmd_tail = MOD_INC(ctrl->cmd_tail, size, softc->cmd_max);
	softc->total_cmd++;

#ifdef AMDVI_DEBUG_CMD
	device_printf(softc->dev, "cmd_tail: %s Tail:0x%x, Head:0x%x.\n",
	    ctrl->cmd_tail,
	    ctrl->cmd_head);
#endif

}