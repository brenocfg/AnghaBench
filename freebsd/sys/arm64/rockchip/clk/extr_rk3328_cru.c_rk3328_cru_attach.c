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
struct rk_cru_softc {int reset_offset; int reset_num; void* nclks; void* clks; void* ngates; void* gates; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct rk_cru_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 void* nitems (void*) ; 
 void* rk3328_clks ; 
 void* rk3328_gates ; 
 int rk_cru_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rk3328_cru_attach(device_t dev)
{
	struct rk_cru_softc *sc;

	sc = device_get_softc(dev);
	sc->dev = dev;

	sc->gates = rk3328_gates;
	sc->ngates = nitems(rk3328_gates);

	sc->clks = rk3328_clks;
	sc->nclks = nitems(rk3328_clks);

	sc->reset_offset = 0x300;
	sc->reset_num = 184;

	return (rk_cru_attach(dev));
}