#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ida_softc {int /*<<< orphan*/  lock; int /*<<< orphan*/ * regs; int /*<<< orphan*/  regs_res_id; int /*<<< orphan*/  regs_res_type; int /*<<< orphan*/  dev; int /*<<< orphan*/ * parent_dmat; int /*<<< orphan*/ * irq; int /*<<< orphan*/  irq_res_type; TYPE_1__* qcbs; int /*<<< orphan*/ * hwqcb_dmat; int /*<<< orphan*/  hwqcb_dmamap; scalar_t__ hwqcbs; scalar_t__ hwqcb_busaddr; int /*<<< orphan*/ * buffer_dmat; int /*<<< orphan*/  ch; int /*<<< orphan*/ * ih; } ;
struct TYPE_2__ {int /*<<< orphan*/  dmamap; } ;

/* Variables and functions */
 int IDA_QCB_MAX ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
ida_free(struct ida_softc *ida)
{
	int i;

	if (ida->ih != NULL)
		bus_teardown_intr(ida->dev, ida->irq, ida->ih);

	mtx_lock(&ida->lock);
	callout_stop(&ida->ch);
	mtx_unlock(&ida->lock);
	callout_drain(&ida->ch);

	if (ida->buffer_dmat) {
		for (i = 0; i < IDA_QCB_MAX; i++)
			bus_dmamap_destroy(ida->buffer_dmat, ida->qcbs[i].dmamap);
		bus_dma_tag_destroy(ida->buffer_dmat);
	}

	if (ida->hwqcb_dmat) {
		if (ida->hwqcb_busaddr)
			bus_dmamap_unload(ida->hwqcb_dmat, ida->hwqcb_dmamap);
		if (ida->hwqcbs)
			bus_dmamem_free(ida->hwqcb_dmat, ida->hwqcbs,
			    ida->hwqcb_dmamap);
		bus_dma_tag_destroy(ida->hwqcb_dmat);
	}

	if (ida->qcbs != NULL)
		free(ida->qcbs, M_DEVBUF);

	if (ida->irq != NULL)
		bus_release_resource(ida->dev, ida->irq_res_type,
		    0, ida->irq);

	if (ida->parent_dmat != NULL)
		bus_dma_tag_destroy(ida->parent_dmat);

	if (ida->regs != NULL)
		bus_release_resource(ida->dev, ida->regs_res_type,
		    ida->regs_res_id, ida->regs);

	mtx_destroy(&ida->lock);
}