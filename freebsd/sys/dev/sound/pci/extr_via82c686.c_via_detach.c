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
struct via_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  sgd_dmat; int /*<<< orphan*/  sgd_dmamap; int /*<<< orphan*/  sgd_table; int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/  irq; int /*<<< orphan*/  irqid; int /*<<< orphan*/  ih; int /*<<< orphan*/  reg; int /*<<< orphan*/  regid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct via_info*,int /*<<< orphan*/ ) ; 
 struct via_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
via_detach(device_t dev)
{
	int r;
	struct via_info *via = NULL;

	r = pcm_unregister(dev);
	if (r)
		return r;

	via = pcm_getdevinfo(dev);
	bus_release_resource(dev, SYS_RES_IOPORT, via->regid, via->reg);
	bus_teardown_intr(dev, via->irq, via->ih);
	bus_release_resource(dev, SYS_RES_IRQ, via->irqid, via->irq);
	bus_dma_tag_destroy(via->parent_dmat);
	bus_dmamap_unload(via->sgd_dmat, via->sgd_dmamap);
	bus_dmamem_free(via->sgd_dmat, via->sgd_table, via->sgd_dmamap);
	bus_dma_tag_destroy(via->sgd_dmat);
	snd_mtxfree(via->lock);
	free(via, M_DEVBUF);
	return 0;
}