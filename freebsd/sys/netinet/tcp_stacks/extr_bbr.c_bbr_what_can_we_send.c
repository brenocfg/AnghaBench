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
typedef  scalar_t__ uint32_t ;
struct tcpcb {scalar_t__ snd_wnd; } ;
struct TYPE_2__ {scalar_t__ rc_lost_bytes; scalar_t__ rc_sacked; } ;
struct tcp_bbr {TYPE_1__ r_ctl; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ ctf_flight_size (struct tcpcb*,scalar_t__) ; 
 scalar_t__ ctf_outstanding (struct tcpcb*) ; 

__attribute__((used)) static inline uint32_t
bbr_what_can_we_send(struct tcpcb *tp, struct tcp_bbr *bbr, uint32_t sendwin,
    uint32_t avail, int32_t sb_offset, uint32_t cts)
{
	uint32_t len;

	if (ctf_outstanding(tp) >= tp->snd_wnd) {
		/* We never want to go over our peers rcv-window */
		len = 0;
	} else {
		uint32_t flight;

		flight = ctf_flight_size(tp, (bbr->r_ctl.rc_sacked + bbr->r_ctl.rc_lost_bytes));
		if (flight >= sendwin) {
			/*
			 * We have in flight what we are allowed by cwnd (if
			 * it was rwnd blocking it would have hit above out
			 * >= tp->snd_wnd).
			 */
			return (0);
		}
		len = sendwin - flight;
		if ((len + ctf_outstanding(tp)) > tp->snd_wnd) {
			/* We would send too much (beyond the rwnd) */
			len = tp->snd_wnd - ctf_outstanding(tp);
		}
		if ((len + sb_offset) > avail) {
			/*
			 * We don't have that much in the SB, how much is
			 * there?
			 */
			len = avail - sb_offset;
		}
	}
	return (len);
}