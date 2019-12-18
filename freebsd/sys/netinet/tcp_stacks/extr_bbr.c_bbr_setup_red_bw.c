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
struct TYPE_2__ {int red_bw; int rc_bbr_cur_del_rate; int /*<<< orphan*/  rc_delrate; } ;
struct tcp_bbr {TYPE_1__ r_ctl; } ;

/* Variables and functions */
 int get_filter_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_bbr_tso_size_check (struct tcp_bbr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bbr_setup_red_bw(struct tcp_bbr *bbr, uint32_t cts)
{
	bbr->r_ctl.red_bw = get_filter_value(&bbr->r_ctl.rc_delrate);
	/* Limit the drop in b/w to 1/2 our current filter. */
	if (bbr->r_ctl.red_bw > bbr->r_ctl.rc_bbr_cur_del_rate)
		bbr->r_ctl.red_bw = bbr->r_ctl.rc_bbr_cur_del_rate;
	if (bbr->r_ctl.red_bw < (get_filter_value(&bbr->r_ctl.rc_delrate) / 2))
		bbr->r_ctl.red_bw = get_filter_value(&bbr->r_ctl.rc_delrate) / 2;
	tcp_bbr_tso_size_check(bbr, cts);
}