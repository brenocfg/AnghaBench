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
struct pqmdio_softc {int /*<<< orphan*/  sc_lock; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pqmdio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pqmdio_detach(device_t dev)
{
	struct pqmdio_softc *sc;

	sc = device_get_softc(dev);

	mtx_destroy(&sc->sc_lock);

	return (0);
}