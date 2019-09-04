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
struct TYPE_2__ {int /*<<< orphan*/  checksumFeed; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cvar_Set2 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_ConditionalRestart (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cl_oldGame ; 
 scalar_t__ cl_oldGameSet ; 
 TYPE_1__ clc ; 
 scalar_t__ qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static void CL_OldGame(void)
{
	if(cl_oldGameSet)
	{
		// change back to previous fs_game
		cl_oldGameSet = qfalse;
		Cvar_Set2("fs_game", cl_oldGame, qtrue);
		FS_ConditionalRestart(clc.checksumFeed, qfalse);
	}
}