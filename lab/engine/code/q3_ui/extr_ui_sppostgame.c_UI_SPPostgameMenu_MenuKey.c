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
typedef  int /*<<< orphan*/  sfxHandle_t ;
struct TYPE_4__ {scalar_t__ ignoreKeysTime; int phase; scalar_t__ starttime; int /*<<< orphan*/  menu; } ;
struct TYPE_3__ {scalar_t__ realtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_APPEND ; 
 int K_ESCAPE ; 
 int K_MOUSE2 ; 
 int /*<<< orphan*/  Menu_DefaultKey (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ postgameMenuInfo ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ uis ; 

__attribute__((used)) static sfxHandle_t UI_SPPostgameMenu_MenuKey( int key ) {
	if ( uis.realtime < postgameMenuInfo.ignoreKeysTime ) {
		return 0;
	}

	if( postgameMenuInfo.phase == 1 ) {
		trap_Cmd_ExecuteText( EXEC_APPEND, "abort_podium\n" );
		postgameMenuInfo.phase = 2;
		postgameMenuInfo.starttime = uis.realtime;
		postgameMenuInfo.ignoreKeysTime	= uis.realtime + 250;
		return 0;
	}

	if( postgameMenuInfo.phase == 2 ) {
		postgameMenuInfo.phase = 3;
		postgameMenuInfo.starttime = uis.realtime;
		postgameMenuInfo.ignoreKeysTime	= uis.realtime + 250;
		return 0;
	}

	if( key == K_ESCAPE || key == K_MOUSE2 ) {
		return 0;
	}

	return Menu_DefaultKey( &postgameMenuInfo.menu, key );
}