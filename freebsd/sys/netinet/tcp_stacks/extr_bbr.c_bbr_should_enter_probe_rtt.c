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
struct TYPE_2__ {scalar_t__ rc_probertt_int; scalar_t__ last_in_probertt; int /*<<< orphan*/  rc_rtt_shrinks; } ;
struct tcp_bbr {int rc_past_init_win; scalar_t__ rc_in_persist; TYPE_1__ r_ctl; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ TSTMP_GT (scalar_t__,scalar_t__) ; 
 scalar_t__ bbr_calc_time (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bbr_can_force_probertt ; 

__attribute__((used)) static int32_t inline
bbr_should_enter_probe_rtt(struct tcp_bbr *bbr, uint32_t cts)
{
	if ((bbr->rc_past_init_win == 1) &&
	    (bbr->rc_in_persist == 0) &&
	    (bbr_calc_time(cts, bbr->r_ctl.rc_rtt_shrinks) >= bbr->r_ctl.rc_probertt_int)) {
		return (1);
	}
	if (bbr_can_force_probertt &&
	    (bbr->rc_in_persist == 0) &&
	    (TSTMP_GT(cts, bbr->r_ctl.last_in_probertt)) &&
	    ((cts - bbr->r_ctl.last_in_probertt) > bbr->r_ctl.rc_probertt_int)) {
		return (1);
	}
	return (0);
}