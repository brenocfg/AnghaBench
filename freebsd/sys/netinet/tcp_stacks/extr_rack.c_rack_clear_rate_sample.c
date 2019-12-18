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
struct TYPE_3__ {scalar_t__ rs_rtt_tot; scalar_t__ rs_rtt_cnt; int /*<<< orphan*/  rs_flags; } ;
struct TYPE_4__ {TYPE_1__ rack_rs; } ;
struct tcp_rack {TYPE_2__ r_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  RACK_RTT_EMPTY ; 

__attribute__((used)) static void inline
rack_clear_rate_sample(struct tcp_rack *rack)
{
	rack->r_ctl.rack_rs.rs_flags = RACK_RTT_EMPTY;
	rack->r_ctl.rack_rs.rs_rtt_cnt = 0;
	rack->r_ctl.rack_rs.rs_rtt_tot = 0;
}