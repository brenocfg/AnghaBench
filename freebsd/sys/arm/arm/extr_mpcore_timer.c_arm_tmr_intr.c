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
struct arm_tmr_softc {TYPE_1__ et; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  PRV_TIMER_INTR ; 
 int /*<<< orphan*/  PRV_TIMER_INTR_EVENT ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmr_prv_write_4 (struct arm_tmr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arm_tmr_intr(void *arg)
{
	struct arm_tmr_softc *sc;

	sc = arg;
	tmr_prv_write_4(sc, PRV_TIMER_INTR, PRV_TIMER_INTR_EVENT);
	if (sc->et.et_active)
		sc->et.et_event_cb(&sc->et, sc->et.et_arg);
	return (FILTER_HANDLED);
}