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
typedef  int /*<<< orphan*/  shader3 ;
typedef  int /*<<< orphan*/  shader2 ;
typedef  int /*<<< orphan*/  shader1 ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {int frameTime; int realTime; } ;
struct TYPE_4__ {TYPE_1__ uiDC; } ;

/* Variables and functions */
 int MAX_QPATH ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 
 char* UI_Argv (int) ; 
 int /*<<< orphan*/  UI_Cache_f () ; 
 int /*<<< orphan*/  UI_CalcPostGameStats () ; 
 int /*<<< orphan*/  UI_Load () ; 
 int /*<<< orphan*/  UI_Report () ; 
 int /*<<< orphan*/  UI_ShowPostGame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int trap_Argc () ; 
 int /*<<< orphan*/  trap_R_RemapShader (char*,char*,char*) ; 
 TYPE_2__ uiInfo ; 

qboolean UI_ConsoleCommand( int realTime ) {
	char	*cmd;

	uiInfo.uiDC.frameTime = realTime - uiInfo.uiDC.realTime;
	uiInfo.uiDC.realTime = realTime;

	cmd = UI_Argv( 0 );

	// ensure minimum menu data is available
	//Menu_Cache();

	if ( Q_stricmp (cmd, "ui_test") == 0 ) {
		UI_ShowPostGame(qtrue);
		return qtrue;
	}

	if ( Q_stricmp (cmd, "ui_report") == 0 ) {
		UI_Report();
		return qtrue;
	}
	
	if ( Q_stricmp (cmd, "ui_load") == 0 ) {
		UI_Load();
		return qtrue;
	}

	if ( Q_stricmp (cmd, "remapShader") == 0 ) {
		if (trap_Argc() == 4) {
			char shader1[MAX_QPATH];
			char shader2[MAX_QPATH];
			char shader3[MAX_QPATH];
			
			Q_strncpyz(shader1, UI_Argv(1), sizeof(shader1));
			Q_strncpyz(shader2, UI_Argv(2), sizeof(shader2));
			Q_strncpyz(shader3, UI_Argv(3), sizeof(shader3));
			
			trap_R_RemapShader(shader1, shader2, shader3);
			return qtrue;
		}
	}

	if ( Q_stricmp (cmd, "postgame") == 0 ) {
		UI_CalcPostGameStats();
		return qtrue;
	}

	if ( Q_stricmp (cmd, "ui_cache") == 0 ) {
		UI_Cache_f();
		return qtrue;
	}

	if ( Q_stricmp (cmd, "ui_teamOrders") == 0 ) {
		//UI_TeamOrdersMenu_f();
		return qtrue;
	}


	if ( Q_stricmp (cmd, "ui_cdkey") == 0 ) {
		//UI_CDKeyMenu_f();
		return qtrue;
	}

	return qfalse;
}