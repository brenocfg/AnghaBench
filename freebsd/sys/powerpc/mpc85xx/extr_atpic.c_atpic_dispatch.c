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
typedef  int uint8_t ;
struct trapframe {int dummy; } ;
struct atpic_softc {int /*<<< orphan*/ * sc_vector; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATPIC_MASTER ; 
 int /*<<< orphan*/  ATPIC_SLAVE ; 
 int OCW3_P ; 
 int OCW3_RR ; 
 int OCW3_SEL ; 
 int atpic_read (struct atpic_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atpic_write (struct atpic_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct atpic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerpc_dispatch_intr (int /*<<< orphan*/ ,struct trapframe*) ; 

__attribute__((used)) static void
atpic_dispatch(device_t dev, struct trapframe *tf)
{
	struct atpic_softc *sc;
	uint8_t irq;

	sc = device_get_softc(dev);
	atpic_write(sc, ATPIC_MASTER, 0, OCW3_SEL | OCW3_P);
	irq = atpic_read(sc, ATPIC_MASTER, 0);
	atpic_write(sc, ATPIC_MASTER, 0, OCW3_SEL | OCW3_RR);
	if ((irq & 0x80) == 0)
		return;

	if (irq == 0x82) {
		atpic_write(sc, ATPIC_SLAVE, 0, OCW3_SEL | OCW3_P);
		irq = atpic_read(sc, ATPIC_SLAVE, 0) + 8;
		atpic_write(sc, ATPIC_SLAVE, 0, OCW3_SEL | OCW3_RR);
		if ((irq & 0x80) == 0)
			return;
	}

	powerpc_dispatch_intr(sc->sc_vector[irq & 0x0f], tf);
}