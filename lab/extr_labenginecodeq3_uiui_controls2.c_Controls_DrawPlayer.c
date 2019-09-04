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
struct TYPE_5__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__ generic; } ;
typedef  TYPE_2__ menubitmap_s ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {int /*<<< orphan*/  playerinfo; int /*<<< orphan*/  playerModel; } ;
struct TYPE_7__ {int realtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANIM_IDLE ; 
 int /*<<< orphan*/  Controls_UpdateModel (int /*<<< orphan*/ ) ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  UI_DrawPlayer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UI_PlayerInfo_SetModel (int /*<<< orphan*/ *,char*) ; 
 TYPE_4__ s_controls ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,char*,int) ; 
 TYPE_3__ uis ; 

__attribute__((used)) static void Controls_DrawPlayer( void *self ) {
	menubitmap_s	*b;
	char			buf[MAX_QPATH];

	trap_Cvar_VariableStringBuffer( "model", buf, sizeof( buf ) );
	if ( strcmp( buf, s_controls.playerModel ) != 0 ) {
		UI_PlayerInfo_SetModel( &s_controls.playerinfo, buf );
		strcpy( s_controls.playerModel, buf );
		Controls_UpdateModel( ANIM_IDLE );
	}

	b = (menubitmap_s*) self;
	UI_DrawPlayer( b->generic.x, b->generic.y, b->width, b->height, &s_controls.playerinfo, uis.realtime/2 );
}