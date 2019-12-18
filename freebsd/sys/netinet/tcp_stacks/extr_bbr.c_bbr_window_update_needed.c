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
typedef  int uint32_t ;
struct tcpcb {int rcv_scale; int rcv_adv; int rcv_nxt; } ;
struct TYPE_2__ {int sb_hiwat; } ;
struct socket {TYPE_1__ so_rcv; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ SEQ_GT (int,int) ; 
 int TCP_MAXWIN ; 
 int min (int,int) ; 

__attribute__((used)) static int
bbr_window_update_needed(struct tcpcb *tp, struct socket *so, uint32_t recwin, int32_t maxseg)
{
	/*
	 * "adv" is the amount we could increase the window, taking into
	 * account that we are limited by TCP_MAXWIN << tp->rcv_scale.
	 */
	uint32_t adv;
	int32_t oldwin;

	adv = min(recwin, TCP_MAXWIN << tp->rcv_scale);
	if (SEQ_GT(tp->rcv_adv, tp->rcv_nxt)) {
		oldwin = (tp->rcv_adv - tp->rcv_nxt);
		adv -= oldwin;
	} else
		oldwin = 0;

	/*
	 * If the new window size ends up being the same as the old size
	 * when it is scaled, then don't force a window update.
	 */
	if (oldwin >> tp->rcv_scale == (adv + oldwin) >> tp->rcv_scale)
		return (0);

	if (adv >= (2 * maxseg) &&
	    (adv >= (so->so_rcv.sb_hiwat / 4) ||
	    recwin <= (so->so_rcv.sb_hiwat / 8) ||
	    so->so_rcv.sb_hiwat <= 8 * maxseg)) {
		return (1);
	}
	if (2 * adv >= (int32_t) so->so_rcv.sb_hiwat)
		return (1);
	return (0);
}