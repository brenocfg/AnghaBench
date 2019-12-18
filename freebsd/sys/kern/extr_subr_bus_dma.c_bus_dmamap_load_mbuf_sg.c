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
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
 int BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  _bus_dmamap_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int _bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ *,int*,int) ; 

int
bus_dmamap_load_mbuf_sg(bus_dma_tag_t dmat, bus_dmamap_t map, struct mbuf *m0,
    bus_dma_segment_t *segs, int *nsegs, int flags)
{
	int error;

	flags |= BUS_DMA_NOWAIT;
	*nsegs = -1;
	error = _bus_dmamap_load_mbuf_sg(dmat, map, m0, segs, nsegs, flags);
	++*nsegs;
	_bus_dmamap_complete(dmat, map, segs, *nsegs, error);
	return (error);
}