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
struct TYPE_2__ {int /*<<< orphan*/  et_arg; int /*<<< orphan*/  (* et_event_cb ) (TYPE_1__*,int /*<<< orphan*/ ) ;scalar_t__ et_active; } ;
struct arm_tmr_softc {TYPE_1__ et; int /*<<< orphan*/  physical; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int GT_CTRL_INT_MASK ; 
 int GT_CTRL_INT_STAT ; 
 int get_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ctrl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arm_tmr_intr(void *arg)
{
	struct arm_tmr_softc *sc;
	int ctrl;

	sc = (struct arm_tmr_softc *)arg;
	ctrl = get_ctrl(sc->physical);
	if (ctrl & GT_CTRL_INT_STAT) {
		ctrl |= GT_CTRL_INT_MASK;
		set_ctrl(ctrl, sc->physical);
	}

	if (sc->et.et_active)
		sc->et.et_event_cb(&sc->et, sc->et.et_arg);

	return (FILTER_HANDLED);
}