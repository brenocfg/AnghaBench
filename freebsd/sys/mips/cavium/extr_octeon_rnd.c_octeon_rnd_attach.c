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
struct octeon_rnd_softc {int /*<<< orphan*/  sc_callout; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct octeon_rnd_softc*) ; 
 int /*<<< orphan*/  cvmx_rng_enable () ; 
 struct octeon_rnd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  octeon_rnd_harvest ; 

__attribute__((used)) static int
octeon_rnd_attach(device_t dev)
{
	struct octeon_rnd_softc *sc;

	sc = device_get_softc(dev);
	callout_init(&sc->sc_callout, 1);
	callout_reset(&sc->sc_callout, hz * 5, octeon_rnd_harvest, sc);

	cvmx_rng_enable();

	return (0);
}