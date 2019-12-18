#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty {int dummy; } ;
struct rp_port {int rp_aiop; int rp_chan; int rp_restart; int /*<<< orphan*/  rp_timer; int /*<<< orphan*/  rp_channel; TYPE_1__* rp_ctlp; struct tty* rp_tty; } ;
struct TYPE_4__ {unsigned char (* ctlmask ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ CONTROLLER_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  POLL_INTERVAL ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rp_handle_port (struct rp_port*) ; 
 int /*<<< orphan*/  rpstart (struct tty*) ; 
 unsigned char sGetAiopIntStatus (TYPE_1__*,int) ; 
 int sGetTxCnt (int /*<<< orphan*/ *) ; 
 unsigned char stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rp_do_poll(void *arg)
{
	CONTROLLER_t	*ctl;
	struct rp_port	*rp;
	struct tty	*tp;
	int	count;
	unsigned char	CtlMask, AiopMask;

	rp = arg;
	tp = rp->rp_tty;
	tty_lock_assert(tp, MA_OWNED);
	ctl = rp->rp_ctlp;
	CtlMask = ctl->ctlmask(ctl);
	if (CtlMask & (1 << rp->rp_aiop)) {
		AiopMask = sGetAiopIntStatus(ctl, rp->rp_aiop);
		if (AiopMask & (1 << rp->rp_chan)) {
			rp_handle_port(rp);
		}
	}

	count = sGetTxCnt(&rp->rp_channel);
	if (count >= 0  && (count <= rp->rp_restart)) {
		rpstart(tp);
	}
	callout_schedule(&rp->rp_timer, POLL_INTERVAL);
}