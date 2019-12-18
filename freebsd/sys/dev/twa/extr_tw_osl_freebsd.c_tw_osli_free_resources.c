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
struct twa_softc {int /*<<< orphan*/  sysctl_ctxt; struct cdev* ctrl_dev; int /*<<< orphan*/ * reg_res; int /*<<< orphan*/  reg_res_id; int /*<<< orphan*/  bus_dev; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/  irq_res_id; scalar_t__ parent_tag; scalar_t__ ioctl_tag; scalar_t__ dma_tag; scalar_t__ cmd_tag; int /*<<< orphan*/  cmd_map; scalar_t__ dma_mem; scalar_t__ non_dma_mem; scalar_t__ req_ctx_buf; scalar_t__ ioctl_map; } ;
struct tw_osli_req_context {scalar_t__ dma_map; int /*<<< orphan*/  ioctl_wake_timeout_lock; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  TW_VOID ;
typedef  int /*<<< orphan*/  TW_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TW_OSLI_FREE_Q ; 
 int /*<<< orphan*/  TW_OSLI_MALLOC_CLASS ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_dev (struct cdev*) ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tw_osli_cam_detach (struct twa_softc*) ; 
 int /*<<< orphan*/  tw_osli_dbg_dprintf (int,struct twa_softc*,char*,...) ; 
 struct tw_osli_req_context* tw_osli_req_q_remove_head (struct twa_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twa_teardown_intr (struct twa_softc*) ; 

__attribute__((used)) static TW_VOID
tw_osli_free_resources(struct twa_softc *sc)
{
	struct tw_osli_req_context	*req;
	TW_INT32			error = 0;

	tw_osli_dbg_dprintf(3, sc, "entered");

	/* Detach from CAM */
	tw_osli_cam_detach(sc);

	if (sc->req_ctx_buf)
		while ((req = tw_osli_req_q_remove_head(sc, TW_OSLI_FREE_Q)) !=
			NULL) {
			mtx_destroy(req->ioctl_wake_timeout_lock);

			if ((error = bus_dmamap_destroy(sc->dma_tag,
					req->dma_map)))
				tw_osli_dbg_dprintf(1, sc,
					"dmamap_destroy(dma) returned %d",
					error);
		}

	if ((sc->ioctl_tag) && (sc->ioctl_map))
		if ((error = bus_dmamap_destroy(sc->ioctl_tag, sc->ioctl_map)))
			tw_osli_dbg_dprintf(1, sc,
				"dmamap_destroy(ioctl) returned %d", error);

	/* Free all memory allocated so far. */
	if (sc->req_ctx_buf)
		free(sc->req_ctx_buf, TW_OSLI_MALLOC_CLASS);

	if (sc->non_dma_mem)
		free(sc->non_dma_mem, TW_OSLI_MALLOC_CLASS);

	if (sc->dma_mem) {
		bus_dmamap_unload(sc->cmd_tag, sc->cmd_map);
		bus_dmamem_free(sc->cmd_tag, sc->dma_mem,
			sc->cmd_map);
	}
	if (sc->cmd_tag)
		if ((error = bus_dma_tag_destroy(sc->cmd_tag)))
			tw_osli_dbg_dprintf(1, sc,
				"dma_tag_destroy(cmd) returned %d", error);

	if (sc->dma_tag)
		if ((error = bus_dma_tag_destroy(sc->dma_tag)))
			tw_osli_dbg_dprintf(1, sc,
				"dma_tag_destroy(dma) returned %d", error);

	if (sc->ioctl_tag)
		if ((error = bus_dma_tag_destroy(sc->ioctl_tag)))
			tw_osli_dbg_dprintf(1, sc,
				"dma_tag_destroy(ioctl) returned %d", error);

	if (sc->parent_tag)
		if ((error = bus_dma_tag_destroy(sc->parent_tag)))
			tw_osli_dbg_dprintf(1, sc,
				"dma_tag_destroy(parent) returned %d", error);


	/* Disconnect the interrupt handler. */
	if ((error = twa_teardown_intr(sc)))
			tw_osli_dbg_dprintf(1, sc,
				"teardown_intr returned %d", error);

	if (sc->irq_res != NULL)
		if ((error = bus_release_resource(sc->bus_dev,
				SYS_RES_IRQ, sc->irq_res_id, sc->irq_res)))
			tw_osli_dbg_dprintf(1, sc,
				"release_resource(irq) returned %d", error);


	/* Release the register window mapping. */
	if (sc->reg_res != NULL)
		if ((error = bus_release_resource(sc->bus_dev,
				SYS_RES_MEMORY, sc->reg_res_id, sc->reg_res)))
			tw_osli_dbg_dprintf(1, sc,
				"release_resource(io) returned %d", error);


	/* Destroy the control device. */
	if (sc->ctrl_dev != (struct cdev *)NULL)
		destroy_dev(sc->ctrl_dev);

	if ((error = sysctl_ctx_free(&sc->sysctl_ctxt)))
		tw_osli_dbg_dprintf(1, sc,
			"sysctl_ctx_free returned %d", error);

}