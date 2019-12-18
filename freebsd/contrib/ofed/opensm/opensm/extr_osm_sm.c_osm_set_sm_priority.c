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
typedef  scalar_t__ uint8_t ;
struct TYPE_8__ {TYPE_2__* p_subn; } ;
typedef  TYPE_3__ osm_sm_t ;
struct TYPE_6__ {scalar_t__ sm_priority; } ;
struct TYPE_7__ {scalar_t__ sm_state; TYPE_1__ opt; } ;

/* Variables and functions */
 scalar_t__ IB_SMINFO_STATE_STANDBY ; 
 int /*<<< orphan*/  TRAP_144_MASK_SM_PRIORITY_CHANGE ; 
 int /*<<< orphan*/  osm_send_trap144 (TYPE_3__*,int /*<<< orphan*/ ) ; 

void osm_set_sm_priority(osm_sm_t * sm, uint8_t priority)
{
	uint8_t old_pri = sm->p_subn->opt.sm_priority;

	sm->p_subn->opt.sm_priority = priority;

	if (old_pri < priority &&
	    sm->p_subn->sm_state == IB_SMINFO_STATE_STANDBY)
		osm_send_trap144(sm, TRAP_144_MASK_SM_PRIORITY_CHANGE);
}