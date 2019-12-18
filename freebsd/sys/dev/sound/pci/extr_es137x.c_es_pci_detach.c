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
struct es_info {scalar_t__ num; int /*<<< orphan*/  lock; int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/  reg; int /*<<< orphan*/  regid; int /*<<< orphan*/  regtype; int /*<<< orphan*/  irq; int /*<<< orphan*/  irqid; int /*<<< orphan*/  ih; int /*<<< orphan*/  poll_timer; scalar_t__ polling; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ES_LOCK (struct es_info*) ; 
 int /*<<< orphan*/  ES_UNLOCK (struct es_info*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct es_info*,int /*<<< orphan*/ ) ; 
 struct es_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
es_pci_detach(device_t dev)
{
	int r;
	struct es_info *es;

	r = pcm_unregister(dev);
	if (r)
		return (r);

	es = pcm_getdevinfo(dev);

	if (es != NULL && es->num != 0) {
		ES_LOCK(es);
		es->polling = 0;
		callout_stop(&es->poll_timer);
		ES_UNLOCK(es);
		callout_drain(&es->poll_timer);
	}

	bus_teardown_intr(dev, es->irq, es->ih);
	bus_release_resource(dev, SYS_RES_IRQ, es->irqid, es->irq);
	bus_release_resource(dev, es->regtype, es->regid, es->reg);
	bus_dma_tag_destroy(es->parent_dmat);
	snd_mtxfree(es->lock);
	free(es, M_DEVBUF);

	return (0);
}