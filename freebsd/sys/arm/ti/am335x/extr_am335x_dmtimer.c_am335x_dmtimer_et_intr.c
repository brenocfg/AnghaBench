#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  et_arg; int /*<<< orphan*/  (* et_event_cb ) (TYPE_2__*,int /*<<< orphan*/ ) ;scalar_t__ et_active; } ;
struct TYPE_3__ {TYPE_2__ et; } ;
struct am335x_dmtimer_softc {TYPE_1__ func; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMTIMER_WRITE4 (struct am335x_dmtimer_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMT_IRQSTATUS ; 
 int /*<<< orphan*/  DMT_IRQ_OVF ; 
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
am335x_dmtimer_et_intr(void *arg)
{
	struct am335x_dmtimer_softc *sc;

	sc = arg;

	/* Ack the interrupt, and invoke the callback if it's still enabled. */
	DMTIMER_WRITE4(sc, DMT_IRQSTATUS, DMT_IRQ_OVF);
	if (sc->func.et.et_active)
		sc->func.et.et_event_cb(&sc->func.et, sc->func.et.et_arg);

	return (FILTER_HANDLED);
}