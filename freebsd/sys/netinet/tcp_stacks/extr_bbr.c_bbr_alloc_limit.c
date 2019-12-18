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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {scalar_t__ rc_num_split_allocs; } ;
struct tcp_bbr {int alloc_limit_reported; TYPE_1__ r_ctl; } ;
struct bbr_sendmap {scalar_t__ r_limit_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_STAT_INC (int /*<<< orphan*/ ) ; 
 struct bbr_sendmap* bbr_alloc (struct tcp_bbr*) ; 
 int /*<<< orphan*/  bbr_alloc_limited_conns ; 
 int /*<<< orphan*/  bbr_split_limited ; 
 scalar_t__ bbr_tcp_map_split_limit ; 

__attribute__((used)) static struct bbr_sendmap *
bbr_alloc_limit(struct tcp_bbr *bbr, uint8_t limit_type)
{
	struct bbr_sendmap *rsm;

	if (limit_type) {
		/* currently there is only one limit type */
		if (bbr_tcp_map_split_limit > 0 &&
		    bbr->r_ctl.rc_num_split_allocs >= bbr_tcp_map_split_limit) {
			BBR_STAT_INC(bbr_split_limited);
			if (!bbr->alloc_limit_reported) {
				bbr->alloc_limit_reported = 1;
				BBR_STAT_INC(bbr_alloc_limited_conns);
			}
			return (NULL);
		}
	}

	/* allocate and mark in the limit type, if set */
	rsm = bbr_alloc(bbr);
	if (rsm != NULL && limit_type) {
		rsm->r_limit_type = limit_type;
		bbr->r_ctl.rc_num_split_allocs++;
	}
	return (rsm);
}