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
struct TYPE_4__ {int /*<<< orphan*/  shader; } ;
struct TYPE_6__ {int /*<<< orphan*/  silenceSound; int /*<<< orphan*/  nightmareSound; int /*<<< orphan*/ * skillpics; TYPE_1__ art_skillPic; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_ANNOUNCER ; 
 int ID_BABY ; 
 int ID_NIGHTMARE ; 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  SetSkillColor (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  color_red ; 
 int /*<<< orphan*/  color_white ; 
 TYPE_3__ skillMenuInfo ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,int) ; 
 scalar_t__ trap_Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  trap_S_StartLocalSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void UI_SPSkillMenu_SkillEvent( void *ptr, int notification ) {
	int		id;
	int		skill;

	if (notification != QM_ACTIVATED)
		return;

	SetSkillColor( (int)trap_Cvar_VariableValue( "g_spSkill" ), color_red );

	id = ((menucommon_s*)ptr)->id;
	skill = id - ID_BABY + 1;
	trap_Cvar_SetValue( "g_spSkill", skill );

	SetSkillColor( skill, color_white );
	skillMenuInfo.art_skillPic.shader = skillMenuInfo.skillpics[skill - 1];

	if( id == ID_NIGHTMARE ) {
		trap_S_StartLocalSound( skillMenuInfo.nightmareSound, CHAN_ANNOUNCER );
	}
	else {
		trap_S_StartLocalSound( skillMenuInfo.silenceSound, CHAN_ANNOUNCER );
	}
}