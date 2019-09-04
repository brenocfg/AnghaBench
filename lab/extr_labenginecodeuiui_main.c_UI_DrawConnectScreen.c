#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* updateInfoString; int connState; char* connectPacketCount; int /*<<< orphan*/  servername; int /*<<< orphan*/  messageString; } ;
typedef  TYPE_1__ uiClientState_t ;
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  menuDef_t ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  downloadName ;

/* Variables and functions */
#define  CA_CHALLENGING 132 
#define  CA_CONNECTED 131 
#define  CA_CONNECTING 130 
#define  CA_LOADING 129 
#define  CA_PRIMED 128 
 int /*<<< orphan*/  CS_SERVERINFO ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITEM_TEXTSTYLE_SHADOWEDMORE ; 
 char* Info_ValueForKey (char*,char*) ; 
 int MAX_INFO_VALUE ; 
 int /*<<< orphan*/  Menu_Paint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Menus_FindByName (char*) ; 
 scalar_t__ Q_stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Text_PaintCenter (float,float,float,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Text_PaintCenter_AutoWrapped (float,float,int,int,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DisplayDownloadInfo (char*,float,float,float) ; 
 int /*<<< orphan*/  colorWhite ; 
 int lastConnState ; 
 char* lastLoadingText ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,char*,int) ; 
 int /*<<< orphan*/  trap_GetClientState (TYPE_1__*) ; 
 scalar_t__ trap_GetConfigString (int /*<<< orphan*/ ,char*,int) ; 
 char* va (char*,char*) ; 

void UI_DrawConnectScreen( qboolean overlay ) {
	char			*s;
	uiClientState_t	cstate;
	char			info[MAX_INFO_VALUE];
	char text[256];
	float centerPoint, yStart, scale;
	
	menuDef_t *menu = Menus_FindByName("Connect");


	if ( !overlay && menu ) {
		Menu_Paint(menu, qtrue);
	}

	if (!overlay) {
		centerPoint = 320;
		yStart = 130;
		scale = 0.5f;
	} else {
		return;
	}

	// see what information we should display
	trap_GetClientState( &cstate );

	info[0] = '\0';
	if( trap_GetConfigString( CS_SERVERINFO, info, sizeof(info) ) ) {
		Text_PaintCenter(centerPoint, yStart, scale, colorWhite, va( "Loading %s", Info_ValueForKey( info, "mapname" )), 0);
	}

	if (!Q_stricmp(cstate.servername,"localhost")) {
		Text_PaintCenter(centerPoint, yStart + 48, scale, colorWhite, "Starting up...", ITEM_TEXTSTYLE_SHADOWEDMORE);
	} else {
		Com_sprintf(text, sizeof(text), "Connecting to %s", cstate.servername);
		Text_PaintCenter(centerPoint, yStart + 48, scale, colorWhite,text , ITEM_TEXTSTYLE_SHADOWEDMORE);
	}

	// display global MOTD at bottom
	Text_PaintCenter(centerPoint, 600, scale, colorWhite, Info_ValueForKey( cstate.updateInfoString, "motd" ), 0);
	// print any server info (server full, bad version, etc)
	if ( cstate.connState < CA_CONNECTED ) {
		Text_PaintCenter_AutoWrapped(centerPoint, yStart + 176, 630, 20, scale, colorWhite, cstate.messageString, 0);
	}

	if ( lastConnState > cstate.connState ) {
		lastLoadingText[0] = '\0';
	}
	lastConnState = cstate.connState;

	switch ( cstate.connState ) {
	case CA_CONNECTING:
		s = va("Awaiting connection...%i", cstate.connectPacketCount);
		break;
	case CA_CHALLENGING:
		s = va("Awaiting challenge...%i", cstate.connectPacketCount);
		break;
	case CA_CONNECTED: {
		char downloadName[MAX_INFO_VALUE];

			trap_Cvar_VariableStringBuffer( "cl_downloadName", downloadName, sizeof(downloadName) );
			if (*downloadName) {
				UI_DisplayDownloadInfo( downloadName, centerPoint, yStart, scale );
				return;
			}
		}
		s = "Awaiting gamestate...";
		break;
	case CA_LOADING:
		return;
	case CA_PRIMED:
		return;
	default:
		return;
	}


	if (Q_stricmp(cstate.servername,"localhost")) {
		Text_PaintCenter(centerPoint, yStart + 80, scale, colorWhite, s, 0);
	}

	// password required / connection rejected information goes here
}