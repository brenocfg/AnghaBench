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
struct socket {int dummy; } ;
struct sdp_sock {struct rx_srcavail_state* rx_sa; } ;
struct rx_srcavail_state {int /*<<< orphan*/  umem; int /*<<< orphan*/  fmr; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdp_free_fmr (struct socket*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sdp_sock* sdp_sk (struct socket*) ; 

void sdp_abort_rdma_read(struct socket *sk)
{
	struct sdp_sock *ssk = sdp_sk(sk);
	struct rx_srcavail_state *rx_sa = ssk->rx_sa;

	if (!rx_sa)
		return;

	sdp_free_fmr(sk, &rx_sa->fmr, &rx_sa->umem);

	ssk->rx_sa = NULL;
}