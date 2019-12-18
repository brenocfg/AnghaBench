#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nbufs; TYPE_4__* shadow; int /*<<< orphan*/ * lanai; TYPE_1__* info; int /*<<< orphan*/  dmat; int /*<<< orphan*/  mlen; int /*<<< orphan*/  alloc_fail; int /*<<< orphan*/  cl_size; } ;
struct mxge_slice_state {TYPE_2__ rx_big; } ;
struct mbuf {int /*<<< orphan*/  m_len; } ;
typedef  TYPE_2__ mxge_rx_ring_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
struct TYPE_8__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_3__ bus_dma_segment_t ;
struct TYPE_9__ {void* addr_high; void* addr_low; } ;
struct TYPE_6__ {struct mbuf* m; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  MXGE_HIGHPART_TO_U32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MXGE_LOWPART_TO_U32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,TYPE_3__*,int*,int /*<<< orphan*/ ) ; 
 void* htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 
 struct mbuf* m_getjcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxge_submit_8rx (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static int
mxge_get_buf_big(struct mxge_slice_state *ss, bus_dmamap_t map, int idx)
{
	bus_dma_segment_t seg[3];
	struct mbuf *m;
	mxge_rx_ring_t *rx = &ss->rx_big;
	int cnt, err, i;

	m = m_getjcl(M_NOWAIT, MT_DATA, M_PKTHDR, rx->cl_size);
	if (m == NULL) {
		rx->alloc_fail++;
		err = ENOBUFS;
		goto done;
	}
	m->m_len = rx->mlen;
	err = bus_dmamap_load_mbuf_sg(rx->dmat, map, m,
				      seg, &cnt, BUS_DMA_NOWAIT);
	if (err != 0) {
		m_free(m);
		goto done;
	}
	rx->info[idx].m = m;
	rx->shadow[idx].addr_low =
		htobe32(MXGE_LOWPART_TO_U32(seg->ds_addr));
	rx->shadow[idx].addr_high =
		htobe32(MXGE_HIGHPART_TO_U32(seg->ds_addr));

#if MXGE_VIRT_JUMBOS
	for (i = 1; i < cnt; i++) {
		rx->shadow[idx + i].addr_low =
			htobe32(MXGE_LOWPART_TO_U32(seg[i].ds_addr));
		rx->shadow[idx + i].addr_high =
			htobe32(MXGE_HIGHPART_TO_U32(seg[i].ds_addr));
       }
#endif

done:
       for (i = 0; i < rx->nbufs; i++) {
		if ((idx & 7) == 7) {
			mxge_submit_8rx(&rx->lanai[idx - 7],
					&rx->shadow[idx - 7]);
		}
		idx++;
	}
	return err;
}