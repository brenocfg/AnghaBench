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
struct TYPE_3__ {int rs_flags; scalar_t__ rs_rtt_lowest; scalar_t__ rs_rtt_highest; int /*<<< orphan*/  rs_rtt_cnt; int /*<<< orphan*/  rs_rtt_tot; } ;
struct TYPE_4__ {TYPE_1__ rack_rs; } ;
struct tcp_rack {TYPE_2__ r_ctl; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int RACK_RTT_EMPTY ; 
 int RACK_RTT_VALID ; 

__attribute__((used)) static void
tcp_rack_xmit_timer(struct tcp_rack *rack, int32_t rtt)
{
	if ((rack->r_ctl.rack_rs.rs_flags & RACK_RTT_EMPTY) ||
	    (rack->r_ctl.rack_rs.rs_rtt_lowest > rtt)) {
		rack->r_ctl.rack_rs.rs_rtt_lowest = rtt;
	}
	if ((rack->r_ctl.rack_rs.rs_flags & RACK_RTT_EMPTY) ||
	    (rack->r_ctl.rack_rs.rs_rtt_highest < rtt)) {
		rack->r_ctl.rack_rs.rs_rtt_highest = rtt;
	}
	rack->r_ctl.rack_rs.rs_flags = RACK_RTT_VALID;
	rack->r_ctl.rack_rs.rs_rtt_tot += rtt;
	rack->r_ctl.rack_rs.rs_rtt_cnt++;
}