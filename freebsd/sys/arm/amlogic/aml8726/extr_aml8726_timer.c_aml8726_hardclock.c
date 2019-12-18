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
struct aml8726_timer_softc {scalar_t__ first_ticks; scalar_t__ period_ticks; TYPE_1__ et; } ;

/* Variables and functions */
 int AML_TIMER_A_EN ; 
 int AML_TIMER_A_PERIODIC ; 
 int /*<<< orphan*/  AML_TIMER_A_REG ; 
 int /*<<< orphan*/  AML_TIMER_LOCK (struct aml8726_timer_softc*) ; 
 int /*<<< orphan*/  AML_TIMER_MUX_REG ; 
 int /*<<< orphan*/  AML_TIMER_UNLOCK (struct aml8726_timer_softc*) ; 
 int CSR_READ_4 (struct aml8726_timer_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_timer_softc*,int /*<<< orphan*/ ,int) ; 
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_hardclock(void *arg)
{
	struct aml8726_timer_softc *sc = (struct aml8726_timer_softc *)arg;

	AML_TIMER_LOCK(sc);

	if (sc->first_ticks != 0 && sc->period_ticks != 0) {
		sc->first_ticks = 0;

		CSR_WRITE_4(sc, AML_TIMER_A_REG, sc->period_ticks);
		CSR_WRITE_4(sc, AML_TIMER_MUX_REG,
		    (CSR_READ_4(sc, AML_TIMER_MUX_REG) |
		    AML_TIMER_A_PERIODIC | AML_TIMER_A_EN));
	}

	AML_TIMER_UNLOCK(sc);

	if (sc->et.et_active)
		sc->et.et_event_cb(&sc->et, sc->et.et_arg);

	return (FILTER_HANDLED);
}