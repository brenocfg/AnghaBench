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
struct TYPE_4__ {int /*<<< orphan*/  after_idle; } ;
struct TYPE_3__ {int /*<<< orphan*/  after_idle; } ;

/* Variables and functions */
 int HTCP_RTT_REF ; 
 int TCP_RTT_SCALE ; 
 TYPE_2__ htcp_cc_algo ; 
 int htcp_rtt_ref ; 
 int hz ; 
 TYPE_1__ newreno_cc_algo ; 

__attribute__((used)) static int
htcp_mod_init(void)
{

	htcp_cc_algo.after_idle = newreno_cc_algo.after_idle;

	/*
	 * HTCP_RTT_REF is defined in ms, and t_srtt in the tcpcb is stored in
	 * units of TCP_RTT_SCALE*hz. Scale HTCP_RTT_REF to be in the same units
	 * as t_srtt.
	 */
	htcp_rtt_ref = (HTCP_RTT_REF * TCP_RTT_SCALE * hz) / 1000;

	return (0);
}