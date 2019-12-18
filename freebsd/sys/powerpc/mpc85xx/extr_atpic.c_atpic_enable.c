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
typedef  size_t u_int ;
struct atpic_softc {size_t* sc_vector; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  atpic_unmask (int /*<<< orphan*/ ,size_t) ; 
 struct atpic_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
atpic_enable(device_t dev, u_int irq, u_int vector)
{
	struct atpic_softc *sc;

	sc = device_get_softc(dev);
	sc->sc_vector[irq] = vector;
	atpic_unmask(dev, irq);
}