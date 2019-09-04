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
typedef  int* vec3_t ;
struct TYPE_5__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__ generic; } ;
typedef  TYPE_2__ menubitmap_s ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {int /*<<< orphan*/  playerinfo; int /*<<< orphan*/  playerModel; } ;
struct TYPE_7__ {int realtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEGS_IDLE ; 
 int MAX_QPATH ; 
 size_t PITCH ; 
 size_t ROLL ; 
 int /*<<< orphan*/  TORSO_STAND ; 
 int /*<<< orphan*/  UI_DrawPlayer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UI_PlayerInfo_SetInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_PlayerInfo_SetModel (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  WP_MACHINEGUN ; 
 size_t YAW ; 
 int /*<<< orphan*/  qfalse ; 
 TYPE_4__ s_playersettings ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,char*,int) ; 
 TYPE_3__ uis ; 
 int /*<<< orphan*/  vec3_origin ; 

__attribute__((used)) static void PlayerSettings_DrawPlayer( void *self ) {
	menubitmap_s	*b;
	vec3_t			viewangles;
	char			buf[MAX_QPATH];

	trap_Cvar_VariableStringBuffer( "model", buf, sizeof( buf ) );
	if ( strcmp( buf, s_playersettings.playerModel ) != 0 ) {
		UI_PlayerInfo_SetModel( &s_playersettings.playerinfo, buf );
		strcpy( s_playersettings.playerModel, buf );

		viewangles[YAW]   = 180 - 30;
		viewangles[PITCH] = 0;
		viewangles[ROLL]  = 0;
		UI_PlayerInfo_SetInfo( &s_playersettings.playerinfo, LEGS_IDLE, TORSO_STAND, viewangles, vec3_origin, WP_MACHINEGUN, qfalse );
	}

	b = (menubitmap_s*) self;
	UI_DrawPlayer( b->generic.x, b->generic.y, b->width, b->height, &s_playersettings.playerinfo, uis.realtime/2 );
}