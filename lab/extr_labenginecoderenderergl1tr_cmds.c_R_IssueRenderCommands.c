#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ cmds; scalar_t__ used; } ;
typedef  TYPE_1__ renderCommandList_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_7__ {TYPE_1__ commands; } ;
struct TYPE_6__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_ExecuteRenderCommands (scalar_t__) ; 
 int RC_END_OF_LIST ; 
 int /*<<< orphan*/  R_PerformanceCounters () ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 TYPE_3__* backEndData ; 
 TYPE_2__* r_skipBackEnd ; 

void R_IssueRenderCommands( qboolean runPerformanceCounters ) {
	renderCommandList_t	*cmdList;

	cmdList = &backEndData->commands;
	assert(cmdList);
	// add an end-of-list command
	*(int *)(cmdList->cmds + cmdList->used) = RC_END_OF_LIST;

	// clear it out, in case this is a sync and not a buffer flip
	cmdList->used = 0;

	if ( runPerformanceCounters ) {
		R_PerformanceCounters();
	}

	// actually start the commands going
	if ( !r_skipBackEnd->integer ) {
		// let it start on the new batch
		RB_ExecuteRenderCommands( cmdList->cmds );
	}
}