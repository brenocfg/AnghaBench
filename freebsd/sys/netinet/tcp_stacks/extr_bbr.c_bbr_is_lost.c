#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct tcp_bbr {int dummy; } ;
struct bbr_sendmap {scalar_t__* r_tim_lastsent; int r_rtr_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_RTT_RACK ; 
 scalar_t__ bbr_calc_thresh_rack (struct tcp_bbr*,int /*<<< orphan*/ ,scalar_t__,struct bbr_sendmap*) ; 
 int /*<<< orphan*/  bbr_get_rtt (struct tcp_bbr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bbr_is_lost(struct tcp_bbr *bbr, struct bbr_sendmap *rsm, uint32_t cts)
{
	uint32_t thresh;

	
	thresh = bbr_calc_thresh_rack(bbr, bbr_get_rtt(bbr, BBR_RTT_RACK),
				      cts, rsm);
	if ((cts - rsm->r_tim_lastsent[(rsm->r_rtr_cnt - 1)]) >= thresh) {
		/* It is lost (past time) */
		return (1);
	}
	return (0);
}