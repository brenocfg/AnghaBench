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
struct tcpcb {scalar_t__ snd_cwnd; int /*<<< orphan*/  t_inpcb; scalar_t__ t_fb_ptr; } ;
struct TYPE_2__ {scalar_t__ rc_lost_bytes; scalar_t__ rc_sacked; } ;
struct tcp_bbr {int r_wanted_output; TYPE_1__ r_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ ctf_flight_size (struct tcpcb*,scalar_t__) ; 

__attribute__((used)) static void
tcp_bbr_partialack(struct tcpcb *tp)
{
	struct tcp_bbr *bbr;

	bbr = (struct tcp_bbr *)tp->t_fb_ptr;
	INP_WLOCK_ASSERT(tp->t_inpcb);
	if (ctf_flight_size(tp,
		(bbr->r_ctl.rc_sacked  + bbr->r_ctl.rc_lost_bytes)) <=
	    tp->snd_cwnd) {
		bbr->r_wanted_output = 1;
	}
}