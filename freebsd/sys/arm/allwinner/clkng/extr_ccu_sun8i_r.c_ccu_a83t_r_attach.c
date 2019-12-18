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
struct aw_ccung_softc {void* nclks; void* clks; void* ngates; void* gates; void* nresets; void* resets; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 void* a83t_clks ; 
 int aw_ccung_attach (int /*<<< orphan*/ ) ; 
 void* ccu_sun8i_r_gates ; 
 void* ccu_sun8i_r_resets ; 
 struct aw_ccung_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 void* nitems (void*) ; 

__attribute__((used)) static int
ccu_a83t_r_attach(device_t dev)
{
	struct aw_ccung_softc *sc;

	sc = device_get_softc(dev);

	sc->resets = ccu_sun8i_r_resets;
	sc->nresets = nitems(ccu_sun8i_r_resets);
	sc->gates = ccu_sun8i_r_gates;
	sc->ngates = nitems(ccu_sun8i_r_gates);
	sc->clks = a83t_clks;
	sc->nclks = nitems(a83t_clks);

	return (aw_ccung_attach(dev));
}