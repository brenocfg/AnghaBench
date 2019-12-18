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
typedef  int qboolean ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {scalar_t__ state; } ;
struct TYPE_3__ {int /*<<< orphan*/ * binding; } ;

/* Variables and functions */
 scalar_t__ CA_DISCONNECTED ; 
 scalar_t__ CL_BindUICommand (char*) ; 
 int /*<<< orphan*/  Cbuf_AddText (char*) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char,char*,int,unsigned int) ; 
 scalar_t__ Key_GetCatcher () ; 
 int MAX_STRING_CHARS ; 
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ *,int) ; 
 TYPE_2__ clc ; 
 scalar_t__ isspace (char) ; 
 TYPE_1__* keys ; 
 char* strchr (char*,char) ; 

void CL_ParseBinding( int key, qboolean down, unsigned time )
{
	char buf[ MAX_STRING_CHARS ], *p = buf, *end;
	qboolean allCommands, allowUpCmds;

	if( clc.state == CA_DISCONNECTED && Key_GetCatcher( ) == 0 )
		return;
	if( !keys[key].binding || !keys[key].binding[0] )
		return;
	Q_strncpyz( buf, keys[key].binding, sizeof( buf ) );

	// run all bind commands if console, ui, etc aren't reading keys
	allCommands = ( Key_GetCatcher( ) == 0 );

	// allow button up commands if in game even if key catcher is set
	allowUpCmds = ( clc.state != CA_DISCONNECTED );

	while( 1 )
	{
		while( isspace( *p ) )
			p++;
		end = strchr( p, ';' );
		if( end )
			*end = '\0';
		if( *p == '+' )
		{
			// button commands add keynum and time as parameters
			// so that multiple sources can be discriminated and
			// subframe corrected
			if ( allCommands || ( allowUpCmds && !down ) ) {
				char cmd[1024];
				Com_sprintf( cmd, sizeof( cmd ), "%c%s %d %d\n",
					( down ) ? '+' : '-', p + 1, key, time );
				Cbuf_AddText( cmd );
			}
		}
		else if( down )
		{
			// normal commands only execute on key press
			if ( allCommands || CL_BindUICommand( p ) ) {
				Cbuf_AddText( p );
				Cbuf_AddText( "\n" );
			}
		}
		if( !end )
			break;
		p = end + 1;
	}
}