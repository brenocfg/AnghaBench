#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  shader3 ;
typedef  int /*<<< orphan*/  shader2 ;
typedef  int /*<<< orphan*/  shader1 ;
struct TYPE_8__ {int /*<<< orphan*/  levelShot; } ;
struct TYPE_7__ {scalar_t__ integer; } ;
struct TYPE_5__ {int /*<<< orphan*/  talkSound; int /*<<< orphan*/  votePassed; int /*<<< orphan*/  voteFailed; } ;
struct TYPE_6__ {scalar_t__ gametype; TYPE_1__ media; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIGCHAR_WIDTH ; 
 int /*<<< orphan*/  CG_AddToTeamChat (char*) ; 
 char const* CG_Argv (int) ; 
 int /*<<< orphan*/  CG_CenterPrint (char const*,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_ConfigStringModified () ; 
 int /*<<< orphan*/  CG_LoadDeferredPlayers () ; 
 int /*<<< orphan*/  CG_MapRestart () ; 
 int /*<<< orphan*/  CG_ParseScores () ; 
 int /*<<< orphan*/  CG_ParseTeamInfo () ; 
 int /*<<< orphan*/  CG_Printf (char*,char const*) ; 
 int /*<<< orphan*/  CG_RemoveChatEscapeChar (char*) ; 
 int /*<<< orphan*/  CG_VoiceChat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHAN_ANNOUNCER ; 
 int /*<<< orphan*/  CHAN_LOCAL_SOUND ; 
 scalar_t__ GT_TEAM ; 
 int MAX_QPATH ; 
 int MAX_SAY_TEXT ; 
 scalar_t__ Q_stricmp (char const*,char*) ; 
 int /*<<< orphan*/  Q_stricmpn (char const*,char*,int) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char const*,int) ; 
 int /*<<< orphan*/  SAY_ALL ; 
 int /*<<< orphan*/  SAY_TEAM ; 
 int /*<<< orphan*/  SAY_TELL ; 
 double SCREEN_HEIGHT ; 
 TYPE_4__ cg ; 
 TYPE_3__ cg_teamChatsOnly ; 
 TYPE_2__ cgs ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int trap_Argc () ; 
 int /*<<< orphan*/  trap_R_RemapShader (char*,char*,char*) ; 
 int /*<<< orphan*/  trap_S_StartLocalSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CG_ServerCommand( void ) {
	const char	*cmd;
	char		text[MAX_SAY_TEXT];

	cmd = CG_Argv(0);

	if ( !cmd[0] ) {
		// server claimed the command
		return;
	}

	if ( !strcmp( cmd, "cp" ) ) {
		CG_CenterPrint( CG_Argv(1), SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH );
		return;
	}

	if ( !strcmp( cmd, "cs" ) ) {
		CG_ConfigStringModified();
		return;
	}

	if ( !strcmp( cmd, "print" ) ) {
		CG_Printf( "%s", CG_Argv(1) );
#ifdef MISSIONPACK
		cmd = CG_Argv(1);			// yes, this is obviously a hack, but so is the way we hear about
									// votes passing or failing
		if ( !Q_stricmpn( cmd, "vote failed", 11 ) || !Q_stricmpn( cmd, "team vote failed", 16 )) {
			trap_S_StartLocalSound( cgs.media.voteFailed, CHAN_ANNOUNCER );
		} else if ( !Q_stricmpn( cmd, "vote passed", 11 ) || !Q_stricmpn( cmd, "team vote passed", 16 ) ) {
			trap_S_StartLocalSound( cgs.media.votePassed, CHAN_ANNOUNCER );
		}
#endif
		return;
	}

	if ( !strcmp( cmd, "chat" ) ) {
		if ( cgs.gametype >= GT_TEAM && cg_teamChatsOnly.integer ) {
			return;
		}

		trap_S_StartLocalSound( cgs.media.talkSound, CHAN_LOCAL_SOUND );
		Q_strncpyz( text, CG_Argv(1), MAX_SAY_TEXT );
		CG_RemoveChatEscapeChar( text );
		CG_Printf( "%s\n", text );
		return;
	}

	if ( !strcmp( cmd, "tchat" ) ) {
		trap_S_StartLocalSound( cgs.media.talkSound, CHAN_LOCAL_SOUND );
		Q_strncpyz( text, CG_Argv(1), MAX_SAY_TEXT );
		CG_RemoveChatEscapeChar( text );
		CG_AddToTeamChat( text );
		CG_Printf( "%s\n", text );
		return;
	}

#ifdef MISSIONPACK
	if ( !strcmp( cmd, "vchat" ) ) {
		CG_VoiceChat( SAY_ALL );
		return;
	}

	if ( !strcmp( cmd, "vtchat" ) ) {
		CG_VoiceChat( SAY_TEAM );
		return;
	}

	if ( !strcmp( cmd, "vtell" ) ) {
		CG_VoiceChat( SAY_TELL );
		return;
	}
#endif

	if ( !strcmp( cmd, "scores" ) ) {
		CG_ParseScores();
		return;
	}

	if ( !strcmp( cmd, "tinfo" ) ) {
		CG_ParseTeamInfo();
		return;
	}

	if ( !strcmp( cmd, "map_restart" ) ) {
		CG_MapRestart();
		return;
	}

	if ( Q_stricmp (cmd, "remapShader") == 0 )
	{
		if (trap_Argc() == 4)
		{
			char shader1[MAX_QPATH];
			char shader2[MAX_QPATH];
			char shader3[MAX_QPATH];

			Q_strncpyz(shader1, CG_Argv(1), sizeof(shader1));
			Q_strncpyz(shader2, CG_Argv(2), sizeof(shader2));
			Q_strncpyz(shader3, CG_Argv(3), sizeof(shader3));

			trap_R_RemapShader(shader1, shader2, shader3);
		}
		
		return;
	}

	// loaddeferred can be both a servercmd and a consolecmd
	if ( !strcmp( cmd, "loaddefered" ) ) {	// FIXME: spelled wrong, but not changing for demo
		CG_LoadDeferredPlayers();
		return;
	}

	// clientLevelShot is sent before taking a special screenshot for
	// the menu system during development
	if ( !strcmp( cmd, "clientLevelShot" ) ) {
		cg.levelShot = qtrue;
		return;
	}

	CG_Printf( "Unknown client game command: %s\n", cmd );
}