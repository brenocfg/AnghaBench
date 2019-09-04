#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ CA_DISCONNECTED ; 
 int /*<<< orphan*/  Field_CharEvent (int /*<<< orphan*/ *,int) ; 
 int KEYCATCH_CONSOLE ; 
 int KEYCATCH_MESSAGE ; 
 int KEYCATCH_UI ; 
 int K_CHAR_FLAG ; 
 int Key_GetCatcher () ; 
 int /*<<< orphan*/  UI_KEY_EVENT ; 
 int /*<<< orphan*/  VM_Call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chatField ; 
 TYPE_1__ clc ; 
 int /*<<< orphan*/  g_consoleField ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  uivm ; 

void CL_CharEvent( int key ) {
	// delete is not a printable character and is
	// otherwise handled by Field_KeyDownEvent
	if ( key == 127 ) {
		return;
	}

	// distribute the key down event to the appropriate handler
	if ( Key_GetCatcher( ) & KEYCATCH_CONSOLE )
	{
		Field_CharEvent( &g_consoleField, key );
	}
	else if ( Key_GetCatcher( ) & KEYCATCH_UI )
	{
		VM_Call( uivm, UI_KEY_EVENT, key | K_CHAR_FLAG, qtrue );
	}
	else if ( Key_GetCatcher( ) & KEYCATCH_MESSAGE ) 
	{
		Field_CharEvent( &chatField, key );
	}
	else if ( clc.state == CA_DISCONNECTED )
	{
		Field_CharEvent( &g_consoleField, key );
	}
}