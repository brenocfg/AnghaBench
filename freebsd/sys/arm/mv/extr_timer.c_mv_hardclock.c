#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  et_arg; int /*<<< orphan*/  (* et_event_cb ) (TYPE_3__*,int /*<<< orphan*/ ) ;scalar_t__ et_active; } ;
struct mv_timer_softc {TYPE_3__ et; } ;
struct TYPE_5__ {TYPE_1__* config; } ;
struct TYPE_4__ {int /*<<< orphan*/  bridge_irq_cause; int /*<<< orphan*/  irq_timer0_clr; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  read_cpu_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* timer_softc ; 
 int /*<<< orphan*/  write_cpu_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_hardclock(void *arg)
{
	struct	mv_timer_softc *sc;
	uint32_t irq_cause;

	irq_cause = read_cpu_ctrl(timer_softc->config->bridge_irq_cause);
	irq_cause &= timer_softc->config->irq_timer0_clr;
	write_cpu_ctrl(timer_softc->config->bridge_irq_cause, irq_cause);

	sc = (struct mv_timer_softc *)arg;
	if (sc->et.et_active)
		sc->et.et_event_cb(&sc->et, sc->et.et_arg);

	return (FILTER_HANDLED);
}