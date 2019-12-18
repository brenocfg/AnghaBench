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
struct ps3disk_softc {int sc_nregs; int /*<<< orphan*/ * sc_reg; int /*<<< orphan*/ * sc_disk; int /*<<< orphan*/  sc_irq; int /*<<< orphan*/  sc_irqid; int /*<<< orphan*/  sc_irqctx; int /*<<< orphan*/  sc_dmatag; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_PS3DISK ; 
 int /*<<< orphan*/  PS3DISK_LOCK_DESTROY (struct ps3disk_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ps3disk_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ps3disk_detach(device_t dev)
{
	struct ps3disk_softc *sc = device_get_softc(dev);
	int i;

	for (i = 0; i < sc->sc_nregs; i++)
		disk_destroy(sc->sc_disk[i]);

	bus_dma_tag_destroy(sc->sc_dmatag);

	bus_teardown_intr(dev, sc->sc_irq, sc->sc_irqctx);
	bus_release_resource(dev, SYS_RES_IRQ, sc->sc_irqid, sc->sc_irq);

	free(sc->sc_disk, M_PS3DISK);
	free(sc->sc_reg, M_PS3DISK);

	PS3DISK_LOCK_DESTROY(sc);

	return (0);
}