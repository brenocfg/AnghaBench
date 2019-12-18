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
typedef  int uint32_t ;
struct hpet_timer {scalar_t__ pcpu_master; size_t* pcpu_slaves; scalar_t__ mode; int div; scalar_t__ irq; int num; int caps; int next; struct hpet_softc* sc; } ;
struct hpet_softc {int freq; int /*<<< orphan*/  mem_res; struct hpet_timer* t; } ;
struct eventtimer {scalar_t__ et_priv; } ;
typedef  int sbintime_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HPET_ISR ; 
 int /*<<< orphan*/  HPET_MAIN_COUNTER ; 
 int HPET_MIN_CYCLES ; 
 int HPET_TCAP_PER_INT ; 
 int HPET_TCNF_INT_ENB ; 
 int HPET_TCNF_TYPE ; 
 int HPET_TCNF_VAL_SET ; 
 int /*<<< orphan*/  HPET_TIMER_CAP_CNF (int) ; 
 int /*<<< orphan*/  HPET_TIMER_COMPARATOR (int) ; 
 scalar_t__ TIMER_ONESHOT ; 
 scalar_t__ TIMER_PERIODIC ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t curcpu ; 

__attribute__((used)) static int
hpet_start(struct eventtimer *et, sbintime_t first, sbintime_t period)
{
	struct hpet_timer *mt = (struct hpet_timer *)et->et_priv;
	struct hpet_timer *t;
	struct hpet_softc *sc = mt->sc;
	uint32_t fdiv, now;

	t = (mt->pcpu_master < 0) ? mt : &sc->t[mt->pcpu_slaves[curcpu]];
	if (period != 0) {
		t->mode = TIMER_PERIODIC;
		t->div = (sc->freq * period) >> 32;
	} else {
		t->mode = TIMER_ONESHOT;
		t->div = 0;
	}
	if (first != 0)
		fdiv = (sc->freq * first) >> 32;
	else
		fdiv = t->div;
	if (t->irq < 0)
		bus_write_4(sc->mem_res, HPET_ISR, 1 << t->num);
	t->caps |= HPET_TCNF_INT_ENB;
	now = bus_read_4(sc->mem_res, HPET_MAIN_COUNTER);
restart:
	t->next = now + fdiv;
	if (t->mode == TIMER_PERIODIC && (t->caps & HPET_TCAP_PER_INT)) {
		t->caps |= HPET_TCNF_TYPE;
		bus_write_4(sc->mem_res, HPET_TIMER_CAP_CNF(t->num),
		    t->caps | HPET_TCNF_VAL_SET);
		bus_write_4(sc->mem_res, HPET_TIMER_COMPARATOR(t->num),
		    t->next);
		bus_write_4(sc->mem_res, HPET_TIMER_COMPARATOR(t->num),
		    t->div);
	} else {
		t->caps &= ~HPET_TCNF_TYPE;
		bus_write_4(sc->mem_res, HPET_TIMER_CAP_CNF(t->num),
		    t->caps);
		bus_write_4(sc->mem_res, HPET_TIMER_COMPARATOR(t->num),
		    t->next);
	}
	now = bus_read_4(sc->mem_res, HPET_MAIN_COUNTER);
	if ((int32_t)(now - t->next + HPET_MIN_CYCLES) >= 0) {
		fdiv *= 2;
		goto restart;
	}
	return (0);
}