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
 int CG_CrosshairPlayer () ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  trap_Argv (int,char*,int) ; 
 int /*<<< orphan*/  trap_SendClientCommand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,int,int /*<<< orphan*/ ) ; 

void CG_TargetCommand_f( void ) {
	int		targetNum;
	char	test[4];

	targetNum = CG_CrosshairPlayer();
	if ( targetNum == -1 ) {
		return;
	}

	trap_Argv( 1, test, 4 );
	trap_SendClientCommand( va( "gc %i %i", targetNum, atoi( test ) ) );
}