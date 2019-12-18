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
struct ess_info {int /*<<< orphan*/ * lock; scalar_t__ parent_dmat; int /*<<< orphan*/ * gp; int /*<<< orphan*/ * mpu; int /*<<< orphan*/ * vc; int /*<<< orphan*/ * sb; int /*<<< orphan*/ * io; int /*<<< orphan*/ * irq; scalar_t__ ih; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  free (struct ess_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ess_release_resources(struct ess_info *sc, device_t dev)
{
    	if (sc->irq) {
		if (sc->ih)
			bus_teardown_intr(dev, sc->irq, sc->ih);
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq);
		sc->irq = NULL;
    	}
    	if (sc->io) {
		bus_release_resource(dev, SYS_RES_IOPORT, PCIR_BAR(0), sc->io);
		sc->io = NULL;
    	}

    	if (sc->sb) {
		bus_release_resource(dev, SYS_RES_IOPORT, PCIR_BAR(1), sc->sb);
		sc->sb = NULL;
    	}

    	if (sc->vc) {
		bus_release_resource(dev, SYS_RES_IOPORT, PCIR_BAR(2), sc->vc);
		sc->vc = NULL;
    	}

    	if (sc->mpu) {
		bus_release_resource(dev, SYS_RES_IOPORT, PCIR_BAR(3), sc->mpu);
		sc->mpu = NULL;
    	}

    	if (sc->gp) {
		bus_release_resource(dev, SYS_RES_IOPORT, PCIR_BAR(4), sc->gp);
		sc->gp = NULL;
    	}

	if (sc->parent_dmat) {
		bus_dma_tag_destroy(sc->parent_dmat);
		sc->parent_dmat = 0;
    	}

#if ESS18XX_MPSAFE == 1
	if (sc->lock) {
		snd_mtxfree(sc->lock);
		sc->lock = NULL;
	}
#endif

    	free(sc, M_DEVBUF);
}