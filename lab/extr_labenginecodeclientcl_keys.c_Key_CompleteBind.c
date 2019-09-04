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
 char* Com_SkipTokens (char*,int,char*) ; 
 int /*<<< orphan*/  Field_CompleteCommand (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Field_CompleteKeyname () ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static void Key_CompleteBind( char *args, int argNum )
{
	char *p;

	if( argNum == 2 )
	{
		// Skip "bind "
		p = Com_SkipTokens( args, 1, " " );

		if( p > args )
			Field_CompleteKeyname( );
	}
	else if( argNum >= 3 )
	{
		// Skip "bind <key> "
		p = Com_SkipTokens( args, 2, " " );

		if( p > args )
			Field_CompleteCommand( p, qtrue, qtrue );
	}
}