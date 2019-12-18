#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int id; } ;
typedef  TYPE_5__ menucommon_s ;
struct TYPE_9__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_10__ {TYPE_3__ field; } ;
struct TYPE_7__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_8__ {TYPE_1__ field; } ;
struct TYPE_12__ {TYPE_4__ password_box; TYPE_2__ name_box; } ;

/* Variables and functions */
#define  ID_CANCEL 129 
#define  ID_LOGIN 128 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_ForceMenuOff () ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 TYPE_6__ s_login ; 
 int /*<<< orphan*/  trap_CL_UI_RankUserLogin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Login_MenuEvent( void* ptr, int event ) {
	if( event != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_LOGIN:
		// set name								``
		//trap_Cvar_Set( "name", s_login.name_box.field.buffer );
		/*
		trap_Cvar_Set( "rank_name", s_login.name_box.field.buffer );
		trap_Cvar_Set( "rank_pwd", s_login.password_box.field.buffer );
		*/

		// login
		trap_CL_UI_RankUserLogin(
			s_login.name_box.field.buffer, 
			s_login.password_box.field.buffer );

		UI_ForceMenuOff();
		break;
		
	case ID_CANCEL:
		UI_PopMenu();
		break;
	}
}