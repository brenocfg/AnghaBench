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
struct amdvi_softc {struct amdvi_ctrl* ctrl; } ;
struct TYPE_2__ {int base; int size; } ;
struct amdvi_ctrl {TYPE_1__ dte; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  amdvi_dte ; 
 int vtophys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amdvi_init_dte(struct amdvi_softc *softc)
{
	struct amdvi_ctrl *ctrl;

	ctrl = softc->ctrl;
	ctrl->dte.base = vtophys(amdvi_dte) / PAGE_SIZE;
	ctrl->dte.size = 0x1FF;		/* 2MB device table. */

	return (0);
}