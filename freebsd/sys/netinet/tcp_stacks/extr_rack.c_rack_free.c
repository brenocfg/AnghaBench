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
struct TYPE_2__ {int /*<<< orphan*/  rc_num_maps_alloced; int /*<<< orphan*/  rc_free; struct rack_sendmap* rc_sacklast; struct rack_sendmap* rc_tlpsend; int /*<<< orphan*/  rc_num_split_allocs; } ;
struct tcp_rack {scalar_t__ rc_free_cnt; TYPE_1__ r_ctl; } ;
struct rack_sendmap {scalar_t__ r_limit_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct rack_sendmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rack_sendmap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_tnext ; 
 scalar_t__ rack_free_cache ; 
 int /*<<< orphan*/  rack_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct rack_sendmap*) ; 

__attribute__((used)) static void
rack_free(struct tcp_rack *rack, struct rack_sendmap *rsm)
{
	if (rsm->r_limit_type) {
		/* currently there is only one limit type */
		rack->r_ctl.rc_num_split_allocs--;
	}
	if (rack->r_ctl.rc_tlpsend == rsm)
		rack->r_ctl.rc_tlpsend = NULL;
	if (rack->r_ctl.rc_sacklast == rsm)
		rack->r_ctl.rc_sacklast = NULL;
	if (rack->rc_free_cnt < rack_free_cache) {
		memset(rsm, 0, sizeof(struct rack_sendmap));
		TAILQ_INSERT_TAIL(&rack->r_ctl.rc_free, rsm, r_tnext);
		rsm->r_limit_type = 0;
		rack->rc_free_cnt++;
		return;
	}
	rack->r_ctl.rc_num_maps_alloced--;
	uma_zfree(rack_zone, rsm);
}