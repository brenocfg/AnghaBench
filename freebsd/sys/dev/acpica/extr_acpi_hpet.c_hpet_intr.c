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
struct hpet_softc {int useirq; int num_timers; int /*<<< orphan*/ * t; int /*<<< orphan*/  mem_res; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int FILTER_STRAY ; 
 int /*<<< orphan*/  HPET_ISR ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hpet_intr_single (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hpet_intr(void *arg)
{
	struct hpet_softc *sc = (struct hpet_softc *)arg;
	int i;
	uint32_t val;

	val = bus_read_4(sc->mem_res, HPET_ISR);
	if (val) {
		bus_write_4(sc->mem_res, HPET_ISR, val);
		val &= sc->useirq;
		for (i = 0; i < sc->num_timers; i++) {
			if ((val & (1 << i)) == 0)
				continue;
			hpet_intr_single(&sc->t[i]);
		}
		return (FILTER_HANDLED);
	}
	return (FILTER_STRAY);
}