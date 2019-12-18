#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  ext_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
struct mbuf {TYPE_2__ m_ext; TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_len; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
struct TYPE_7__ {int ds_addr; } ;
typedef  TYPE_3__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int TSEC_RXBUFFER_ALIGNMENT ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,TYPE_3__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_getjcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
tsec_new_rxbuf(bus_dma_tag_t tag, bus_dmamap_t map, struct mbuf **mbufp,
    uint32_t *paddr)
{
	struct mbuf *new_mbuf;
	bus_dma_segment_t seg[1];
	int error, nsegs;

	KASSERT(mbufp != NULL, ("NULL mbuf pointer!"));

	new_mbuf = m_getjcl(M_NOWAIT, MT_DATA, M_PKTHDR, MCLBYTES);
	if (new_mbuf == NULL)
		return (ENOBUFS);
	new_mbuf->m_len = new_mbuf->m_pkthdr.len = new_mbuf->m_ext.ext_size;

	if (*mbufp) {
		bus_dmamap_sync(tag, map, BUS_DMASYNC_POSTREAD);
		bus_dmamap_unload(tag, map);
	}

	error = bus_dmamap_load_mbuf_sg(tag, map, new_mbuf, seg, &nsegs,
	    BUS_DMA_NOWAIT);
	KASSERT(nsegs == 1, ("Too many segments returned!"));
	if (nsegs != 1 || error)
		panic("tsec_new_rxbuf(): nsegs(%d), error(%d)", nsegs, error);

#if 0
	if (error) {
		printf("tsec: bus_dmamap_load_mbuf_sg() returned: %d!\n",
			error);
		m_freem(new_mbuf);
		return (ENOBUFS);
	}
#endif

#if 0
	KASSERT(((seg->ds_addr) & (TSEC_RXBUFFER_ALIGNMENT-1)) == 0,
		("Wrong alignment of RX buffer!"));
#endif
	bus_dmamap_sync(tag, map, BUS_DMASYNC_PREREAD);

	(*mbufp) = new_mbuf;
	(*paddr) = seg->ds_addr;
	return (0);
}