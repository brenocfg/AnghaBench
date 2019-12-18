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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_int ;
struct hpet_timer {scalar_t__ irq; } ;
struct hpet_softc {int num_timers; int /*<<< orphan*/  mem_res; struct hpet_timer* t; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  HPET_TIMER_FSB_ADDR (int) ; 
 int /*<<< orphan*/  HPET_TIMER_FSB_VAL (int) ; 
 int PCIB_MAP_MSI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct hpet_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_disable (struct hpet_softc*) ; 
 int /*<<< orphan*/  hpet_enable (struct hpet_softc*) ; 

__attribute__((used)) static int
hpet_remap_intr(device_t dev, device_t child, u_int irq)
{
	struct hpet_softc *sc = device_get_softc(dev);
	struct hpet_timer *t;
	uint64_t addr;
	uint32_t data;
	int error, i;

	for (i = 0; i < sc->num_timers; i++) {
		t = &sc->t[i];
		if (t->irq != irq)
			continue;
		error = PCIB_MAP_MSI(
		    device_get_parent(device_get_parent(dev)), dev,
		    irq, &addr, &data);
		if (error)
			return (error);
		hpet_disable(sc); /* Stop timer to avoid interrupt loss. */
		bus_write_4(sc->mem_res, HPET_TIMER_FSB_ADDR(i), addr);
		bus_write_4(sc->mem_res, HPET_TIMER_FSB_VAL(i), data);
		hpet_enable(sc);
		return (0);
	}
	return (ENOENT);
}