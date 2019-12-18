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
struct htcp {int t_last_cong; int beta; int alpha; } ;
struct cc_var {struct htcp* cc_data; } ;

/* Variables and functions */
 int CCV (struct cc_var*,int /*<<< orphan*/ ) ; 
 int HTCP_CALC_ALPHA (int) ; 
 int HTCP_DELTA_L ; 
 int /*<<< orphan*/  HTCP_MAXROWE ; 
 int HTCP_MINROWE ; 
 int HTCP_SHIFT ; 
 scalar_t__ V_htcp_adaptive_backoff ; 
 scalar_t__ V_htcp_rtt_scaling ; 
 int htcp_max_diff ; 
 int htcp_rtt_ref ; 
 int max (int,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t_srtt ; 
 int ticks ; 

__attribute__((used)) static void
htcp_recalc_alpha(struct cc_var *ccv)
{
	struct htcp *htcp_data;
	int alpha, diff, now;

	htcp_data = ccv->cc_data;
	now = ticks;

	/*
	 * If ticks has wrapped around (will happen approximately once every 49
	 * days on a machine with the default kern.hz=1000) and a flow straddles
	 * the wrap point, our alpha calcs will be completely wrong. We cut our
	 * losses and restart alpha from scratch by setting t_last_cong = now -
	 * HTCP_DELTA_L.
	 *
	 * This does not deflate our cwnd at all. It simply slows the rate cwnd
	 * is growing by until alpha regains the value it held prior to taking
	 * this drastic measure.
	 */
	if (now < htcp_data->t_last_cong)
		htcp_data->t_last_cong = now - HTCP_DELTA_L;

	diff = now - htcp_data->t_last_cong - HTCP_DELTA_L;

	/* Cap alpha if the value of diff would overflow HTCP_CALC_ALPHA(). */
	if (diff < htcp_max_diff) {
		/*
		 * If it has been more than HTCP_DELTA_L ticks since congestion,
		 * increase alpha according to the function defined in the spec.
		 */
		if (diff > 0) {
			alpha = HTCP_CALC_ALPHA(diff);

			/*
			 * Adaptive backoff fairness adjustment:
			 * 2 * (1 - beta) * alpha_raw
			 */
			if (V_htcp_adaptive_backoff)
				alpha = max(1, (2 * ((1 << HTCP_SHIFT) -
				    htcp_data->beta) * alpha) >> HTCP_SHIFT);

			/*
			 * RTT scaling: (RTT / RTT_ref) * alpha
			 * alpha will be the raw value from HTCP_CALC_ALPHA() if
			 * adaptive backoff is off, or the adjusted value if
			 * adaptive backoff is on.
			 */
			if (V_htcp_rtt_scaling)
				alpha = max(1, (min(max(HTCP_MINROWE,
				    (CCV(ccv, t_srtt) << HTCP_SHIFT) /
				    htcp_rtt_ref), HTCP_MAXROWE) * alpha)
				    >> HTCP_SHIFT);

		} else
			alpha = 1;

		htcp_data->alpha = alpha;
	}
}