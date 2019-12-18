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
struct ess_info {scalar_t__ parent_dmat; int /*<<< orphan*/ * io_base; int /*<<< orphan*/ * drq2; int /*<<< orphan*/ * drq1; int /*<<< orphan*/ * irq; scalar_t__ ih; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  free (struct ess_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_dma_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ess_release_resources(struct ess_info *sc, device_t dev)
{
    	if (sc->irq) {
    		if (sc->ih)
			bus_teardown_intr(dev, sc->irq, sc->ih);
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq);
		sc->irq = NULL;
    	}
    	if (sc->drq1) {
		isa_dma_release(rman_get_start(sc->drq1));
		bus_release_resource(dev, SYS_RES_DRQ, 0, sc->drq1);
		sc->drq1 = NULL;
    	}
    	if (sc->drq2) {
		isa_dma_release(rman_get_start(sc->drq2));
		bus_release_resource(dev, SYS_RES_DRQ, 1, sc->drq2);
		sc->drq2 = NULL;
    	}
    	if (sc->io_base) {
		bus_release_resource(dev, SYS_RES_IOPORT, 0, sc->io_base);
		sc->io_base = NULL;
    	}
    	if (sc->parent_dmat) {
		bus_dma_tag_destroy(sc->parent_dmat);
		sc->parent_dmat = 0;
    	}
     	free(sc, M_DEVBUF);
}