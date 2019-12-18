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
struct sdp_sock {int /*<<< orphan*/  socket; } ;
struct rx_srcavail_state {int used; int reported; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 struct mbuf* sdp_alloc_mb_rdmardcompl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_post_send (struct sdp_sock*,struct mbuf*) ; 

int sdp_post_rdma_rd_compl(struct sdp_sock *ssk,
		struct rx_srcavail_state *rx_sa)
{
	struct mbuf *mb;
	int copied = rx_sa->used - rx_sa->reported;

	if (rx_sa->used <= rx_sa->reported)
		return 0;

	mb = sdp_alloc_mb_rdmardcompl(ssk->socket, copied, 0);

	rx_sa->reported += copied;

	/* TODO: What if no tx_credits available? */
	sdp_post_send(ssk, mb);

	return 0;
}