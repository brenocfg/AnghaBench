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

/* Variables and functions */
 int /*<<< orphan*/  Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_GameRestart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_Set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 

void Com_GameRestart_f(void)
{
	Cvar_Set("fs_game", Cmd_Argv(1));

	Com_GameRestart(0, qtrue);
}