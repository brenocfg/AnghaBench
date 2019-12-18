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
typedef  int /*<<< orphan*/  uint8_t ;
struct amdvi_softc {int /*<<< orphan*/ * cmd; struct amdvi_ctrl* ctrl; } ;
struct amdvi_ctrl {int cmd_tail; } ;
struct amdvi_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (struct amdvi_softc*,char*) ; 

__attribute__((used)) static struct amdvi_cmd *
amdvi_get_cmd_tail(struct amdvi_softc *softc)
{
	struct amdvi_ctrl *ctrl;
	struct amdvi_cmd *tail;

	KASSERT(softc, ("softc is NULL"));
	KASSERT(softc->cmd != NULL, ("cmd is NULL"));

	ctrl = softc->ctrl;
	KASSERT(ctrl != NULL, ("ctrl is NULL"));

	tail = (struct amdvi_cmd *)((uint8_t *)softc->cmd +
	    ctrl->cmd_tail);

	return (tail);
}