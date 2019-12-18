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
struct sc_info {int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/  irq; int /*<<< orphan*/  irqid; int /*<<< orphan*/  ih; int /*<<< orphan*/  mem; int /*<<< orphan*/  memid; int /*<<< orphan*/  reg; int /*<<< orphan*/  regid; int /*<<< orphan*/  regtype; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4281_power (struct sc_info*,int) ; 
 int /*<<< orphan*/  free (struct sc_info*,int /*<<< orphan*/ ) ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cs4281_pci_detach(device_t dev)
{
    int r;
    struct sc_info *sc;

    r = pcm_unregister(dev);
    if (r)
	return r;

    sc = pcm_getdevinfo(dev);

    /* power off */
    cs4281_power(sc, 3);

    bus_release_resource(dev, sc->regtype, sc->regid, sc->reg);
    bus_release_resource(dev, SYS_RES_MEMORY, sc->memid, sc->mem);
    bus_teardown_intr(dev, sc->irq, sc->ih);
    bus_release_resource(dev, SYS_RES_IRQ, sc->irqid, sc->irq);
    bus_dma_tag_destroy(sc->parent_dmat);
    free(sc, M_DEVBUF);

    return 0;
}