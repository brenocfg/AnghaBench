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
typedef  int /*<<< orphan*/  cleanName ;
struct TYPE_3__ {char* stringData; int* stringOffsets; } ;
struct TYPE_4__ {TYPE_1__ gameState; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_AddReliableCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CS_PLAYERS ; 
 size_t CS_SERVERINFO ; 
 int Cmd_Argc () ; 
 char* Cmd_ArgsFrom (int) ; 
 char* Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_FieldStringToPlayerName (char*,int,char*) ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int /*<<< orphan*/  Info_ValueForKey (char const*,char*) ; 
 int MAX_NAME_LENGTH ; 
 int /*<<< orphan*/  Q_CleanStr (char*) ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ ,int) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 TYPE_2__ cl ; 
 int /*<<< orphan*/  qfalse ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  va (char*,int,char*) ; 

void CL_Sayto_f( void ) {
	char		*rawname;
	char		name[MAX_NAME_LENGTH];
	char		cleanName[MAX_NAME_LENGTH];
	const char	*info;
	int			count;
	int			i;
	int			clientNum;
	char		*p;

	if ( Cmd_Argc() < 3 ) {
		Com_Printf ("sayto <player name> <text>\n");
		return;
	}

	rawname = Cmd_Argv(1);

	Com_FieldStringToPlayerName( name, MAX_NAME_LENGTH, rawname );

	info = cl.gameState.stringData + cl.gameState.stringOffsets[CS_SERVERINFO];
	count = atoi( Info_ValueForKey( info, "sv_maxclients" ) );

	clientNum = -1;
	for( i = 0; i < count; i++ ) {

		info = cl.gameState.stringData + cl.gameState.stringOffsets[CS_PLAYERS+i];
		Q_strncpyz( cleanName, Info_ValueForKey( info, "n" ), sizeof(cleanName) );
		Q_CleanStr( cleanName );

		if ( !Q_stricmp( cleanName, name ) ) {
			clientNum = i;
			break;
		}
	}
	if( clientNum <= -1 )
	{
		Com_Printf ("No such player name: %s.\n", name);
		return;
	}

	p = Cmd_ArgsFrom(2);

	if ( *p == '"' ) {
		p++;
		p[strlen(p)-1] = 0;
	}

	CL_AddReliableCommand(va("tell %i \"%s\"", clientNum, p ), qfalse);
}