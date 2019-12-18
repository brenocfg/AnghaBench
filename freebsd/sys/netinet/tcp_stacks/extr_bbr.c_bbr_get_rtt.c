#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int rc_pkt_epoch_rtt; int rc_last_rtt; scalar_t__ rc_ack_hdwr_delay; int /*<<< orphan*/  rc_rttprop; } ;
struct tcp_bbr {TYPE_2__* rc_tp; TYPE_1__ r_ctl; scalar_t__ rc_ack_was_delayed; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {scalar_t__ t_srtt; } ;

/* Variables and functions */
 int BBR_INITIAL_RTO ; 
 scalar_t__ BBR_RTT_PKTRTT ; 
 scalar_t__ BBR_RTT_PROP ; 
 scalar_t__ BBR_RTT_RACK ; 
 scalar_t__ BBR_SRTT ; 
 int TCP_RTT_SHIFT ; 
 int TICKS_2_USEC (scalar_t__) ; 
 int bbr_delayed_ack_time ; 
 int get_filter_value_small (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 

__attribute__((used)) static __inline uint32_t
bbr_get_rtt(struct tcp_bbr *bbr, int32_t rtt_type)
{
	uint32_t f_rtt;
	uint32_t srtt;

	f_rtt = get_filter_value_small(&bbr->r_ctl.rc_rttprop);
	if (get_filter_value_small(&bbr->r_ctl.rc_rttprop) == 0xffffffff) {
		/* We have no rtt at all */
		if (bbr->rc_tp->t_srtt == 0)
			f_rtt = BBR_INITIAL_RTO;
		else
			f_rtt = (TICKS_2_USEC(bbr->rc_tp->t_srtt) >> TCP_RTT_SHIFT);
		/*
		 * Since we don't know how good the rtt is apply a
		 * delayed-ack min
		 */
		if (f_rtt < bbr_delayed_ack_time) {
			f_rtt = bbr_delayed_ack_time;
		}
	}
	/* Take the filter version or last measured pkt-rtt */
	if (rtt_type == BBR_RTT_PROP) {
		srtt = f_rtt;
	} else if (rtt_type == BBR_RTT_PKTRTT) {
		if (bbr->r_ctl.rc_pkt_epoch_rtt) {
			srtt = bbr->r_ctl.rc_pkt_epoch_rtt;
		} else {
			/* No pkt rtt yet */
			srtt = f_rtt;
		}
	} else if (rtt_type == BBR_RTT_RACK) {
		srtt = bbr->r_ctl.rc_last_rtt;
		/* We need to add in any internal delay for our timer */
		if (bbr->rc_ack_was_delayed)
			srtt += bbr->r_ctl.rc_ack_hdwr_delay;
	} else if (rtt_type == BBR_SRTT) {
		srtt = (TICKS_2_USEC(bbr->rc_tp->t_srtt) >> TCP_RTT_SHIFT);
	} else {
		/* TSNH */
		srtt = f_rtt;
#ifdef BBR_INVARIANTS
		panic("Unknown rtt request type %d", rtt_type);
#endif
	}
	return (srtt);
}