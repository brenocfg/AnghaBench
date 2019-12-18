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
typedef  union ccb {int dummy; } ccb ;
struct hpt_iop_srb {int /*<<< orphan*/  timeout; scalar_t__ dma_map; } ;
struct hpt_iop_hba {int /*<<< orphan*/  lock; scalar_t__ bar2_res; int /*<<< orphan*/  bar2_rid; int /*<<< orphan*/  pcidev; scalar_t__ bar0_res; int /*<<< orphan*/  bar0_rid; scalar_t__ irq_res; scalar_t__ parent_dmat; scalar_t__ io_dmat; scalar_t__ srb_dmat; scalar_t__ srb_dmamap; struct hpt_iop_srb** srb; scalar_t__ ctlcfg_dmat; scalar_t__ ctlcfg_dmamap; int /*<<< orphan*/  ctlcfg_ptr; scalar_t__ sim; scalar_t__ irq_handle; scalar_t__ path; scalar_t__ ioctl_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  func_code; } ;
struct ccb_setasync {scalar_t__ callback_arg; int /*<<< orphan*/  callback; scalar_t__ event_enable; TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int HPT_SRB_MAX_QUEUE_SIZE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XPT_SASYNC_CB ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (scalar_t__) ; 
 int /*<<< orphan*/  destroy_dev (scalar_t__) ; 
 int /*<<< orphan*/  hptiop_async ; 
 int /*<<< orphan*/  hptiop_lock_adapter (struct hpt_iop_hba*) ; 
 int /*<<< orphan*/  hptiop_unlock_adapter (struct hpt_iop_hba*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (scalar_t__) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_1__*,scalar_t__,int) ; 

__attribute__((used)) static void hptiop_release_resource(struct hpt_iop_hba *hba)
{
	int i;

	if (hba->ioctl_dev)
		destroy_dev(hba->ioctl_dev);

	if (hba->path) {
		struct ccb_setasync ccb;

		xpt_setup_ccb(&ccb.ccb_h, hba->path, /*priority*/5);
		ccb.ccb_h.func_code = XPT_SASYNC_CB;
		ccb.event_enable = 0;
		ccb.callback = hptiop_async;
		ccb.callback_arg = hba->sim;
		xpt_action((union ccb *)&ccb);
		xpt_free_path(hba->path);
	}

	if (hba->irq_handle)
		bus_teardown_intr(hba->pcidev, hba->irq_res, hba->irq_handle);

	if (hba->sim) {
		hptiop_lock_adapter(hba);
		xpt_bus_deregister(cam_sim_path(hba->sim));
		cam_sim_free(hba->sim, TRUE);
		hptiop_unlock_adapter(hba);
	}

	if (hba->ctlcfg_dmat) {
		bus_dmamap_unload(hba->ctlcfg_dmat, hba->ctlcfg_dmamap);
		bus_dmamem_free(hba->ctlcfg_dmat,
					hba->ctlcfg_ptr, hba->ctlcfg_dmamap);
		bus_dma_tag_destroy(hba->ctlcfg_dmat);
	}

	for (i = 0; i < HPT_SRB_MAX_QUEUE_SIZE; i++) {
		struct hpt_iop_srb *srb = hba->srb[i];
		if (srb->dma_map)
			bus_dmamap_destroy(hba->io_dmat, srb->dma_map);
		callout_drain(&srb->timeout);
	}

	if (hba->srb_dmat) {
		bus_dmamap_unload(hba->srb_dmat, hba->srb_dmamap);
		bus_dmamap_destroy(hba->srb_dmat, hba->srb_dmamap);
		bus_dma_tag_destroy(hba->srb_dmat);
	}

	if (hba->io_dmat)
		bus_dma_tag_destroy(hba->io_dmat);

	if (hba->parent_dmat)
		bus_dma_tag_destroy(hba->parent_dmat);

	if (hba->irq_res)
		bus_release_resource(hba->pcidev, SYS_RES_IRQ,
					0, hba->irq_res);

	if (hba->bar0_res)
		bus_release_resource(hba->pcidev, SYS_RES_MEMORY,
					hba->bar0_rid, hba->bar0_res);
	if (hba->bar2_res)
		bus_release_resource(hba->pcidev, SYS_RES_MEMORY,
					hba->bar2_rid, hba->bar2_res);
	mtx_destroy(&hba->lock);
}