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
struct fman_softc {scalar_t__ err_irq_res; int /*<<< orphan*/  err_irq_rid; scalar_t__ irq_res; int /*<<< orphan*/  irq_rid; scalar_t__ mem_res; int /*<<< orphan*/  mem_rid; scalar_t__ fm_handle; scalar_t__ muram_handle; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FM_Free (scalar_t__) ; 
 int /*<<< orphan*/  FM_MURAM_Free (scalar_t__) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct fman_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
fman_detach(device_t dev)
{
	struct fman_softc *sc;

	sc = device_get_softc(dev);

	if (sc->muram_handle) {
		FM_MURAM_Free(sc->muram_handle);
	}

	if (sc->fm_handle) {
		FM_Free(sc->fm_handle);
	}

	if (sc->mem_res) {
		bus_release_resource(dev, SYS_RES_MEMORY, sc->mem_rid,
		    sc->mem_res);
	}

	if (sc->irq_res) {
		bus_release_resource(dev, SYS_RES_IRQ, sc->irq_rid,
		    sc->irq_res);
	}

	if (sc->irq_res) {
		bus_release_resource(dev, SYS_RES_IRQ, sc->err_irq_rid,
		    sc->err_irq_res);
	}

	return (0);
}