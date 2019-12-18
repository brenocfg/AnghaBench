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
struct TYPE_2__ {int /*<<< orphan*/  down; scalar_t__ repeats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_KEY_EVENT ; 
 int /*<<< orphan*/  CL_ParseBinding (int,int /*<<< orphan*/ ,unsigned int) ; 
 int KEYCATCH_CGAME ; 
 int KEYCATCH_UI ; 
 int K_CONSOLE ; 
 int K_ESCAPE ; 
 size_t K_SHIFT ; 
 int Key_GetCatcher () ; 
 int /*<<< orphan*/  UI_KEY_EVENT ; 
 int /*<<< orphan*/  VM_Call (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ anykeydown ; 
 scalar_t__ cgvm ; 
 TYPE_1__* keys ; 
 int /*<<< orphan*/  qfalse ; 
 scalar_t__ uivm ; 

void CL_KeyUpEvent( int key, unsigned time )
{
	keys[key].repeats = 0;
	keys[key].down = qfalse;
	anykeydown--;

	if (anykeydown < 0) {
		anykeydown = 0;
	}

	// don't process key-up events for the console key
	if ( key == K_CONSOLE || ( key == K_ESCAPE && keys[K_SHIFT].down ) )
		return;

	//
	// key up events only perform actions if the game key binding is
	// a button command (leading + sign).  These will be processed even in
	// console mode and menu mode, to keep the character from continuing
	// an action started before a mode switch.
	//
	CL_ParseBinding( key, qfalse, time );

	if ( Key_GetCatcher( ) & KEYCATCH_UI && uivm ) {
		VM_Call( uivm, UI_KEY_EVENT, key, qfalse );
	} else if ( Key_GetCatcher( ) & KEYCATCH_CGAME && cgvm ) {
		VM_Call( cgvm, CG_KEY_EVENT, key, qfalse );
	}
}