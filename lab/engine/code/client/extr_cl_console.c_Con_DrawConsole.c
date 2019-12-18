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
struct TYPE_4__ {scalar_t__ state; } ;
struct TYPE_3__ {double displayFrac; } ;

/* Variables and functions */
 scalar_t__ CA_ACTIVE ; 
 scalar_t__ CA_DISCONNECTED ; 
 int /*<<< orphan*/  Con_CheckResize () ; 
 int /*<<< orphan*/  Con_DrawNotify () ; 
 int /*<<< orphan*/  Con_DrawSolidConsole (double) ; 
 int KEYCATCH_CGAME ; 
 int KEYCATCH_UI ; 
 int Key_GetCatcher () ; 
 TYPE_2__ clc ; 
 TYPE_1__ con ; 

void Con_DrawConsole( void ) {
	// check for console width changes from a vid mode change
	Con_CheckResize ();

	// if disconnected, render console full screen
	if ( clc.state == CA_DISCONNECTED ) {
		if ( !( Key_GetCatcher( ) & (KEYCATCH_UI | KEYCATCH_CGAME)) ) {
			Con_DrawSolidConsole( 1.0 );
			return;
		}
	}

	if ( con.displayFrac ) {
		Con_DrawSolidConsole( con.displayFrac );
	} else {
		// draw notify lines
		if ( clc.state == CA_ACTIVE ) {
			Con_DrawNotify ();
		}
	}
}