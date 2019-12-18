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
struct TYPE_2__ {scalar_t__ rc_num_maps_alloced; } ;
struct tcp_bbr {int alloc_limit_reported; TYPE_1__ r_ctl; } ;
struct bbr_sendmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_STAT_INC (int /*<<< orphan*/ ) ; 
 struct bbr_sendmap* bbr_alloc (struct tcp_bbr*) ; 
 int /*<<< orphan*/  bbr_alloc_limited ; 
 int /*<<< orphan*/  bbr_alloc_limited_conns ; 
 scalar_t__ bbr_tcp_map_entries_limit ; 

__attribute__((used)) static struct bbr_sendmap *
bbr_alloc_full_limit(struct tcp_bbr *bbr)
{
	if ((bbr_tcp_map_entries_limit > 0) &&
	    (bbr->r_ctl.rc_num_maps_alloced >= bbr_tcp_map_entries_limit)) {
		BBR_STAT_INC(bbr_alloc_limited);
		if (!bbr->alloc_limit_reported) {
			bbr->alloc_limit_reported = 1;
			BBR_STAT_INC(bbr_alloc_limited_conns);
		}
		return (NULL);
	}
	return (bbr_alloc(bbr));
}