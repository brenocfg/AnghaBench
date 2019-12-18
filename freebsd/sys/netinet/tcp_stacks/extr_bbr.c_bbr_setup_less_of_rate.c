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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  rc_delrate; } ;
struct tcp_bbr {int skip_gain; int gain_is_limited; TYPE_1__ r_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  filter_reduce_by (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ get_filter_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bbr_setup_less_of_rate(struct tcp_bbr *bbr, uint32_t cts,
		       uint64_t act_rate, uint64_t rate_wanted)
{
	/*
	 * We could not get a full gains worth
	 * of rate.
	 */
	if (get_filter_value(&bbr->r_ctl.rc_delrate) >= act_rate) {
		/* we can't even get the real rate */
		uint64_t red;

		bbr->skip_gain = 1;
		bbr->gain_is_limited = 0;
		red = get_filter_value(&bbr->r_ctl.rc_delrate) - act_rate;
		if (red)
			filter_reduce_by(&bbr->r_ctl.rc_delrate, red, cts);
	} else {
		/* We can use a lower gain */
		bbr->skip_gain = 0;
		bbr->gain_is_limited = 1;
	}
}