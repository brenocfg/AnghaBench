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
struct aml8726_rng_softc {int ticks; int /*<<< orphan*/  co; int /*<<< orphan*/  res; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  aml8726_rng_harvest ; 
 int /*<<< orphan*/  aml8726_rng_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct aml8726_rng_softc*) ; 
 struct aml8726_rng_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 

__attribute__((used)) static int
aml8726_rng_attach(device_t dev)
{
	struct aml8726_rng_softc *sc = device_get_softc(dev);

	sc->dev = dev;

	if (bus_alloc_resources(dev, aml8726_rng_spec, sc->res)) {
		device_printf(dev, "can not allocate resources for device\n");
		return (ENXIO);
	}

	/* Install a periodic collector for the RNG */
	if (hz > 100)
		sc->ticks = hz / 100;
	else
		sc->ticks = 1;

	callout_init(&sc->co, 1);
	callout_reset(&sc->co, sc->ticks, aml8726_rng_harvest, sc);

	return (0);
}