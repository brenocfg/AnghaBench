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
struct bcm_vchiq_softc {int /*<<< orphan*/  lock; int /*<<< orphan*/  mem_res; int /*<<< orphan*/  irq_res; scalar_t__ intr_hl; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct bcm_vchiq_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiq_exit () ; 

__attribute__((used)) static int
bcm_vchiq_detach(device_t dev)
{
	struct bcm_vchiq_softc *sc = device_get_softc(dev);

	vchiq_exit();

	if (sc->intr_hl)
                bus_teardown_intr(dev, sc->irq_res, sc->intr_hl);
	bus_release_resource(dev, SYS_RES_IRQ, 0,
		sc->irq_res);
	bus_release_resource(dev, SYS_RES_MEMORY, 0,
		sc->mem_res);

	mtx_destroy(&sc->lock);

	return (0);
}