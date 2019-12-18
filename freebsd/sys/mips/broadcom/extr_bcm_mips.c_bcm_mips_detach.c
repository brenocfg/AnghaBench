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
typedef  size_t u_int ;
struct bcm_mips_softc {size_t num_cpuirqs; int /*<<< orphan*/ * cpuirqs; TYPE_1__* isrcs; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  isrc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_mips_fini_cpuirq (struct bcm_mips_softc*,int /*<<< orphan*/ *) ; 
 struct bcm_mips_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_isrc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intr_pic_deregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t nitems (TYPE_1__*) ; 

int
bcm_mips_detach(device_t dev)
{
	struct bcm_mips_softc *sc;

	sc = device_get_softc(dev);

	/* Deregister PIC before performing any other cleanup */
	intr_pic_deregister(dev, 0);

	/* Deregister all interrupt sources */
	for (size_t i = 0; i < nitems(sc->isrcs); i++)
		intr_isrc_deregister(&sc->isrcs[i].isrc);

	/* Free our MIPS CPU interrupt handler state */
	for (u_int i = 0; i < sc->num_cpuirqs; i++)
		bcm_mips_fini_cpuirq(sc, &sc->cpuirqs[i]);

	return (0);
}