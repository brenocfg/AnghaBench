#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cmd_sema; int /*<<< orphan*/  queue_mtx; scalar_t__ configured; scalar_t__ iores; int /*<<< orphan*/  rid; int /*<<< orphan*/  iotype; int /*<<< orphan*/  dev; scalar_t__ irqres; int /*<<< orphan*/  irqrid; scalar_t__ irqcookie; scalar_t__ adapter_dmatag; } ;
typedef  TYPE_1__ ips_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ips_pci_free(ips_softc_t *sc)
{
	if(sc->adapter_dmatag)
		bus_dma_tag_destroy(sc->adapter_dmatag);
	if(sc->irqcookie)
                bus_teardown_intr(sc->dev, sc->irqres, sc->irqcookie);
        if(sc->irqres)
               bus_release_resource(sc->dev, SYS_RES_IRQ, sc->irqrid, sc->irqres);
        if(sc->iores)
                bus_release_resource(sc->dev, sc->iotype, sc->rid, sc->iores);
	sc->configured = 0;
	mtx_destroy(&sc->queue_mtx);
	sema_destroy(&sc->cmd_sema);
	return 0;
}