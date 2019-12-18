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
struct cubic {int min_rtt_ticks; int mean_rtt_ticks; int sum_rtt_ticks; int /*<<< orphan*/  epoch_ack_count; } ;
struct cc_var {struct cubic* cc_data; } ;

/* Variables and functions */
 int CCV (struct cc_var*,int /*<<< orphan*/ ) ; 
 int CUBIC_MIN_RTT_SAMPLES ; 
 int TCPTV_SRTTBASE ; 
 int TCP_RTT_SCALE ; 
 int max (int,int) ; 
 int /*<<< orphan*/  t_rttupdated ; 
 int /*<<< orphan*/  t_srtt ; 

__attribute__((used)) static void
cubic_record_rtt(struct cc_var *ccv)
{
	struct cubic *cubic_data;
	int t_srtt_ticks;

	/* Ignore srtt until a min number of samples have been taken. */
	if (CCV(ccv, t_rttupdated) >= CUBIC_MIN_RTT_SAMPLES) {
		cubic_data = ccv->cc_data;
		t_srtt_ticks = CCV(ccv, t_srtt) / TCP_RTT_SCALE;

		/*
		 * Record the current SRTT as our minrtt if it's the smallest
		 * we've seen or minrtt is currently equal to its initialised
		 * value.
		 *
		 * XXXLAS: Should there be some hysteresis for minrtt?
		 */
		if ((t_srtt_ticks < cubic_data->min_rtt_ticks ||
		    cubic_data->min_rtt_ticks == TCPTV_SRTTBASE)) {
			cubic_data->min_rtt_ticks = max(1, t_srtt_ticks);

			/*
			 * If the connection is within its first congestion
			 * epoch, ensure we prime mean_rtt_ticks with a
			 * reasonable value until the epoch average RTT is
			 * calculated in cubic_post_recovery().
			 */
			if (cubic_data->min_rtt_ticks >
			    cubic_data->mean_rtt_ticks)
				cubic_data->mean_rtt_ticks =
				    cubic_data->min_rtt_ticks;
		}

		/* Sum samples for epoch average RTT calculation. */
		cubic_data->sum_rtt_ticks += t_srtt_ticks;
		cubic_data->epoch_ack_count++;
	}
}