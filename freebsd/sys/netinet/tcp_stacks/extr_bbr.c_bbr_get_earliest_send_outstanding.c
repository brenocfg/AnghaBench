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
struct TYPE_2__ {int /*<<< orphan*/  rc_tmap; } ;
struct tcp_bbr {TYPE_1__ r_ctl; } ;
struct bbr_sendmap {int r_rtr_cnt; int /*<<< orphan*/ * r_tim_lastsent; } ;

/* Variables and functions */
 struct bbr_sendmap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t
bbr_get_earliest_send_outstanding(struct tcp_bbr *bbr, struct bbr_sendmap *u_rsm, uint32_t cts)
{
	struct bbr_sendmap *rsm;
	
	rsm = TAILQ_FIRST(&bbr->r_ctl.rc_tmap);
	if ((rsm == NULL) || (u_rsm == rsm))
		return (cts);
	return(rsm->r_tim_lastsent[(rsm->r_rtr_cnt-1)]);
}