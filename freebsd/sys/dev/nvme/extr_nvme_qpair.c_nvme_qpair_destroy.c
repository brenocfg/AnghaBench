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
struct nvme_tracker {int /*<<< orphan*/  payload_dma_map; } ;
struct nvme_qpair {scalar_t__ dma_tag_payload; scalar_t__ dma_tag; int /*<<< orphan*/  free_tr; struct nvme_tracker* act_tr; int /*<<< orphan*/  queuemem_map; int /*<<< orphan*/ * cmd; scalar_t__ res; TYPE_1__* ctrlr; int /*<<< orphan*/  lock; scalar_t__ tag; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NVME ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct nvme_tracker* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nvme_tracker*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  free_domain (struct nvme_tracker*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_rid (scalar_t__) ; 
 int /*<<< orphan*/  tailq ; 

__attribute__((used)) static void
nvme_qpair_destroy(struct nvme_qpair *qpair)
{
	struct nvme_tracker	*tr;

	if (qpair->tag)
		bus_teardown_intr(qpair->ctrlr->dev, qpair->res, qpair->tag);

	if (mtx_initialized(&qpair->lock))
		mtx_destroy(&qpair->lock);

	if (qpair->res)
		bus_release_resource(qpair->ctrlr->dev, SYS_RES_IRQ,
		    rman_get_rid(qpair->res), qpair->res);

	if (qpair->cmd != NULL) {
		bus_dmamap_unload(qpair->dma_tag, qpair->queuemem_map);
		bus_dmamem_free(qpair->dma_tag, qpair->cmd,
		    qpair->queuemem_map);
	}

	if (qpair->act_tr)
		free_domain(qpair->act_tr, M_NVME);

	while (!TAILQ_EMPTY(&qpair->free_tr)) {
		tr = TAILQ_FIRST(&qpair->free_tr);
		TAILQ_REMOVE(&qpair->free_tr, tr, tailq);
		bus_dmamap_destroy(qpair->dma_tag_payload,
		    tr->payload_dma_map);
		free_domain(tr, M_NVME);
	}

	if (qpair->dma_tag)
		bus_dma_tag_destroy(qpair->dma_tag);

	if (qpair->dma_tag_payload)
		bus_dma_tag_destroy(qpair->dma_tag_payload);
}