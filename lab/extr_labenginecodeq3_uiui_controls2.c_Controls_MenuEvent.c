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
struct TYPE_3__ {int id; } ;
typedef  TYPE_1__ menucommon_s ;
struct TYPE_4__ {int /*<<< orphan*/  changesmade; int /*<<< orphan*/  section; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_LOOKING ; 
 int /*<<< orphan*/  C_MISC ; 
 int /*<<< orphan*/  C_MOVEMENT ; 
 int /*<<< orphan*/  C_WEAPONS ; 
 int /*<<< orphan*/  Controls_ResetDefaults_Action ; 
 int /*<<< orphan*/  Controls_ResetDefaults_Draw ; 
 int /*<<< orphan*/  Controls_SetConfig () ; 
 int /*<<< orphan*/  Controls_Update () ; 
#define  ID_ALWAYSRUN 143 
#define  ID_AUTOSWITCH 142 
#define  ID_BACK 141 
#define  ID_DEFAULTS 140 
#define  ID_EXIT 139 
#define  ID_FREELOOK 138 
#define  ID_INVERTMOUSE 137 
#define  ID_JOYENABLE 136 
#define  ID_JOYTHRESHOLD 135 
#define  ID_LOOKING 134 
#define  ID_MISC 133 
#define  ID_MOUSESPEED 132 
#define  ID_MOVEMENT 131 
#define  ID_SAVEANDEXIT 130 
#define  ID_SMOOTHMOUSE 129 
#define  ID_WEAPONS 128 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_ConfirmMenu (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_2__ s_controls ; 

__attribute__((used)) static void Controls_MenuEvent( void* ptr, int event )
{
	switch (((menucommon_s*)ptr)->id)
	{
		case ID_MOVEMENT:
			if (event == QM_ACTIVATED)
			{
				s_controls.section = C_MOVEMENT; 
				Controls_Update();
			}
			break;

		case ID_LOOKING:
			if (event == QM_ACTIVATED)
			{
				s_controls.section = C_LOOKING; 
				Controls_Update();
			}
			break;

		case ID_WEAPONS:
			if (event == QM_ACTIVATED)
			{
				s_controls.section = C_WEAPONS; 
				Controls_Update();
			}
			break;

		case ID_MISC:
			if (event == QM_ACTIVATED)
			{
				s_controls.section = C_MISC; 
				Controls_Update();
			}
			break;

		case ID_DEFAULTS:
			if (event == QM_ACTIVATED)
			{
				UI_ConfirmMenu( "SET TO DEFAULTS?", Controls_ResetDefaults_Draw, Controls_ResetDefaults_Action );
			}
			break;

		case ID_BACK:
			if (event == QM_ACTIVATED)
			{
				if (s_controls.changesmade)
					Controls_SetConfig();
				UI_PopMenu();
			}
			break;

		case ID_SAVEANDEXIT:
			if (event == QM_ACTIVATED)
			{
				Controls_SetConfig();
				UI_PopMenu();
			}
			break;

		case ID_EXIT:
			if (event == QM_ACTIVATED)
			{
				UI_PopMenu();
			}
			break;

		case ID_FREELOOK:
		case ID_MOUSESPEED:
		case ID_INVERTMOUSE:
		case ID_SMOOTHMOUSE:
		case ID_ALWAYSRUN:
		case ID_AUTOSWITCH:
		case ID_JOYENABLE:
		case ID_JOYTHRESHOLD:
			if (event == QM_ACTIVATED)
			{
				s_controls.changesmade = qtrue;
			}
			break;		
	}
}