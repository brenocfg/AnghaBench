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
struct amdvi_softc {int event_max; scalar_t__ event; int /*<<< orphan*/  dev; struct amdvi_ctrl* ctrl; } ;
struct amdvi_event {int dummy; } ;
struct TYPE_2__ {int len; int base; } ;
struct amdvi_ctrl {scalar_t__ evt_tail; scalar_t__ evt_head; TYPE_1__ event; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_AMDVI ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 uintptr_t PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int vtophys (scalar_t__) ; 

__attribute__((used)) static int
amdvi_init_event(struct amdvi_softc *softc)
{
	struct amdvi_ctrl *ctrl;

	ctrl = softc->ctrl;
	ctrl->event.len = 8;
	softc->event_max = 1 << ctrl->event.len;
	softc->event = malloc(sizeof(struct amdvi_event) *
	    softc->event_max, M_AMDVI, M_WAITOK | M_ZERO);
	if ((uintptr_t)softc->event & PAGE_MASK) {
		device_printf(softc->dev, "Event buffer not aligned on page.");
		return (false);
	}
	ctrl->event.base = vtophys(softc->event) / PAGE_SIZE;

	/* Reset the pointers. */
	ctrl->evt_head = 0;
	ctrl->evt_tail = 0;

	return (0);
}