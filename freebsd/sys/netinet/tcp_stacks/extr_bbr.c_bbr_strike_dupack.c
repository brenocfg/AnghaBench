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
struct TYPE_2__ {int /*<<< orphan*/  rc_tmap; } ;
struct tcp_bbr {int r_wanted_output; TYPE_1__ r_ctl; } ;
struct bbr_sendmap {int r_dupack; } ;

/* Variables and functions */
 int DUP_ACK_THRESHOLD ; 
 struct bbr_sendmap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bbr_strike_dupack(struct tcp_bbr *bbr)
{
	struct bbr_sendmap *rsm;

	rsm = TAILQ_FIRST(&bbr->r_ctl.rc_tmap);
	if (rsm && (rsm->r_dupack < 0xff)) {
		rsm->r_dupack++;
		if (rsm->r_dupack >= DUP_ACK_THRESHOLD)
			bbr->r_wanted_output = 1;
	}
}