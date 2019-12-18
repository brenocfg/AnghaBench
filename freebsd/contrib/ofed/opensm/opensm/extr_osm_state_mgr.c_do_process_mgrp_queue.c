#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* p_subn; } ;
typedef  TYPE_4__ osm_sm_t ;
struct TYPE_7__ {int /*<<< orphan*/  disable_multicast; } ;
struct TYPE_9__ {scalar_t__ sm_state; TYPE_2__* p_osm; TYPE_1__ opt; } ;
struct TYPE_8__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IB_SMINFO_STATE_MASTER ; 
 int /*<<< orphan*/  osm_mcast_mgr_process (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_pending_transactions (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_process_mgrp_queue(osm_sm_t * sm)
{
	if (sm->p_subn->sm_state != IB_SMINFO_STATE_MASTER)
		return;
	if (!sm->p_subn->opt.disable_multicast) {
		osm_mcast_mgr_process(sm, FALSE);
		wait_for_pending_transactions(&sm->p_subn->p_osm->stats);
	}
}