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
struct TYPE_2__ {scalar_t__ len; } ;
struct mbuf {scalar_t__ m_len; struct mbuf* m_next; TYPE_1__ m_pkthdr; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
 int EFBIG ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  KASSERT (scalar_t__,char*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ PIO_LEN ; 
 int TX_MAX_SEGS ; 
 scalar_t__ __predict_true (int) ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  busdma_map_mbuf_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ cxgb_debug ; 
 struct mbuf* m_defrag (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
busdma_map_sg_collapse(bus_dma_tag_t tag, bus_dmamap_t map,
	struct mbuf **m, bus_dma_segment_t *segs, int *nsegs)
{
	struct mbuf *n = *m;
	int seg_count, defragged = 0, err = 0;
	bus_dma_segment_t *psegs;
	
	KASSERT(n->m_pkthdr.len, ("packet has zero header len"));
	if (n->m_pkthdr.len <= PIO_LEN)
		return (0);
retry:
	psegs = segs;
	seg_count = 0;
	if (n->m_next == NULL) {
		busdma_map_mbuf_fast(tag, map, n, segs);
		*nsegs = 1;
		return (0);
	}
#if defined(__i386__) || defined(__amd64__)
	while (n && seg_count < TX_MAX_SEGS) {
		/*
		 * firmware doesn't like empty segments
		 */
		if (__predict_true(n->m_len != 0)) {
			seg_count++;
			busdma_map_mbuf_fast(tag, map, n, psegs);
			psegs++;
		}
		n = n->m_next;
	}
#else
	err = bus_dmamap_load_mbuf_sg(tag, map, *m, segs, &seg_count, 0);
#endif	
	if (seg_count == 0) {
		if (cxgb_debug)
			printf("empty segment chain\n");
		err = EFBIG;
		goto err_out;
	}  else if (err == EFBIG || seg_count >= TX_MAX_SEGS) {
		if (cxgb_debug)
			printf("mbuf chain too long: %d max allowed %d\n",
			    seg_count, TX_MAX_SEGS);
		if (!defragged) {
			n = m_defrag(*m, M_NOWAIT);
			if (n == NULL) {
				err = ENOBUFS;
				goto err_out;
			}
			*m = n;
			defragged = 1;
			goto retry;
		}
		err = EFBIG;
		goto err_out;
	}

	*nsegs = seg_count;
err_out:	
	return (err);
}