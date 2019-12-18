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
struct xgbe_ring_data {int dummy; } ;
struct xgbe_ring {unsigned int rdesc_count; int /*<<< orphan*/ * rdesc; int /*<<< orphan*/ * rdesc_dmat; int /*<<< orphan*/ * rdesc_map; int /*<<< orphan*/ * rdata; int /*<<< orphan*/ * mbuf_dmat; int /*<<< orphan*/ * mbuf_map; } ;
struct xgbe_prv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_AXGBE ; 
 struct xgbe_ring_data* XGBE_GET_DESC_DATA (struct xgbe_ring*,unsigned int) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_unmap_rdata (struct xgbe_prv_data*,struct xgbe_ring_data*) ; 

__attribute__((used)) static void xgbe_free_ring(struct xgbe_prv_data *pdata,
			   struct xgbe_ring *ring)
{
	struct xgbe_ring_data *rdata;
	unsigned int i;

	if (!ring)
		return;

	bus_dmamap_destroy(ring->mbuf_dmat, ring->mbuf_map);
	bus_dma_tag_destroy(ring->mbuf_dmat);

	ring->mbuf_map = NULL;
	ring->mbuf_dmat = NULL;

	if (ring->rdata) {
		for (i = 0; i < ring->rdesc_count; i++) {
			rdata = XGBE_GET_DESC_DATA(ring, i);
			xgbe_unmap_rdata(pdata, rdata);
		}

		free(ring->rdata, M_AXGBE);
		ring->rdata = NULL;
	}

	bus_dmamap_unload(ring->rdesc_dmat, ring->rdesc_map);
	bus_dmamem_free(ring->rdesc_dmat, ring->rdesc, ring->rdesc_map);
	bus_dma_tag_destroy(ring->rdesc_dmat);

	ring->rdesc_map = NULL;
	ring->rdesc_dmat = NULL;
	ring->rdesc = NULL;
}