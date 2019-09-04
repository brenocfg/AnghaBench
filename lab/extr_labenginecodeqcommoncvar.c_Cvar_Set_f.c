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
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ cvar_t ;

/* Variables and functions */
 int CVAR_ARCHIVE ; 
 int CVAR_SERVERINFO ; 
 int CVAR_USERINFO ; 
 int Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_ArgsFrom (int) ; 
 char* Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_Printf (char*,char*) ; 
 int /*<<< orphan*/  Cvar_Print_f () ; 
 TYPE_1__* Cvar_Set2 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cvar_modifiedFlags ; 
 int /*<<< orphan*/  qfalse ; 

void Cvar_Set_f( void ) {
	int		c;
	char	*cmd;
	cvar_t	*v;

	c = Cmd_Argc();
	cmd = Cmd_Argv(0);

	if ( c < 2 ) {
		Com_Printf ("usage: %s <variable> <value>\n", cmd);
		return;
	}
	if ( c == 2 ) {
		Cvar_Print_f();
		return;
	}

	v = Cvar_Set2 (Cmd_Argv(1), Cmd_ArgsFrom(2), qfalse);
	if( !v ) {
		return;
	}
	switch( cmd[3] ) {
		case 'a':
			if( !( v->flags & CVAR_ARCHIVE ) ) {
				v->flags |= CVAR_ARCHIVE;
				cvar_modifiedFlags |= CVAR_ARCHIVE;
			}
			break;
		case 'u':
			if( !( v->flags & CVAR_USERINFO ) ) {
				v->flags |= CVAR_USERINFO;
				cvar_modifiedFlags |= CVAR_USERINFO;
			}
			break;
		case 's':
			if( !( v->flags & CVAR_SERVERINFO ) ) {
				v->flags |= CVAR_SERVERINFO;
				cvar_modifiedFlags |= CVAR_SERVERINFO;
			}
			break;
	}
}