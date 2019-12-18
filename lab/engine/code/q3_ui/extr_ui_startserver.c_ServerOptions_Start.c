#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_34__ {int curvalue; } ;
struct TYPE_33__ {int curvalue; } ;
struct TYPE_32__ {int curvalue; } ;
struct TYPE_30__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_31__ {TYPE_5__ field; } ;
struct TYPE_28__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_29__ {TYPE_3__ field; } ;
struct TYPE_26__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_27__ {TYPE_1__ field; } ;
struct TYPE_21__ {int curvalue; } ;
struct TYPE_19__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_20__ {TYPE_11__ field; } ;
struct TYPE_18__ {int curvalue; } ;
struct TYPE_25__ {char** playerNameBuffers; int gametype; TYPE_15__* playerTeam; TYPE_14__* playerType; TYPE_13__ punkbuster; TYPE_12__ hostname; TYPE_10__ botSkill; TYPE_9__ pure; TYPE_8__ friendlyfire; TYPE_7__ dedicated; TYPE_6__ flaglimit; TYPE_4__ fraglimit; TYPE_2__ timelimit; } ;
struct TYPE_24__ {size_t currentmap; int /*<<< orphan*/ * maplist; } ;
struct TYPE_23__ {size_t curvalue; } ;
struct TYPE_22__ {int curvalue; } ;

/* Variables and functions */
 int Com_Clamp (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char*,int,...) ; 
 int /*<<< orphan*/  EXEC_APPEND ; 
#define  GT_CTF 131 
#define  GT_FFA 130 
#define  GT_TEAM 129 
#define  GT_TOURNAMENT 128 
 int /*<<< orphan*/  Info_ValueForKey (char const*,char*) ; 
 int PLAYER_SLOTS ; 
 char* UI_GetArenaInfoByNumber (int /*<<< orphan*/ ) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * playerTeam_list ; 
 TYPE_17__ s_serveroptions ; 
 TYPE_16__ s_startserver ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,int) ; 
 char* va (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ServerOptions_Start( void ) {
	int		timelimit;
	int		fraglimit;
	int		maxclients;
	int		dedicated;
	int		friendlyfire;
	int		flaglimit;
	int		pure;
	int		skill;
	int		n;
	char	buf[64];
	const char *info;

	timelimit	 = atoi( s_serveroptions.timelimit.field.buffer );
	fraglimit	 = atoi( s_serveroptions.fraglimit.field.buffer );
	flaglimit	 = atoi( s_serveroptions.flaglimit.field.buffer );
	dedicated	 = s_serveroptions.dedicated.curvalue;
	friendlyfire = s_serveroptions.friendlyfire.curvalue;
	pure		 = s_serveroptions.pure.curvalue;
	skill		 = s_serveroptions.botSkill.curvalue + 1;

	//set maxclients
	for( n = 0, maxclients = 0; n < PLAYER_SLOTS; n++ ) {
		if( s_serveroptions.playerType[n].curvalue == 2 ) {
			continue;
		}
		if( (s_serveroptions.playerType[n].curvalue == 1) && (s_serveroptions.playerNameBuffers[n][0] == 0) ) {
			continue;
		}
		maxclients++;
	}

	switch( s_serveroptions.gametype ) {
	case GT_FFA:
	default:
		trap_Cvar_SetValue( "ui_ffa_fraglimit", fraglimit );
		trap_Cvar_SetValue( "ui_ffa_timelimit", timelimit );
		break;

	case GT_TOURNAMENT:
		trap_Cvar_SetValue( "ui_tourney_fraglimit", fraglimit );
		trap_Cvar_SetValue( "ui_tourney_timelimit", timelimit );
		break;

	case GT_TEAM:
		trap_Cvar_SetValue( "ui_team_fraglimit", fraglimit );
		trap_Cvar_SetValue( "ui_team_timelimit", timelimit );
		trap_Cvar_SetValue( "ui_team_friendly", friendlyfire );
		break;

	case GT_CTF:
		trap_Cvar_SetValue( "ui_ctf_capturelimit", flaglimit );
		trap_Cvar_SetValue( "ui_ctf_timelimit", timelimit );
		trap_Cvar_SetValue( "ui_ctf_friendly", friendlyfire );
		break;
	}

	trap_Cvar_SetValue( "sv_maxclients", Com_Clamp( 0, 12, maxclients ) );
	trap_Cvar_SetValue( "dedicated", Com_Clamp( 0, 2, dedicated ) );
	trap_Cvar_SetValue ("timelimit", Com_Clamp( 0, timelimit, timelimit ) );
	trap_Cvar_SetValue ("fraglimit", Com_Clamp( 0, fraglimit, fraglimit ) );
	trap_Cvar_SetValue ("capturelimit", Com_Clamp( 0, flaglimit, flaglimit ) );
	trap_Cvar_SetValue( "g_friendlyfire", friendlyfire );
	trap_Cvar_SetValue( "sv_pure", pure );
	trap_Cvar_Set("sv_hostname", s_serveroptions.hostname.field.buffer );
	
	trap_Cvar_SetValue( "sv_punkbuster", s_serveroptions.punkbuster.curvalue );

	// the wait commands will allow the dedicated to take effect
	info = UI_GetArenaInfoByNumber( s_startserver.maplist[ s_startserver.currentmap ]);
	trap_Cmd_ExecuteText( EXEC_APPEND, va( "wait ; wait ; map %s\n", Info_ValueForKey( info, "map" )));

	// add bots
	trap_Cmd_ExecuteText( EXEC_APPEND, "wait 3\n" );
	for( n = 1; n < PLAYER_SLOTS; n++ ) {
		if( s_serveroptions.playerType[n].curvalue != 1 ) {
			continue;
		}
		if( s_serveroptions.playerNameBuffers[n][0] == 0 ) {
			continue;
		}
		if( s_serveroptions.playerNameBuffers[n][0] == '-' ) {
			continue;
		}
		if( s_serveroptions.gametype >= GT_TEAM ) {
			Com_sprintf( buf, sizeof(buf), "addbot %s %i %s\n", s_serveroptions.playerNameBuffers[n], skill,
				playerTeam_list[s_serveroptions.playerTeam[n].curvalue] );
		}
		else {
			Com_sprintf( buf, sizeof(buf), "addbot %s %i\n", s_serveroptions.playerNameBuffers[n], skill );
		}
		trap_Cmd_ExecuteText( EXEC_APPEND, buf );
	}

	// set player's team
	if( dedicated == 0 && s_serveroptions.gametype >= GT_TEAM ) {
		// send team command for vanilla q3 game qvm
		trap_Cmd_ExecuteText( EXEC_APPEND, va( "wait 5; team %s\n", playerTeam_list[s_serveroptions.playerTeam[0].curvalue] ) );

		// set g_localTeamPref for ioq3 game qvm
		trap_Cvar_Set( "g_localTeamPref", playerTeam_list[s_serveroptions.playerTeam[0].curvalue] );
	}
}