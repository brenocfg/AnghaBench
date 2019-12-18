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
struct TYPE_2__ {int rc_incr_tmrs; int rc_inc_tcp_oh; int rc_inc_ip_oh; int rc_inc_enet_oh; int /*<<< orphan*/  rc_rttprop; int /*<<< orphan*/  rc_delrate; int /*<<< orphan*/  rc_probertt_int; scalar_t__ bbr_google_discount; } ;
struct tcp_bbr {int rc_no_pacing; int bbr_use_rack_cheat; int /*<<< orphan*/  rc_tv; TYPE_1__ r_ctl; scalar_t__ no_pacing_until; scalar_t__ r_use_policer; scalar_t__ rc_use_google; } ;

/* Variables and functions */
 int USECS_IN_SECOND ; 
 int bbr_filter_len_sec ; 
 scalar_t__ bbr_include_enet_oh ; 
 scalar_t__ bbr_include_ip_oh ; 
 scalar_t__ bbr_include_tcp_oh ; 
 scalar_t__ bbr_incr_timers ; 
 scalar_t__ bbr_no_pacing_until ; 
 int /*<<< orphan*/  bbr_num_pktepo_for_del_limit ; 
 int /*<<< orphan*/  bbr_rtt_probe_limit ; 
 scalar_t__ bbr_use_rack_resend_cheat ; 
 int /*<<< orphan*/  reset_time (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_time_small (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tcp_bbr_tso_size_check (struct tcp_bbr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_get_usecs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bbr_google_mode_off(struct tcp_bbr *bbr)
{
	bbr->rc_use_google = 0;
	bbr->r_ctl.bbr_google_discount = 0;
	bbr->no_pacing_until = bbr_no_pacing_until;
	bbr->r_use_policer = 0;
	if (bbr->no_pacing_until)
		bbr->rc_no_pacing = 1;
	else
		bbr->rc_no_pacing = 0;
	if (bbr_use_rack_resend_cheat)
		bbr->bbr_use_rack_cheat = 1;
	else
		bbr->bbr_use_rack_cheat = 0;
	if (bbr_incr_timers)
		bbr->r_ctl.rc_incr_tmrs = 1;
	else
		bbr->r_ctl.rc_incr_tmrs = 0;
	if (bbr_include_tcp_oh)
		bbr->r_ctl.rc_inc_tcp_oh = 1;
	else
		bbr->r_ctl.rc_inc_tcp_oh = 0;
	if (bbr_include_ip_oh)
		bbr->r_ctl.rc_inc_ip_oh = 1;
	else
		bbr->r_ctl.rc_inc_ip_oh = 0;
	if (bbr_include_enet_oh)
		bbr->r_ctl.rc_inc_enet_oh = 1;
	else
		bbr->r_ctl.rc_inc_enet_oh = 0;
	bbr->r_ctl.rc_probertt_int = bbr_rtt_probe_limit;
	reset_time(&bbr->r_ctl.rc_delrate,
		   bbr_num_pktepo_for_del_limit);
	reset_time_small(&bbr->r_ctl.rc_rttprop,
			 (bbr_filter_len_sec * USECS_IN_SECOND));
	tcp_bbr_tso_size_check(bbr, tcp_get_usecs(&bbr->rc_tv));
}