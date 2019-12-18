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
struct netfront_rxq {struct mbuf** mbufs; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  RING_IDX ;

/* Variables and functions */
 int xn_rxidx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mbuf *
xn_get_rx_mbuf(struct netfront_rxq *rxq, RING_IDX ri)
{
	int i;
	struct mbuf *m;

	i = xn_rxidx(ri);
	m = rxq->mbufs[i];
	rxq->mbufs[i] = NULL;
	return (m);
}