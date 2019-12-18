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
typedef  int uint64_t ;
struct TYPE_2__ {int cur_rtt_send_time; int bbr_ts_check_our_cts; int last_inbound_ts; int bbr_ts_check_tstmp; int bbr_peer_tsratio; } ;
struct tcp_bbr {int rc_ts_clock_set; int rc_ts_cant_be_used; TYPE_1__ r_ctl; } ;

/* Variables and functions */
 scalar_t__ bbr_delta_percent ; 
 int /*<<< orphan*/  bbr_log_tstmp_validation (struct tcp_bbr*,int,int) ; 
 int bbr_min_peer_delta ; 
 int bbr_min_usec_delta ; 

__attribute__((used)) static void
bbr_make_timestamp_determination(struct tcp_bbr *bbr)
{
	/**
	 * We have in our bbr control:
	 * 1) The timestamp we started observing cum-acks (bbr->r_ctl.bbr_ts_check_tstmp).
	 * 2) Our timestamp indicating when we sent that packet (bbr->r_ctl.rsm->bbr_ts_check_our_cts).
	 * 3) The current timestamp that just came in (bbr->r_ctl.last_inbound_ts)
	 * 4) The time that the packet that generated that ack was sent (bbr->r_ctl.cur_rtt_send_time)
	 *
	 * Now we can calculate the time between the sends by doing:
	 *
	 * delta = bbr->r_ctl.cur_rtt_send_time - bbr->r_ctl.bbr_ts_check_our_cts
	 *
	 * And the peer's time between receiving them by doing:
	 *
	 * peer_delta = bbr->r_ctl.last_inbound_ts - bbr->r_ctl.bbr_ts_check_tstmp
	 * 
	 * We want to figure out if the timestamp values are in msec, 10msec or usec.
	 * We also may find that we can't use the timestamps if say we see
	 * that the peer_delta indicates that though we may have taken 10ms to
	 * pace out the data, it only saw 1ms between the two packets. This would
	 * indicate that somewhere on the path is a batching entity that is giving
	 * out time-slices of the actual b/w. This would mean we could not use
	 * reliably the peers timestamps.
	 *
	 * We expect delta > peer_delta initially. Until we figure out the
	 * timestamp difference which we will store in bbr->r_ctl.bbr_peer_tsratio.
	 * If we place 1000 there then its a ms vs our usec. If we place 10000 there
	 * then its 10ms vs our usec. If the peer is running a usec clock we would
	 * put a 1 there. If the value is faster then ours, we will disable the
	 * use of timestamps (though we could revist this later if we find it to be not
	 * just an isolated one or two flows)).
	 * 
	 * To detect the batching middle boxes we will come up with our compensation and
	 * if with it in place, we find the peer is drastically off (by some margin) in
	 * the smaller direction, then we will assume the worst case and disable use of timestamps.
	 * 
	 */
	uint64_t delta, peer_delta, delta_up;

	delta = bbr->r_ctl.cur_rtt_send_time - bbr->r_ctl.bbr_ts_check_our_cts;
	if (delta < bbr_min_usec_delta) {
		/*
		 * Have not seen a min amount of time
		 * between our send times so we can
		 * make a determination of the timestamp
		 * yet.
		 */
		return;
	}
	peer_delta = bbr->r_ctl.last_inbound_ts - bbr->r_ctl.bbr_ts_check_tstmp;
	if (peer_delta < bbr_min_peer_delta) {
		/*
		 * We may have enough in the form of
		 * our delta but the peers number
		 * has not changed that much. It could
		 * be its clock ratio is such that
		 * we need more data (10ms tick) or
		 * there may be other compression scenarios
		 * going on. In any event we need the
		 * spread to be larger.
		 */
		return;
	}
	/* Ok lets first see which way our delta is going */
	if (peer_delta > delta) {
		/* Very unlikely, the peer without
		 * compensation shows that it saw
		 * the two sends arrive further apart
		 * then we saw then in micro-seconds. 
		 */
		if (peer_delta < (delta + ((delta * (uint64_t)1000)/ (uint64_t)bbr_delta_percent))) {
			/* well it looks like the peer is a micro-second clock. */
			bbr->rc_ts_clock_set = 1;
			bbr->r_ctl.bbr_peer_tsratio = 1;
		} else {
			bbr->rc_ts_cant_be_used = 1;
			bbr->rc_ts_clock_set = 1;
		}
		return;
	}
	/* Ok we know that the peer_delta is smaller than our send distance */
	bbr->rc_ts_clock_set = 1;
	/* First question is it within the percentage that they are using usec time? */
	delta_up = (peer_delta * 1000) / (uint64_t)bbr_delta_percent;
	if ((peer_delta + delta_up) >= delta) {
		/* Its a usec clock */
		bbr->r_ctl.bbr_peer_tsratio = 1;
		bbr_log_tstmp_validation(bbr, peer_delta, delta);
		return;
	}
	/* Ok if not usec, what about 10usec (though unlikely)? */
	delta_up = (peer_delta * 1000 * 10) / (uint64_t)bbr_delta_percent;
	if (((peer_delta * 10) + delta_up) >= delta) {
		bbr->r_ctl.bbr_peer_tsratio = 10; 
		bbr_log_tstmp_validation(bbr, peer_delta, delta);
		return;
	}
	/* And what about 100usec (though again unlikely)? */
	delta_up = (peer_delta * 1000 * 100) / (uint64_t)bbr_delta_percent;
	if (((peer_delta * 100) + delta_up) >= delta) {
		bbr->r_ctl.bbr_peer_tsratio = 100;
		bbr_log_tstmp_validation(bbr, peer_delta, delta);
		return;
	}
	/* And how about 1 msec (the most likely one)? */
	delta_up = (peer_delta * 1000 * 1000) / (uint64_t)bbr_delta_percent;
	if (((peer_delta * 1000) + delta_up) >= delta) {
		bbr->r_ctl.bbr_peer_tsratio = 1000;
		bbr_log_tstmp_validation(bbr, peer_delta, delta);
		return;
	}
	/* Ok if not msec could it be 10 msec? */
	delta_up = (peer_delta * 1000 * 10000) / (uint64_t)bbr_delta_percent;
	if (((peer_delta * 10000) + delta_up) >= delta) {
		bbr->r_ctl.bbr_peer_tsratio = 10000;
		return;
	}
	/* If we fall down here the clock tick so slowly we can't use it */
	bbr->rc_ts_cant_be_used = 1;
	bbr->r_ctl.bbr_peer_tsratio = 0;
	bbr_log_tstmp_validation(bbr, peer_delta, delta);
}