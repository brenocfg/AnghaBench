#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* p_subn; } ;
typedef  TYPE_3__ osm_sm_t ;
struct TYPE_7__ {TYPE_1__* p_osm; } ;
struct TYPE_6__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  osm_guid_mgr_process (TYPE_3__*) ; 
 int /*<<< orphan*/  wait_for_pending_transactions (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_process_guid_queue(osm_sm_t *sm)
{
	osm_guid_mgr_process(sm);
	wait_for_pending_transactions(&sm->p_subn->p_osm->stats);
}