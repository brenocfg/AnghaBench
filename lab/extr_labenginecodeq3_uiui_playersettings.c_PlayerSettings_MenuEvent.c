#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int id; } ;
typedef  TYPE_2__ menucommon_s ;
struct TYPE_4__ {int curvalue; } ;
struct TYPE_6__ {TYPE_1__ handicap; } ;

/* Variables and functions */
#define  ID_BACK 130 
#define  ID_HANDICAP 129 
#define  ID_MODEL 128 
 int /*<<< orphan*/  PlayerSettings_SaveChanges () ; 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_PlayerModelMenu () ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 TYPE_3__ s_playersettings ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,int) ; 

__attribute__((used)) static void PlayerSettings_MenuEvent( void* ptr, int event ) {
	if( event != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_HANDICAP:
		trap_Cvar_Set( "handicap", va( "%i", 100 - 25 * s_playersettings.handicap.curvalue ) );
		break;

	case ID_MODEL:
		PlayerSettings_SaveChanges();
		UI_PlayerModelMenu();
		break;

	case ID_BACK:
		PlayerSettings_SaveChanges();
		UI_PopMenu();
		break;
	}
}