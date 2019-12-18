#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_8__ {int rc_pace_min_segs; int rc_pace_max_segs; int rc_bbr_hptsi_gain; int bbr_cross_over; int bbr_hptsi_segments_max; int bbr_hptsi_per_second; int bbr_hptsi_segments_floor; int bbr_utter_max; int /*<<< orphan*/  bbr_hptsi_segments_delay_tar; } ;
struct tcp_bbr {scalar_t__ rc_last_options; scalar_t__ rc_past_init_win; scalar_t__ rc_use_google; TYPE_3__ r_ctl; TYPE_2__* rc_inp; scalar_t__ rc_no_pacing; TYPE_5__* rc_tp; scalar_t__ bbr_init_win_cheat; } ;
struct TYPE_10__ {scalar_t__ t_maxseg; int /*<<< orphan*/  t_flags; int /*<<< orphan*/  snd_wnd; } ;
struct TYPE_6__ {int sb_flags; } ;
struct TYPE_9__ {TYPE_1__ so_snd; } ;
struct TYPE_7__ {TYPE_4__* inp_socket; } ;

/* Variables and functions */
 int BBR_MIN_SEG ; 
 int BBR_UNIT ; 
 int FIVETWELVE_MBPS ; 
 scalar_t__ IN_RECOVERY (int /*<<< orphan*/ ) ; 
 int ONE_POINT_TWO_MEG ; 
 int PACE_MAX_IP_BYTES ; 
 int SB_TLS_IFNET ; 
 int /*<<< orphan*/  bbr_adjust_for_hw_pacing (struct tcp_bbr*,int) ; 
 scalar_t__ bbr_all_get_min ; 
 int bbr_get_bw (struct tcp_bbr*) ; 
 int bbr_get_pacing_length (struct tcp_bbr*,int,int /*<<< orphan*/ ,int) ; 
 int bbr_initial_cwnd (struct tcp_bbr*,TYPE_5__*) ; 
 int /*<<< orphan*/  bbr_log_type_tsosize (struct tcp_bbr*,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int bbr_minseg (struct tcp_bbr*) ; 
 int ctf_get_opt_tls_size (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int rounddown (int,int) ; 
 int roundup (int,int) ; 

__attribute__((used)) static void
tcp_bbr_tso_size_check(struct tcp_bbr *bbr, uint32_t cts)
{
	uint64_t bw;
	uint32_t old_tso = 0, new_tso;
	uint32_t maxseg, bytes;
	uint32_t tls_seg=0;
	/* 
	 * Google/linux uses the following algorithm to determine
	 * the TSO size based on the b/w of the link (from Neal Cardwell email 9/27/18):
	 *
	 *  bytes = bw_in_bytes_per_second / 1000
	 *  bytes = min(bytes, 64k)
	 *  tso_segs = bytes / MSS
	 *  if (bw < 1.2Mbs)
	 *      min_tso_segs = 1
	 *  else
	 *	min_tso_segs = 2
	 * tso_segs = max(tso_segs, min_tso_segs)
	 *
	 * * Note apply a device specific limit (we apply this in the 
	 *   tcp_m_copym).
	 * Note that before the initial measurement is made google bursts out
	 * a full iwnd just like new-reno/cubic.
	 *
	 * We do not use this algorithm. Instead we
	 * use a two phased approach:
	 *
	 *  if ( bw <= per-tcb-cross-over)
	 *     goal_tso =  calculate how much with this bw we
	 *                 can send in goal-time seconds.
	 *     if (goal_tso > mss)
	 *         seg = goal_tso / mss
	 *         tso = seg * mss
	 *     else
         *         tso = mss
	 *     if (tso > per-tcb-max)
	 *         tso = per-tcb-max
	 *  else if ( bw > 512Mbps)
	 *     tso = max-tso (64k/mss)
	 *  else
	 *     goal_tso = bw / per-tcb-divsor
	 *     seg = (goal_tso + mss-1)/mss
	 *     tso = seg * mss
	 *
	 * if (tso < per-tcb-floor)
	 *    tso = per-tcb-floor
	 * if (tso > per-tcb-utter_max)
	 *    tso = per-tcb-utter_max
	 *
	 * Note the default per-tcb-divisor is 1000 (same as google).
	 * the goal cross over is 30Mbps however. To recreate googles
	 * algorithm you need to set:
	 * 
	 * cross-over = 23,168,000 bps
	 * goal-time = 18000
	 * per-tcb-max = 2
	 * per-tcb-divisor = 1000
	 * per-tcb-floor = 1
	 *
	 * This will get you "google bbr" behavior with respect to tso size.
	 *
	 * Note we do set anything TSO size until we are past the initial
	 * window. Before that we gnerally use either a single MSS
	 * or we use the full IW size (so we burst a IW at a time)
	 * Also note that Hardware-TLS is special and does alternate
	 * things to minimize PCI Bus Bandwidth use.
	 */

	if (bbr->rc_tp->t_maxseg > bbr->rc_last_options) {
		maxseg = bbr->rc_tp->t_maxseg - bbr->rc_last_options;
	} else {
		maxseg = BBR_MIN_SEG - bbr->rc_last_options;
	}
#ifdef KERN_TLS
	if (bbr->rc_inp->inp_socket->so_snd.sb_flags & SB_TLS_IFNET) {
		tls_seg =  ctf_get_opt_tls_size(bbr->rc_inp->inp_socket, bbr->rc_tp->snd_wnd);
		bbr->r_ctl.rc_pace_min_segs = (tls_seg + bbr->rc_last_options);
	}
#endif
	old_tso = bbr->r_ctl.rc_pace_max_segs;
	if (bbr->rc_past_init_win == 0) {
		/*
		 * Not enough data has been acknowledged to make a
		 * judgement unless we are hardware TLS. Set up
		 * the inital TSO based on if we are sending a
		 * full IW at once or not.
		 */
		if (bbr->rc_use_google)
			bbr->r_ctl.rc_pace_max_segs = ((bbr->rc_tp->t_maxseg - bbr->rc_last_options) * 2);
		else if (bbr->bbr_init_win_cheat)
			bbr->r_ctl.rc_pace_max_segs = bbr_initial_cwnd(bbr, bbr->rc_tp);
		else
			bbr->r_ctl.rc_pace_max_segs = bbr->rc_tp->t_maxseg - bbr->rc_last_options;
		if (bbr->r_ctl.rc_pace_min_segs != bbr->rc_tp->t_maxseg)
			bbr->r_ctl.rc_pace_min_segs = bbr->rc_tp->t_maxseg;
#ifdef KERN_TLS
		if ((bbr->rc_inp->inp_socket->so_snd.sb_flags & SB_TLS_IFNET) && tls_seg) {
			/*
			 * For hardware TLS we set our min to the tls_seg size.
			 */
			bbr->r_ctl.rc_pace_max_segs = tls_seg;
			bbr->r_ctl.rc_pace_min_segs = tls_seg + bbr->rc_last_options;
		}
#endif
		if (bbr->r_ctl.rc_pace_max_segs == 0) {
			bbr->r_ctl.rc_pace_max_segs = maxseg;
		}
		bbr_log_type_tsosize(bbr, cts, bbr->r_ctl.rc_pace_max_segs, tls_seg, old_tso, maxseg, 0);
#ifdef KERN_TLS
		if ((bbr->rc_inp->inp_socket->so_snd.sb_flags & SB_TLS_IFNET) == 0)
#endif
			bbr_adjust_for_hw_pacing(bbr, cts);
		return;
	}
	/**
	 * Now lets set the TSO goal based on our delivery rate in
	 * bytes per second. Note we only do this if
	 * we have acked at least the initial cwnd worth of data.
	 */
	bw = bbr_get_bw(bbr);
	if (IN_RECOVERY(bbr->rc_tp->t_flags) &&
	     (bbr->rc_use_google == 0)) {
		/* We clamp to one MSS in recovery */
		new_tso = maxseg;
	} else if (bbr->rc_use_google) {
		int min_tso_segs;
		
		/* Google considers the gain too */
		if (bbr->r_ctl.rc_bbr_hptsi_gain != BBR_UNIT) {
			bw *= bbr->r_ctl.rc_bbr_hptsi_gain;
			bw /= BBR_UNIT;
		}
		bytes = bw / 1024;
		if (bytes > (64 * 1024))
			bytes = 64 * 1024;
		new_tso = bytes / maxseg;
		if (bw < ONE_POINT_TWO_MEG)
			min_tso_segs = 1;
		else
			min_tso_segs = 2;
		if (new_tso < min_tso_segs)
			new_tso = min_tso_segs;
		new_tso *= maxseg;
	} else if (bbr->rc_no_pacing) {
		new_tso = (PACE_MAX_IP_BYTES / maxseg) * maxseg;
	} else if (bw <= bbr->r_ctl.bbr_cross_over) {
		/*
		 * Calculate the worse case b/w TSO if we are inserting no
		 * more than a delay_target number of TSO's.
		 */
		uint32_t tso_len, min_tso;

		tso_len = bbr_get_pacing_length(bbr, BBR_UNIT, bbr->r_ctl.bbr_hptsi_segments_delay_tar, bw);
		if (tso_len > maxseg) {
			new_tso = tso_len / maxseg;
			if (new_tso > bbr->r_ctl.bbr_hptsi_segments_max)
				new_tso = bbr->r_ctl.bbr_hptsi_segments_max;
			new_tso *= maxseg;
		} else {
			/*
			 * less than a full sized frame yikes.. long rtt or
			 * low bw?
			 */
			min_tso = bbr_minseg(bbr);
			if ((tso_len > min_tso) && (bbr_all_get_min == 0))
				new_tso = rounddown(tso_len, min_tso);
			else
				new_tso = min_tso;
		}
	} else if (bw > FIVETWELVE_MBPS) {
		/*
		 * This guy is so fast b/w wise that we can TSO as large as
		 * possible of segments that the NIC will allow.
		 */
		new_tso = rounddown(PACE_MAX_IP_BYTES, maxseg);
	} else {
		/*
		 * This formula is based on attempting to send a segment or
		 * more every bbr_hptsi_per_second. The default is 1000
		 * which means you are targeting what you can send every 1ms
		 * based on the peers bw.
		 *
		 * If the number drops to say 500, then you are looking more
		 * at 2ms and you will raise how much we send in a single
		 * TSO thus saving CPU (less bbr_output_wtime() calls). The
		 * trade off of course is you will send more at once and
		 * thus tend to clump up the sends into larger "bursts"
		 * building a queue.
		 */
		bw /= bbr->r_ctl.bbr_hptsi_per_second;
		new_tso = roundup(bw, (uint64_t)maxseg);
		/*
		 * Gate the floor to match what our lower than 48Mbps
		 * algorithm does. The ceiling (bbr_hptsi_segments_max) thus
		 * becomes the floor for this calculation.
		 */
		if (new_tso < (bbr->r_ctl.bbr_hptsi_segments_max * maxseg))
			new_tso = (bbr->r_ctl.bbr_hptsi_segments_max * maxseg);
	}
	if (bbr->r_ctl.bbr_hptsi_segments_floor && (new_tso < (maxseg * bbr->r_ctl.bbr_hptsi_segments_floor)))
		new_tso = maxseg * bbr->r_ctl.bbr_hptsi_segments_floor;
	if (new_tso > PACE_MAX_IP_BYTES)
		new_tso = rounddown(PACE_MAX_IP_BYTES, maxseg);
	/* Enforce an utter maximum if we are not HW-TLS */
#ifdef KERN_TLS
	if ((bbr->rc_inp->inp_socket->so_snd.sb_flags & SB_TLS_IFNET) == 0)
#endif
		if (bbr->r_ctl.bbr_utter_max && (new_tso > (bbr->r_ctl.bbr_utter_max * maxseg))) {
			new_tso = bbr->r_ctl.bbr_utter_max * maxseg;
		}
#ifdef KERN_TLS
	if (tls_seg) {
		/* 
		 * Lets move the output size
		 * up to 1 or more TLS record sizes.
		 */
		uint32_t temp;

		temp = roundup(new_tso, tls_seg);
		new_tso = temp;
		/* Back down if needed to under a full frame */
		while (new_tso > PACE_MAX_IP_BYTES)
			new_tso -= tls_seg;
	}
#endif
	if (old_tso != new_tso) {
		/* Only log changes */
		bbr_log_type_tsosize(bbr, cts, new_tso, tls_seg, old_tso, maxseg, 0);
		bbr->r_ctl.rc_pace_max_segs = new_tso;
	}
#ifdef KERN_TLS
	if ((bbr->rc_inp->inp_socket->so_snd.sb_flags & SB_TLS_IFNET) &&
	     tls_seg) {
		bbr->r_ctl.rc_pace_min_segs = tls_seg + bbr->rc_last_options;
	} else
#endif
		/* We have hardware pacing and not hardware TLS! */
		bbr_adjust_for_hw_pacing(bbr, cts);
}