#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ len; } ;
struct TYPE_3__ {scalar_t__ ext_free; int ext_buf; int /*<<< orphan*/  ext_paddr; } ;
struct mbuf {int m_flags; int m_data; TYPE_2__ m_pkthdr; TYPE_1__ m_ext; } ;
struct ieee80211_rx_ampdu {int rxa_qframes; int rxa_wnd; struct mbuf** rxa_m; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ MCLBYTES ; 
 int /*<<< orphan*/  MEXTADD (struct mbuf*,void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEXTREMOVE (struct mbuf*) ; 
 int M_CLUSTER ; 
 int M_EXT ; 
 int M_EXT_RW ; 
 int /*<<< orphan*/  _MOWNERREF (struct mbuf*,int) ; 
 int /*<<< orphan*/  mclpool_cache ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int,scalar_t__) ; 
 scalar_t__ mwl_ext_free ; 
 void* pool_cache_get_paddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mwl_ampdu_rxdma_reclaim(struct ieee80211_rx_ampdu *rap)
{
#if 0
	int i, n, off;
	struct mbuf *m;
	void *cl;

	n = rap->rxa_qframes;
	for (i = 0; i < rap->rxa_wnd && n > 0; i++) {
		m = rap->rxa_m[i];
		if (m == NULL)
			continue;
		n--;
		/* our dma buffers have a well-known free routine */
		if ((m->m_flags & M_EXT) == 0 ||
		    m->m_ext.ext_free != mwl_ext_free)
			continue;
		/*
		 * Try to allocate a cluster and move the data.
		 */
		off = m->m_data - m->m_ext.ext_buf;
		if (off + m->m_pkthdr.len > MCLBYTES) {
			/* XXX no AMSDU for now */
			continue;
		}
		cl = pool_cache_get_paddr(&mclpool_cache, 0,
		    &m->m_ext.ext_paddr);
		if (cl != NULL) {
			/*
			 * Copy the existing data to the cluster, remove
			 * the rx dma buffer, and attach the cluster in
			 * its place.  Note we preserve the offset to the
			 * data so frames being bridged can still prepend
			 * their headers without adding another mbuf.
			 */
			memcpy((caddr_t) cl + off, m->m_data, m->m_pkthdr.len);
			MEXTREMOVE(m);
			MEXTADD(m, cl, MCLBYTES, 0, NULL, &mclpool_cache);
			/* setup mbuf like _MCLGET does */
			m->m_flags |= M_CLUSTER | M_EXT_RW;
			_MOWNERREF(m, M_EXT | M_CLUSTER);
			/* NB: m_data is clobbered by MEXTADDR, adjust */
			m->m_data += off;
		}
	}
#endif
}