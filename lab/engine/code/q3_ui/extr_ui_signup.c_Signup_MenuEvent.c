#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int id; } ;
typedef  TYPE_9__ menucommon_s ;
struct TYPE_18__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_19__ {TYPE_7__ field; } ;
struct TYPE_16__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_17__ {TYPE_5__ field; } ;
struct TYPE_14__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_15__ {TYPE_3__ field; } ;
struct TYPE_12__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_13__ {TYPE_1__ field; } ;
struct TYPE_11__ {TYPE_8__ email_box; TYPE_6__ password_box; TYPE_4__ name_box; TYPE_2__ again_box; } ;

/* Variables and functions */
#define  ID_CANCEL 129 
#define  ID_SIGNUP 128 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_ForceMenuOff () ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 TYPE_10__ s_signup ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_CL_UI_RankUserCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Signup_MenuEvent( void* ptr, int event ) {
	//char	cmd[1024];
	
	if( event != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_SIGNUP:
		if( strcmp(s_signup.password_box.field.buffer, 
			s_signup.again_box.field.buffer) != 0 )
		{
			// GRANK_FIXME - password mismatch
			break;
		}
		// set name
		//trap_Cvar_Set( "name", s_signup.name_box.field.buffer );
		/*
		trap_Cvar_Set( "rank_name", s_signup.name_box.field.buffer );
		trap_Cvar_Set( "rank_pwd", s_signup.password_box.field.buffer );
		*/

		// create account
		/*
		sprintf( cmd, "cmd rank_create \"%s\" \"%s\" \"%s\"\n", 
			s_signup.name_box.field.buffer, 
			s_signup.password_box.field.buffer, 
			s_signup.email_box.field.buffer );
		trap_Cmd_ExecuteText( EXEC_APPEND, cmd );
		*/
		trap_CL_UI_RankUserCreate(
			s_signup.name_box.field.buffer, 
			s_signup.password_box.field.buffer, 
			s_signup.email_box.field.buffer );

		UI_ForceMenuOff();
		break;
		
	case ID_CANCEL:
		UI_PopMenu();
		break;
	}
}