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
struct hpet_timer {scalar_t__ pcpu_master; size_t* pcpu_slaves; int caps; int /*<<< orphan*/  num; int /*<<< orphan*/  mode; struct hpet_softc* sc; } ;
struct hpet_softc {int /*<<< orphan*/  mem_res; struct hpet_timer* t; } ;
struct eventtimer {scalar_t__ et_priv; } ;

/* Variables and functions */
 int HPET_TCNF_INT_ENB ; 
 int HPET_TCNF_TYPE ; 
 int /*<<< orphan*/  HPET_TIMER_CAP_CNF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_STOPPED ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t curcpu ; 

__attribute__((used)) static int
hpet_stop(struct eventtimer *et)
{
	struct hpet_timer *mt = (struct hpet_timer *)et->et_priv;
	struct hpet_timer *t;
	struct hpet_softc *sc = mt->sc;

	t = (mt->pcpu_master < 0) ? mt : &sc->t[mt->pcpu_slaves[curcpu]];
	t->mode = TIMER_STOPPED;
	t->caps &= ~(HPET_TCNF_INT_ENB | HPET_TCNF_TYPE);
	bus_write_4(sc->mem_res, HPET_TIMER_CAP_CNF(t->num), t->caps);
	return (0);
}