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
struct amdvi_softc {int /*<<< orphan*/  dev; struct amdvi_ctrl* ctrl; } ;
struct amdvi_ctrl {int control; int /*<<< orphan*/  cmd_head; int /*<<< orphan*/  cmd_tail; } ;

/* Variables and functions */
 int AMDVI_CTRL_EN ; 
 int /*<<< orphan*/  KASSERT (struct amdvi_softc*,char*) ; 
 scalar_t__ amdvi_cmp_wait (struct amdvi_softc*) ; 
 int /*<<< orphan*/  amdvi_dump_cmds (struct amdvi_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
amdvi_wait(struct amdvi_softc *softc)
{
	struct amdvi_ctrl *ctrl;
	int i;

	KASSERT(softc, ("softc is NULL"));

	ctrl = softc->ctrl;
	KASSERT(ctrl != NULL, ("ctrl is NULL"));
	/* Don't wait if h/w is not enabled. */
	if ((ctrl->control & AMDVI_CTRL_EN) == 0)
		return;

	for (i = 0; i < 10; i++) {
		if (amdvi_cmp_wait(softc))
			return;
	}

	device_printf(softc->dev, "Error: completion failed"
		      " tail:0x%x, head:0x%x.\n",
		      ctrl->cmd_tail, ctrl->cmd_head);
	amdvi_dump_cmds(softc);
}