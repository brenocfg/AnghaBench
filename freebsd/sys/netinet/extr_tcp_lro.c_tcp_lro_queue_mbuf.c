#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_4__ {scalar_t__ csum_flags; scalar_t__ flowid; scalar_t__ rcv_tstmp; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;
struct lro_ctrl {scalar_t__ lro_mbuf_max; size_t lro_mbuf_count; TYPE_2__* lro_mbuf_data; TYPE_3__* ifp; } ;
struct TYPE_6__ {int if_capenable; int /*<<< orphan*/  (* if_input ) (TYPE_3__*,struct mbuf*) ;} ;
struct TYPE_5__ {int seq; struct mbuf* mb; } ;

/* Variables and functions */
 int IFCAP_LRO ; 
 scalar_t__ M_HASHTYPE_GET (struct mbuf*) ; 
 int M_TSTMP ; 
 int M_TSTMP_LRO ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  nanouptime (struct timespec*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct mbuf*) ; 
 int /*<<< orphan*/  tcp_lro_flush_all (struct lro_ctrl*) ; 

void
tcp_lro_queue_mbuf(struct lro_ctrl *lc, struct mbuf *mb)
{
	struct timespec arrv;

	/* sanity checks */
	if (__predict_false(lc->ifp == NULL || lc->lro_mbuf_data == NULL ||
	    lc->lro_mbuf_max == 0)) {
		/* packet drop */
		m_freem(mb);
		return;
	}

	/* check if packet is not LRO capable */
	if (__predict_false(mb->m_pkthdr.csum_flags == 0 ||
	    (lc->ifp->if_capenable & IFCAP_LRO) == 0)) {

		/* input packet to network layer */
		(*lc->ifp->if_input) (lc->ifp, mb);
		return;
	}
	/* Arrival Stamp the packet */

	if ((mb->m_flags & M_TSTMP) == 0) {
		/* If no hardware or arrival stamp on the packet add arrival */
		nanouptime(&arrv);
		mb->m_pkthdr.rcv_tstmp = ((arrv.tv_sec * 1000000000) +
			                  arrv.tv_nsec);
		mb->m_flags |= M_TSTMP_LRO;
	}
	/* create sequence number */
	lc->lro_mbuf_data[lc->lro_mbuf_count].seq =
	    (((uint64_t)M_HASHTYPE_GET(mb)) << 56) |
	    (((uint64_t)mb->m_pkthdr.flowid) << 24) |
	    ((uint64_t)lc->lro_mbuf_count);

	/* enter mbuf */
	lc->lro_mbuf_data[lc->lro_mbuf_count].mb = mb;

	/* flush if array is full */
	if (__predict_false(++lc->lro_mbuf_count == lc->lro_mbuf_max))
		tcp_lro_flush_all(lc);
}