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
struct netfront_rxq {int* grant_ref; struct mbuf** mbufs; int /*<<< orphan*/  gref_head; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int GRANT_REF_INVALID ; 
 int NET_RX_RING_SIZE ; 
 int /*<<< orphan*/  gnttab_end_foreign_access_ref (int) ; 
 int /*<<< orphan*/  gnttab_release_grant_reference (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void
xn_release_rx_bufs(struct netfront_rxq *rxq)
{
	int i,  ref;
	struct mbuf *m;

	for (i = 0; i < NET_RX_RING_SIZE; i++) {
		m = rxq->mbufs[i];

		if (m == NULL)
			continue;

		ref = rxq->grant_ref[i];
		if (ref == GRANT_REF_INVALID)
			continue;

		gnttab_end_foreign_access_ref(ref);
		gnttab_release_grant_reference(&rxq->gref_head, ref);
		rxq->mbufs[i] = NULL;
		rxq->grant_ref[i] = GRANT_REF_INVALID;
		m_freem(m);
	}
}