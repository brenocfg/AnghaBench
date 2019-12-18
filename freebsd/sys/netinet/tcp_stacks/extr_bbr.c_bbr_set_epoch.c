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
struct TYPE_2__ {scalar_t__ rc_rcv_epoch_start; int /*<<< orphan*/  rc_rtt_epoch; } ;
struct tcp_bbr {TYPE_1__ r_ctl; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  bbr_log_time_epoch (struct tcp_bbr*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void
bbr_set_epoch(struct tcp_bbr *bbr, uint32_t cts, int32_t line)
{
	uint32_t epoch_time;

	/* Tick the RTT clock */
	bbr->r_ctl.rc_rtt_epoch++;
	epoch_time = cts - bbr->r_ctl.rc_rcv_epoch_start;
	bbr_log_time_epoch(bbr, cts, line, epoch_time);
	bbr->r_ctl.rc_rcv_epoch_start = cts;
}