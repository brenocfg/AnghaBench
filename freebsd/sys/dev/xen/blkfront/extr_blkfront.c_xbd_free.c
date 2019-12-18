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
struct xbd_softc {int xbd_max_requests; int xbd_max_request_indirectpages; int /*<<< orphan*/  xen_intr_handle; int /*<<< orphan*/  xbd_io_dmat; struct xbd_command* xbd_shadow; int /*<<< orphan*/  xbd_io_lock; int /*<<< orphan*/  xbd_state; } ;
struct xbd_command {int /*<<< orphan*/  cm_map; int /*<<< orphan*/ * cm_indirectionpages; int /*<<< orphan*/ * cm_indirectionrefs; struct xbd_command* cm_sg_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_XENBLOCKFRONT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  XBD_Q_COMPLETE ; 
 int /*<<< orphan*/  XBD_Q_FREE ; 
 int /*<<< orphan*/  XBD_Q_READY ; 
 int /*<<< orphan*/  XBD_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  contigfree (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct xbd_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnttab_end_foreign_access_references (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xbd_free_ring (struct xbd_softc*) ; 
 int /*<<< orphan*/  xbd_initq_cm (struct xbd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_intr_unbind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void 
xbd_free(struct xbd_softc *sc)
{
	int i;
	
	/* Prevent new requests being issued until we fix things up. */
	mtx_lock(&sc->xbd_io_lock);
	sc->xbd_state = XBD_STATE_DISCONNECTED; 
	mtx_unlock(&sc->xbd_io_lock);

	/* Free resources associated with old device channel. */
	xbd_free_ring(sc);
	if (sc->xbd_shadow) {

		for (i = 0; i < sc->xbd_max_requests; i++) {
			struct xbd_command *cm;

			cm = &sc->xbd_shadow[i];
			if (cm->cm_sg_refs != NULL) {
				free(cm->cm_sg_refs, M_XENBLOCKFRONT);
				cm->cm_sg_refs = NULL;
			}

			if (cm->cm_indirectionpages != NULL) {
				gnttab_end_foreign_access_references(
				    sc->xbd_max_request_indirectpages,
				    &cm->cm_indirectionrefs[0]);
				contigfree(cm->cm_indirectionpages, PAGE_SIZE *
				    sc->xbd_max_request_indirectpages,
				    M_XENBLOCKFRONT);
				cm->cm_indirectionpages = NULL;
			}

			bus_dmamap_destroy(sc->xbd_io_dmat, cm->cm_map);
		}
		free(sc->xbd_shadow, M_XENBLOCKFRONT);
		sc->xbd_shadow = NULL;

		bus_dma_tag_destroy(sc->xbd_io_dmat);
		
		xbd_initq_cm(sc, XBD_Q_FREE);
		xbd_initq_cm(sc, XBD_Q_READY);
		xbd_initq_cm(sc, XBD_Q_COMPLETE);
	}
		
	xen_intr_unbind(&sc->xen_intr_handle);

}