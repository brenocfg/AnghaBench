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
struct mbuf {struct mbuf* m_nextpkt; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  busdma_map_mbuf_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ *) ; 

void
busdma_map_sg_vec(bus_dma_tag_t tag, bus_dmamap_t map,
    struct mbuf *m, bus_dma_segment_t *segs, int *nsegs)
{

	for (*nsegs = 0; m != NULL ; segs++, *nsegs += 1, m = m->m_nextpkt)
		busdma_map_mbuf_fast(tag, map, m, segs);
}