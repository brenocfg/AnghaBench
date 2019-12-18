#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int m_data; scalar_t__ m_len; struct mbuf* m_next; } ;
typedef  int /*<<< orphan*/  iflib_rxq_t ;
typedef  TYPE_2__* if_rxsd_t ;
typedef  TYPE_3__* if_rxd_info_t ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_12__ {scalar_t__ irf_len; } ;
struct TYPE_11__ {int iri_nfrags; int iri_pad; int iri_len; TYPE_4__* iri_frags; } ;
struct TYPE_10__ {TYPE_1__* ifsd_fl; int /*<<< orphan*/ ** ifsd_cl; } ;
struct TYPE_9__ {int /*<<< orphan*/  ifl_cltype; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_DATA ; 
 int M_EXT ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int M_PKTHDR ; 
 int PFIL_CONSUMED ; 
 int PFIL_DROPPED ; 
 int PFIL_PASS ; 
 int /*<<< orphan*/  m_cljset (struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 
 int /*<<< orphan*/  m_init (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mbuf* rxd_frag_to_sd (int /*<<< orphan*/ ,TYPE_4__*,int,TYPE_2__*,int*,TYPE_3__*) ; 

__attribute__((used)) static struct mbuf *
assemble_segments(iflib_rxq_t rxq, if_rxd_info_t ri, if_rxsd_t sd, int *pf_rv)
{
	struct mbuf *m, *mh, *mt;
	caddr_t cl;
	int  *pf_rv_ptr, flags, i, padlen;
	bool consumed;

	i = 0;
	mh = NULL;
	consumed = false;
	*pf_rv = PFIL_PASS;
	pf_rv_ptr = pf_rv;
	do {
		m = rxd_frag_to_sd(rxq, &ri->iri_frags[i], !consumed, sd,
		    pf_rv_ptr, ri);

		MPASS(*sd->ifsd_cl != NULL);

		/*
		 * Exclude zero-length frags & frags from
		 * packets the filter has consumed or dropped
		 */
		if (ri->iri_frags[i].irf_len == 0 || consumed ||
		    *pf_rv == PFIL_CONSUMED || *pf_rv == PFIL_DROPPED) {
			if (mh == NULL) {
				/* everything saved here */
				consumed = true;
				pf_rv_ptr = NULL;
				continue;
			}
			/* XXX we can save the cluster here, but not the mbuf */
			m_init(m, M_NOWAIT, MT_DATA, 0);
			m_free(m);
			continue;
		}
		if (mh == NULL) {
			flags = M_PKTHDR|M_EXT;
			mh = mt = m;
			padlen = ri->iri_pad;
		} else {
			flags = M_EXT;
			mt->m_next = m;
			mt = m;
			/* assuming padding is only on the first fragment */
			padlen = 0;
		}
		cl = *sd->ifsd_cl;
		*sd->ifsd_cl = NULL;

		/* Can these two be made one ? */
		m_init(m, M_NOWAIT, MT_DATA, flags);
		m_cljset(m, cl, sd->ifsd_fl->ifl_cltype);
		/*
		 * These must follow m_init and m_cljset
		 */
		m->m_data += padlen;
		ri->iri_len -= padlen;
		m->m_len = ri->iri_frags[i].irf_len;
	} while (++i < ri->iri_nfrags);

	return (mh);
}