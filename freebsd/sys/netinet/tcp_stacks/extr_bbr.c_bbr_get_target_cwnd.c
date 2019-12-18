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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int rc_pace_max_segs; } ;
struct tcp_bbr {scalar_t__ rc_bbr_state; scalar_t__ rc_use_google; TYPE_2__ r_ctl; scalar_t__ rc_last_options; TYPE_1__* rc_tp; } ;
struct TYPE_3__ {scalar_t__ t_maxseg; } ;

/* Variables and functions */
 scalar_t__ BBR_STATE_PROBE_BW ; 
 scalar_t__ BBR_SUB_GAIN ; 
 int /*<<< orphan*/  bbr_get_raw_target_cwnd (struct tcp_bbr*,int /*<<< orphan*/ ,int) ; 
 int bbr_quanta ; 
 scalar_t__ bbr_state_val (struct tcp_bbr*) ; 
 int get_min_cwnd (struct tcp_bbr*) ; 
 int min (scalar_t__,int) ; 
 int roundup (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t
bbr_get_target_cwnd(struct tcp_bbr *bbr, uint64_t bw, uint32_t gain)
{
	uint32_t cwnd, mss;

	mss = min((bbr->rc_tp->t_maxseg - bbr->rc_last_options), bbr->r_ctl.rc_pace_max_segs);
	/* Get the base cwnd with gain rounded to a mss */
	cwnd = roundup(bbr_get_raw_target_cwnd(bbr, bw, gain), mss);
	/* 
	 * Add in N (2 default since we do not have a
	 * fq layer to trap packets in) quanta's per the I-D 
	 * section 4.2.3.2 quanta adjust. 
	 */
	cwnd += (bbr_quanta * bbr->r_ctl.rc_pace_max_segs);
	if (bbr->rc_use_google) {
		if((bbr->rc_bbr_state == BBR_STATE_PROBE_BW) &&
		   (bbr_state_val(bbr) == BBR_SUB_GAIN)) {
			/* 
			 * The linux implementation adds
			 * an extra 2 x mss in gain cycle which
			 * is documented no-where except in the code.
			 * so we add more for Neal undocumented feature 
			 */
			cwnd += 2 * mss;
		}
 		if ((cwnd / mss) & 0x1) {
			/* Round up for odd num mss */
			cwnd += mss;
		}
	}
	/* Are we below the min cwnd? */
	if (cwnd < get_min_cwnd(bbr))
		return (get_min_cwnd(bbr));
	return (cwnd);
}