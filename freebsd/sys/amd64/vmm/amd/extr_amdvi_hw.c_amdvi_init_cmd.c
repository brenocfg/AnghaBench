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
struct amdvi_softc {int cmd_max; scalar_t__ cmd; struct amdvi_ctrl* ctrl; } ;
struct TYPE_2__ {int len; int base; } ;
struct amdvi_ctrl {scalar_t__ cmd_head; scalar_t__ cmd_tail; TYPE_1__ cmd; } ;
struct amdvi_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_AMDVI ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 uintptr_t PAGE_MASK ; 
 int PAGE_SIZE ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int vtophys (scalar_t__) ; 

__attribute__((used)) static int
amdvi_init_cmd(struct amdvi_softc *softc)
{
	struct amdvi_ctrl *ctrl = softc->ctrl;

	ctrl->cmd.len = 8;	/* Use 256 command buffer entries. */
	softc->cmd_max = 1 << ctrl->cmd.len;

	softc->cmd = malloc(sizeof(struct amdvi_cmd) *
	    softc->cmd_max, M_AMDVI, M_WAITOK | M_ZERO);

	if ((uintptr_t)softc->cmd & PAGE_MASK)
		panic("AMDVi: Command buffer not aligned on page boundary.");

	ctrl->cmd.base = vtophys(softc->cmd) / PAGE_SIZE;
	/*
	 * XXX: Reset the h/w pointers in case IOMMU is restarting,
	 * h/w doesn't clear these pointers based on empirical data.
	 */
	ctrl->cmd_tail = 0;
	ctrl->cmd_head = 0;

	return (0);
}