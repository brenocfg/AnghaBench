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
struct tr_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/  irq; int /*<<< orphan*/  irqid; int /*<<< orphan*/  ih; int /*<<< orphan*/  reg; int /*<<< orphan*/  regid; int /*<<< orphan*/  regtype; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct tr_info*,int /*<<< orphan*/ ) ; 
 struct tr_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tr_pci_detach(device_t dev)
{
	int r;
	struct tr_info *tr;

	r = pcm_unregister(dev);
	if (r)
		return r;

	tr = pcm_getdevinfo(dev);
	bus_release_resource(dev, tr->regtype, tr->regid, tr->reg);
	bus_teardown_intr(dev, tr->irq, tr->ih);
	bus_release_resource(dev, SYS_RES_IRQ, tr->irqid, tr->irq);
	bus_dma_tag_destroy(tr->parent_dmat);
	snd_mtxfree(tr->lock);
	free(tr, M_DEVBUF);

	return 0;
}