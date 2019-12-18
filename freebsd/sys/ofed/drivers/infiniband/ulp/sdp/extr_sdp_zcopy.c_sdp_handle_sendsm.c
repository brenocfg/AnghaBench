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
typedef  int /*<<< orphan*/  u32 ;
struct socket {int /*<<< orphan*/  sk_sleep; } ;
struct sdp_sock {int /*<<< orphan*/  tx_sa_lock; int /*<<< orphan*/  srcavail_cancel_work; TYPE_1__* tx_sa; struct socket* socket; } ;
struct TYPE_2__ {int /*<<< orphan*/  abort_flags; int /*<<< orphan*/  mseq; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_SA_SENDSM ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdp_dbg_data (struct socket*,char*,...) ; 
 int /*<<< orphan*/  sdp_prf1 (struct socket*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ ) ; 

void sdp_handle_sendsm(struct sdp_sock *ssk, u32 mseq_ack)
{
	struct socket *sk = ssk->socket;
	unsigned long flags;

	spin_lock_irqsave(&ssk->tx_sa_lock, flags);

	if (!ssk->tx_sa) {
		sdp_prf1(sk, NULL, "SendSM for cancelled/finished SrcAvail");
		goto out;
	}

	if (ssk->tx_sa->mseq > mseq_ack) {
		sdp_dbg_data(sk, "SendSM arrived for old SrcAvail. "
			"SendSM mseq_ack: 0x%x, SrcAvail mseq: 0x%x\n",
			mseq_ack, ssk->tx_sa->mseq);
		goto out;
	}

	sdp_dbg_data(sk, "Got SendSM - aborting SrcAvail\n");

	ssk->tx_sa->abort_flags |= TX_SA_SENDSM;
	cancel_delayed_work(&ssk->srcavail_cancel_work);

	wake_up(sk->sk_sleep);
	sdp_dbg_data(sk, "woke up sleepers\n");

out:
	spin_unlock_irqrestore(&ssk->tx_sa_lock, flags);
}