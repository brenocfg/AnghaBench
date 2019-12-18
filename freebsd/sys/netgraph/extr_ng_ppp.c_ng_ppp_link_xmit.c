#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_10__ {int xmitOctets; int /*<<< orphan*/  xmitFrames; } ;
struct TYPE_8__ {size_t mru; int /*<<< orphan*/  enableACFComp; int /*<<< orphan*/  enableProtoComp; } ;
struct ng_ppp_link {int bytesInQueue; int /*<<< orphan*/  lastWrite; TYPE_3__ stats; int /*<<< orphan*/ * hook; TYPE_1__ conf; } ;
struct TYPE_9__ {size_t len; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
typedef  TYPE_6__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
struct TYPE_12__ {int /*<<< orphan*/  enableRoundRobin; scalar_t__ enableMultilink; } ;
struct TYPE_11__ {int xmitOctets; int /*<<< orphan*/  xmitFrames; } ;
struct TYPE_13__ {int /*<<< orphan*/  xmtx; TYPE_5__ conf; int /*<<< orphan*/  allLinksEqual; TYPE_4__ bundleStats; struct ng_ppp_link* links; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  ENETDOWN ; 
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  ERROUT (int /*<<< orphan*/ ) ; 
 scalar_t__ MP_AVERAGE_LINK_OVERHEAD ; 
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int /*<<< orphan*/  NG_FWD_NEW_DATA (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mbuf*) ; 
 TYPE_6__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 size_t NG_PPP_MAX_LINKS ; 
 size_t PROT_LCP ; 
 int /*<<< orphan*/  getmicrouptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_ppp_acf ; 
 struct mbuf* ng_ppp_addproto (struct mbuf*,size_t,int /*<<< orphan*/ ) ; 
 struct mbuf* ng_ppp_prepend (struct mbuf*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ng_ppp_link_xmit(node_p node, item_p item, uint16_t proto, uint16_t linkNum, int plen)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct ng_ppp_link *link;
	int len, error;
	struct mbuf *m;
	uint16_t mru;

	/* Check if link correct. */
	if (linkNum >= NG_PPP_MAX_LINKS) {
		ERROUT(ENETDOWN);
	}

	/* Get link pointer (optimization). */
	link = &priv->links[linkNum];

	/* Check link status (if real). */
	if (link->hook == NULL) {
		ERROUT(ENETDOWN);
	}

	/* Extract mbuf. */
	NGI_GET_M(item, m);

	/* Check peer's MRU for this link. */
	mru = link->conf.mru;
	if (mru != 0 && m->m_pkthdr.len > mru) {
		NG_FREE_M(m);
		ERROUT(EMSGSIZE);
	}

	/* Prepend protocol number, possibly compressed. */
	if ((m = ng_ppp_addproto(m, proto, link->conf.enableProtoComp)) ==
	    NULL) {
		ERROUT(ENOBUFS);
	}

	/* Prepend address and control field (unless compressed). */
	if (proto == PROT_LCP || !link->conf.enableACFComp) {
		if ((m = ng_ppp_prepend(m, &ng_ppp_acf, 2)) == NULL)
			ERROUT(ENOBUFS);
	}

	/* Deliver frame. */
	len = m->m_pkthdr.len;
	NG_FWD_NEW_DATA(error, item, link->hook, m);

	mtx_lock(&priv->xmtx);

	/* Update link stats. */
	link->stats.xmitFrames++;
	link->stats.xmitOctets += len;

	/* Update bundle stats. */
	if (plen > 0) {
	    priv->bundleStats.xmitFrames++;
	    priv->bundleStats.xmitOctets += plen;
	}

	/* Update 'bytes in queue' counter. */
	if (error == 0) {
		/* bytesInQueue and lastWrite required only for mp_strategy. */
		if (priv->conf.enableMultilink && !priv->allLinksEqual &&
		    !priv->conf.enableRoundRobin) {
			/* If queue was empty, then mark this time. */
			if (link->bytesInQueue == 0)
				getmicrouptime(&link->lastWrite);
			link->bytesInQueue += len + MP_AVERAGE_LINK_OVERHEAD;
			/* Limit max queue length to 50 pkts. BW can be defined
		    	   incorrectly and link may not signal overload. */
			if (link->bytesInQueue > 50 * 1600)
				link->bytesInQueue = 50 * 1600;
		}
	}
	mtx_unlock(&priv->xmtx);
	return (error);

done:
	NG_FREE_ITEM(item);
	return (error);
}