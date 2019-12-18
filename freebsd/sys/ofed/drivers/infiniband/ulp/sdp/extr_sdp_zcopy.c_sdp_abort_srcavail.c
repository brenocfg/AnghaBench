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
struct tx_srcavail_state {int /*<<< orphan*/  umem; int /*<<< orphan*/  fmr; } ;
struct socket {int dummy; } ;
struct sdp_sock {int /*<<< orphan*/  tx_sa_lock; struct tx_srcavail_state* tx_sa; int /*<<< orphan*/  srcavail_cancel_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  sdp_free_fmr (struct socket*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sdp_sock* sdp_sk (struct socket*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void sdp_abort_srcavail(struct socket *sk)
{
	struct sdp_sock *ssk = sdp_sk(sk);
	struct tx_srcavail_state *tx_sa = ssk->tx_sa;
	unsigned long flags;

	if (!tx_sa)
		return;

	cancel_delayed_work(&ssk->srcavail_cancel_work);
	flush_scheduled_work();

	spin_lock_irqsave(&ssk->tx_sa_lock, flags);

	sdp_free_fmr(sk, &tx_sa->fmr, &tx_sa->umem);

	ssk->tx_sa = NULL;

	spin_unlock_irqrestore(&ssk->tx_sa_lock, flags);
}