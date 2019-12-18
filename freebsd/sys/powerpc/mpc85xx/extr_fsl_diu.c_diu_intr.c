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
struct diu_softc {int /*<<< orphan*/ * res; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIU_INT_STATUS ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
diu_intr(void *arg)
{
	struct diu_softc *sc;
	int reg;

	sc = arg;

	/* Ack interrupts */
	reg = bus_read_4(sc->res[0], DIU_INT_STATUS);
	bus_write_4(sc->res[0], DIU_INT_STATUS, reg);

	/* TODO interrupt handler */
}