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
typedef  int /*<<< orphan*/  uint32_t ;
struct tcp_rack {int dummy; } ;
struct rack_sendmap {int r_rtr_cnt; int /*<<< orphan*/ * r_tim_lastsent; int /*<<< orphan*/  r_start; int /*<<< orphan*/  r_end; scalar_t__ r_rtr_bytes; int /*<<< orphan*/  r_dupack; int /*<<< orphan*/  r_flags; } ;

/* Variables and functions */

__attribute__((used)) static __inline void
rack_clone_rsm(struct tcp_rack *rack, struct rack_sendmap *nrsm,
	       struct rack_sendmap *rsm, uint32_t start)
{
	int idx;

	nrsm->r_start = start;
	nrsm->r_end = rsm->r_end;
	nrsm->r_rtr_cnt = rsm->r_rtr_cnt;
	nrsm->r_flags = rsm->r_flags;
	nrsm->r_dupack = rsm->r_dupack;
	nrsm->r_rtr_bytes = 0;
	rsm->r_end = nrsm->r_start;
	for (idx = 0; idx < nrsm->r_rtr_cnt; idx++) {
		nrsm->r_tim_lastsent[idx] = rsm->r_tim_lastsent[idx];
	}
}