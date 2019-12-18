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
 int aw_ccung_attach (int /*<<< orphan*/ ) ; 
 struct aw_ccung_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 void* h6_ccu_clks ; 
 void* h6_ccu_gates ; 
 void* h6_ccu_resets ; 
 void* nitems (void*) ; 

__attribute__((used)) static int
ccu_h6_attach(device_t dev)
{
	struct aw_ccung_softc *sc;

	sc = device_get_softc(dev);

	sc->resets = h6_ccu_resets;
	sc->nresets = nitems(h6_ccu_resets);
	sc->gates = h6_ccu_gates;
	sc->ngates = nitems(h6_ccu_gates);
	sc->clks = h6_ccu_clks;
	sc->nclks = nitems(h6_ccu_clks);

	return (aw_ccung_attach(dev));
}