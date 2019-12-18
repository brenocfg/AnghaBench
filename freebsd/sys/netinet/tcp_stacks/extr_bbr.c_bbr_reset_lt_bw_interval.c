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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  rc_lost; int /*<<< orphan*/  rc_lt_lost; int /*<<< orphan*/  rc_delivered; int /*<<< orphan*/  rc_lt_del; int /*<<< orphan*/  rc_del_time; int /*<<< orphan*/  rc_lt_time; int /*<<< orphan*/  rc_pkt_epoch; int /*<<< orphan*/  rc_lt_epoch; } ;
struct tcp_bbr {TYPE_1__ r_ctl; } ;

/* Variables and functions */

__attribute__((used)) static inline void
bbr_reset_lt_bw_interval(struct tcp_bbr *bbr, uint32_t cts)
{
	bbr->r_ctl.rc_lt_epoch = bbr->r_ctl.rc_pkt_epoch;
	bbr->r_ctl.rc_lt_time = bbr->r_ctl.rc_del_time;
	bbr->r_ctl.rc_lt_del = bbr->r_ctl.rc_delivered;
	bbr->r_ctl.rc_lt_lost = bbr->r_ctl.rc_lost;
}