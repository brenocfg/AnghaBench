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
struct htcp {scalar_t__ minrtt; scalar_t__ maxrtt; } ;
struct cc_var {struct htcp* cc_data; } ;

/* Variables and functions */
 scalar_t__ CCV (struct cc_var*,int /*<<< orphan*/ ) ; 
 scalar_t__ HTCP_MIN_RTT_SAMPLES ; 
 scalar_t__ TCPTV_SRTTBASE ; 
 int /*<<< orphan*/  t_rttupdated ; 
 int /*<<< orphan*/  t_srtt ; 

__attribute__((used)) static void
htcp_record_rtt(struct cc_var *ccv)
{
	struct htcp *htcp_data;

	htcp_data = ccv->cc_data;

	/* XXXLAS: Should there be some hysteresis for minrtt? */

	/*
	 * Record the current SRTT as our minrtt if it's the smallest we've seen
	 * or minrtt is currently equal to its initialised value. Ignore SRTT
	 * until a min number of samples have been taken.
	 */
	if ((CCV(ccv, t_srtt) < htcp_data->minrtt ||
	    htcp_data->minrtt == TCPTV_SRTTBASE) &&
	    (CCV(ccv, t_rttupdated) >= HTCP_MIN_RTT_SAMPLES))
		htcp_data->minrtt = CCV(ccv, t_srtt);

	/*
	 * Record the current SRTT as our maxrtt if it's the largest we've
	 * seen. Ignore SRTT until a min number of samples have been taken.
	 */
	if (CCV(ccv, t_srtt) > htcp_data->maxrtt
	    && CCV(ccv, t_rttupdated) >= HTCP_MIN_RTT_SAMPLES)
		htcp_data->maxrtt = CCV(ccv, t_srtt);
}