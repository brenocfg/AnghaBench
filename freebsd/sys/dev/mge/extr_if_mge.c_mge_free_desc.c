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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct mge_softc {int /*<<< orphan*/  mge_desc_dtag; } ;
struct mge_desc_wrapper {scalar_t__ desc_dmap; int /*<<< orphan*/  mge_desc; int /*<<< orphan*/  buffer; scalar_t__ buffer_dmap; } ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mge_free_desc(struct mge_softc *sc, struct mge_desc_wrapper* tab,
    uint32_t size, bus_dma_tag_t buffer_tag, uint8_t free_mbufs)
{
	struct mge_desc_wrapper *dw;
	int i;

	for (i = 0; i < size; i++) {
		/* Free RX mbuf */
		dw = &(tab[i]);

		if (dw->buffer_dmap) {
			if (free_mbufs) {
				bus_dmamap_sync(buffer_tag, dw->buffer_dmap,
				    BUS_DMASYNC_POSTREAD);
				bus_dmamap_unload(buffer_tag, dw->buffer_dmap);
			}
			bus_dmamap_destroy(buffer_tag, dw->buffer_dmap);
			if (free_mbufs)
				m_freem(dw->buffer);
		}
		/* Free RX descriptors */
		if (dw->desc_dmap) {
			bus_dmamap_sync(sc->mge_desc_dtag, dw->desc_dmap,
			    BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(sc->mge_desc_dtag, dw->desc_dmap);
			bus_dmamem_free(sc->mge_desc_dtag, dw->mge_desc,
			    dw->desc_dmap);
		}
	}
}