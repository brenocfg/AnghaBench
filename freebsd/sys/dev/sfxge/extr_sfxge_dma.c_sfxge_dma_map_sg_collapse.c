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
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct mbuf {scalar_t__ m_len; struct mbuf* m_next; TYPE_1__ m_pkthdr; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
 int EFBIG ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 struct mbuf* m_defrag (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_map_mbuf_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ *) ; 

int
sfxge_dma_map_sg_collapse(bus_dma_tag_t tag, bus_dmamap_t map,
			  struct mbuf **mp, bus_dma_segment_t *segs,
			  int *nsegs, int maxsegs)
{
	bus_dma_segment_t *psegs;
	struct mbuf *m;
	int seg_count;
	int defragged;
	int err;

	m = *mp;
	defragged = err = seg_count = 0;

	KASSERT(m->m_pkthdr.len, ("packet has zero header length"));

retry:
	psegs = segs;
	seg_count = 0;
	if (m->m_next == NULL) {
		sfxge_map_mbuf_fast(tag, map, m, segs);
		*nsegs = 1;
		return (0);
	}
#if defined(__i386__) || defined(__amd64__)
	while (m != NULL && seg_count < maxsegs) {
		/*
		 * firmware doesn't like empty segments
		 */
		if (m->m_len != 0) {
			seg_count++;
			sfxge_map_mbuf_fast(tag, map, m, psegs);
			psegs++;
		}
		m = m->m_next;
	}
#else
	err = bus_dmamap_load_mbuf_sg(tag, map, *mp, segs, &seg_count, 0);
#endif
	if (seg_count == 0) {
		err = EFBIG;
		goto err_out;
	} else if (err == EFBIG || seg_count >= maxsegs) {
		if (!defragged) {
			m = m_defrag(*mp, M_NOWAIT);
			if (m == NULL) {
				err = ENOBUFS;
				goto err_out;
			}
			*mp = m;
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