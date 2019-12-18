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
typedef  int u_int ;
struct atpic_softc {int* sc_mask; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 size_t ATPIC_MASTER ; 
 size_t ATPIC_SLAVE ; 
 int /*<<< orphan*/  atpic_write (struct atpic_softc*,size_t,int,int) ; 
 struct atpic_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
atpic_mask(device_t dev, u_int irq)
{
	struct atpic_softc *sc;

	sc = device_get_softc(dev);
	if (irq > 7) {
		sc->sc_mask[ATPIC_SLAVE] |= 1 << (irq - 8);
		atpic_write(sc, ATPIC_SLAVE, 1, sc->sc_mask[ATPIC_SLAVE]);
	} else {
		sc->sc_mask[ATPIC_MASTER] |= 1 << irq;
		atpic_write(sc, ATPIC_MASTER, 1, sc->sc_mask[ATPIC_MASTER]);
	}
}