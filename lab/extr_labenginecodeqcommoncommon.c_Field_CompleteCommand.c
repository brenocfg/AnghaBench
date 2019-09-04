#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_4__ {char* buffer; int /*<<< orphan*/  cursor; } ;
struct TYPE_3__ {scalar_t__ integer; } ;

/* Variables and functions */
 int Cmd_Argc () ; 
 void* Cmd_Argv (int) ; 
 int /*<<< orphan*/  Cmd_CommandCompletion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cmd_CompleteArgument (char const*,char*,int) ; 
 int /*<<< orphan*/  Cmd_TokenizeStringIgnoreQuotes (char*) ; 
 char* Com_SkipCharset (char*,char*) ; 
 int /*<<< orphan*/  Cvar_CommandCompletion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Field_Complete () ; 
 char* Field_FindFirstSeparator (char*) ; 
 int /*<<< orphan*/  FindMatches ; 
 int /*<<< orphan*/  PrintCvarMatches ; 
 int /*<<< orphan*/  PrintMatches ; 
 TYPE_2__* completionField ; 
 char* completionString ; 
 TYPE_1__* con_autochat ; 
 scalar_t__ matchCount ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 scalar_t__ qtrue ; 
 scalar_t__* shortestMatch ; 
 scalar_t__ strlen (char*) ; 

void Field_CompleteCommand( char *cmd,
		qboolean doCommands, qboolean doCvars )
{
	int		completionArgument = 0;

	// Skip leading whitespace and quotes
	cmd = Com_SkipCharset( cmd, " \"" );

	Cmd_TokenizeStringIgnoreQuotes( cmd );
	completionArgument = Cmd_Argc( );

	// If there is trailing whitespace on the cmd
	if( *( cmd + strlen( cmd ) - 1 ) == ' ' )
	{
		completionString = "";
		completionArgument++;
	}
	else
		completionString = Cmd_Argv( completionArgument - 1 );

#ifndef DEDICATED
	// add a '\' to the start of the buffer if it might be sent as chat otherwise
	if( con_autochat->integer && completionField->buffer[ 0 ] &&
			completionField->buffer[ 0 ] != '\\' )
	{
		if( completionField->buffer[ 0 ] != '/' )
		{
			// Buffer is full, refuse to complete
			if( strlen( completionField->buffer ) + 1 >=
				sizeof( completionField->buffer ) )
				return;

			memmove( &completionField->buffer[ 1 ],
				&completionField->buffer[ 0 ],
				strlen( completionField->buffer ) + 1 );
			completionField->cursor++;
		}

		completionField->buffer[ 0 ] = '\\';
	}
#endif

	if( completionArgument > 1 )
	{
		const char *baseCmd = Cmd_Argv( 0 );
		char *p;

#ifndef DEDICATED
		// This should always be true
		if( baseCmd[ 0 ] == '\\' || baseCmd[ 0 ] == '/' )
			baseCmd++;
#endif

		if( ( p = Field_FindFirstSeparator( cmd ) ) )
			Field_CompleteCommand( p + 1, qtrue, qtrue ); // Compound command
		else
			Cmd_CompleteArgument( baseCmd, cmd, completionArgument ); 
	}
	else
	{
		if( completionString[0] == '\\' || completionString[0] == '/' )
			completionString++;

		matchCount = 0;
		shortestMatch[ 0 ] = 0;

		if( strlen( completionString ) == 0 )
			return;

		if( doCommands )
			Cmd_CommandCompletion( FindMatches );

		if( doCvars )
			Cvar_CommandCompletion( FindMatches );

		if( !Field_Complete( ) )
		{
			// run through again, printing matches
			if( doCommands )
				Cmd_CommandCompletion( PrintMatches );

			if( doCvars )
				Cvar_CommandCompletion( PrintCvarMatches );
		}
	}
}