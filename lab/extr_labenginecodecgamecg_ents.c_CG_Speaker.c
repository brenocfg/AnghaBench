#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int clientNum; size_t eventParm; int frame; int /*<<< orphan*/  number; } ;
struct TYPE_7__ {scalar_t__ miscTime; TYPE_1__ currentState; } ;
typedef  TYPE_2__ centity_t ;
struct TYPE_9__ {scalar_t__ time; } ;
struct TYPE_8__ {int /*<<< orphan*/ * gameSounds; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_ITEM ; 
 TYPE_4__ cg ; 
 TYPE_3__ cgs ; 
 int crandom () ; 
 int /*<<< orphan*/  trap_S_StartSound (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CG_Speaker( centity_t *cent ) {
	if ( ! cent->currentState.clientNum ) {	// FIXME: use something other than clientNum...
		return;		// not auto triggering
	}

	if ( cg.time < cent->miscTime ) {
		return;
	}

	trap_S_StartSound (NULL, cent->currentState.number, CHAN_ITEM, cgs.gameSounds[cent->currentState.eventParm] );

	//	ent->s.frame = ent->wait * 10;
	//	ent->s.clientNum = ent->random * 10;
	cent->miscTime = cg.time + cent->currentState.frame * 100 + cent->currentState.clientNum * 100 * crandom();
}