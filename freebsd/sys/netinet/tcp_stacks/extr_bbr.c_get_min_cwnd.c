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
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  rc_pace_max_segs; } ;
struct tcp_bbr {TYPE_2__ r_ctl; scalar_t__ rc_last_options; TYPE_1__* rc_tp; } ;
struct TYPE_3__ {scalar_t__ t_maxseg; } ;

/* Variables and functions */
 scalar_t__ BBR_HIGH_SPEED ; 
 int /*<<< orphan*/  BBR_RTT_PROP ; 
 int bbr_cwnd_min_val ; 
 int bbr_cwnd_min_val_hs ; 
 scalar_t__ bbr_get_rtt (struct tcp_bbr*,int /*<<< orphan*/ ) ; 
 int min (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t
get_min_cwnd(struct tcp_bbr *bbr)
{
	int mss;

	mss = min((bbr->rc_tp->t_maxseg - bbr->rc_last_options), bbr->r_ctl.rc_pace_max_segs);
	if (bbr_get_rtt(bbr, BBR_RTT_PROP) < BBR_HIGH_SPEED)
		return (bbr_cwnd_min_val_hs * mss);
	else
		return (bbr_cwnd_min_val * mss);
}