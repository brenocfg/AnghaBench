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
struct fsl_pcib_softc {int /*<<< orphan*/  sc_cfg_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 struct fsl_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fsl_pcib_detach(device_t dev)
{
	struct fsl_pcib_softc *sc;

	sc = device_get_softc(dev);

	mtx_destroy(&sc->sc_cfg_mtx);

	return (bus_generic_detach(dev));
}