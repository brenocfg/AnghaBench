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
struct TYPE_4__ {scalar_t__ state; scalar_t__ demoplaying; } ;
struct TYPE_3__ {int repeats; int /*<<< orphan*/  down; } ;

/* Variables and functions */
 scalar_t__ CA_ACTIVE ; 
 scalar_t__ CA_CINEMATIC ; 
 scalar_t__ CA_DISCONNECTED ; 
 int /*<<< orphan*/  CGAME_EVENT_NONE ; 
 int /*<<< orphan*/  CG_EVENT_HANDLING ; 
 int /*<<< orphan*/  CG_KEY_EVENT ; 
 int /*<<< orphan*/  CL_Disconnect_f () ; 
 int /*<<< orphan*/  CL_ParseBinding (int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  Con_ToggleConsole_f () ; 
 int /*<<< orphan*/  Console_Key (int) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  Cvar_SetValue (char*,int) ; 
 int /*<<< orphan*/  Cvar_VariableIntegerValue (char*) ; 
 scalar_t__ Cvar_VariableValue (char*) ; 
 int KEYCATCH_CGAME ; 
 int KEYCATCH_CONSOLE ; 
 int KEYCATCH_MESSAGE ; 
 int KEYCATCH_UI ; 
 size_t K_ALT ; 
 int K_CONSOLE ; 
 int K_ENTER ; 
 int K_ESCAPE ; 
 int K_MOUSE1 ; 
 size_t K_SHIFT ; 
 int /*<<< orphan*/  Key_ClearStates () ; 
 int Key_GetCatcher () ; 
 int /*<<< orphan*/  Key_SetCatcher (int) ; 
 int /*<<< orphan*/  Message_Key (int) ; 
 int /*<<< orphan*/  S_StopAllSounds () ; 
 int /*<<< orphan*/  UIMENU_INGAME ; 
 int /*<<< orphan*/  UIMENU_MAIN ; 
 int /*<<< orphan*/  UI_KEY_EVENT ; 
 int /*<<< orphan*/  UI_SET_ACTIVE_MENU ; 
 int /*<<< orphan*/  VM_Call (scalar_t__,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  anykeydown ; 
 scalar_t__ cgvm ; 
 TYPE_2__ clc ; 
 TYPE_1__* keys ; 
 int /*<<< orphan*/  qtrue ; 
 scalar_t__ uivm ; 

void CL_KeyDownEvent( int key, unsigned time )
{
	keys[key].down = qtrue;
	keys[key].repeats++;
	if( keys[key].repeats == 1 )
		anykeydown++;

	if( keys[K_ALT].down && key == K_ENTER )
	{
		// don't repeat fullscreen toggle when keys are held down
		if ( keys[K_ENTER].repeats > 1 ) {
			return;
		}

		Cvar_SetValue( "r_fullscreen",
			!Cvar_VariableIntegerValue( "r_fullscreen" ) );
		return;
	}

	// console key is hardcoded, so the user can never unbind it
	if( key == K_CONSOLE || ( keys[K_SHIFT].down && key == K_ESCAPE ) )
	{
		Con_ToggleConsole_f ();
		Key_ClearStates ();
		return;
	}


	// keys can still be used for bound actions
	if ( ( key < 128 || key == K_MOUSE1 ) &&
		( clc.demoplaying || clc.state == CA_CINEMATIC ) && Key_GetCatcher( ) == 0 ) {

		if (Cvar_VariableValue ("com_cameraMode") == 0) {
			Cvar_Set ("nextdemo","");
			key = K_ESCAPE;
		}
	}

	// escape is always handled special
	if ( key == K_ESCAPE ) {
		if ( Key_GetCatcher( ) & KEYCATCH_MESSAGE ) {
			// clear message mode
			Message_Key( key );
			return;
		}

		// escape always gets out of CGAME stuff
		if (Key_GetCatcher( ) & KEYCATCH_CGAME) {
			Key_SetCatcher( Key_GetCatcher( ) & ~KEYCATCH_CGAME );
			VM_Call (cgvm, CG_EVENT_HANDLING, CGAME_EVENT_NONE);
			return;
		}

		if ( !( Key_GetCatcher( ) & KEYCATCH_UI ) ) {
			if ( clc.state == CA_ACTIVE && !clc.demoplaying ) {
				VM_Call( uivm, UI_SET_ACTIVE_MENU, UIMENU_INGAME );
			}
			else if ( clc.state != CA_DISCONNECTED ) {
				CL_Disconnect_f();
				S_StopAllSounds();
				VM_Call( uivm, UI_SET_ACTIVE_MENU, UIMENU_MAIN );
			}
			return;
		}

		VM_Call( uivm, UI_KEY_EVENT, key, qtrue );
		return;
	}

	// send the bound action
	CL_ParseBinding( key, qtrue, time );

	// distribute the key down event to the appropriate handler
	if ( Key_GetCatcher( ) & KEYCATCH_CONSOLE ) {
		Console_Key( key );
	} else if ( Key_GetCatcher( ) & KEYCATCH_UI ) {
		if ( uivm ) {
			VM_Call( uivm, UI_KEY_EVENT, key, qtrue );
		} 
	} else if ( Key_GetCatcher( ) & KEYCATCH_CGAME ) {
		if ( cgvm ) {
			VM_Call( cgvm, CG_KEY_EVENT, key, qtrue );
		} 
	} else if ( Key_GetCatcher( ) & KEYCATCH_MESSAGE ) {
		Message_Key( key );
	} else if ( clc.state == CA_DISCONNECTED ) {
		Console_Key( key );
	}
}