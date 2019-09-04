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
struct TYPE_4__ {int /*<<< orphan*/  integer; } ;
struct TYPE_3__ {scalar_t__ displayFrac; scalar_t__ finalFrac; } ;

/* Variables and functions */
 int /*<<< orphan*/  Con_ClearNotify () ; 
 int /*<<< orphan*/  Field_Clear (int /*<<< orphan*/ *) ; 
 int KEYCATCH_CONSOLE ; 
 int Key_GetCatcher () ; 
 int /*<<< orphan*/  Key_SetCatcher (int) ; 
 TYPE_2__* com_cl_running ; 
 TYPE_1__ con ; 
 int /*<<< orphan*/  g_consoleField ; 

void Con_Close( void ) {
	if ( !com_cl_running->integer ) {
		return;
	}
	Field_Clear( &g_consoleField );
	Con_ClearNotify ();
	Key_SetCatcher( Key_GetCatcher( ) & ~KEYCATCH_CONSOLE );
	con.finalFrac = 0;				// none visible
	con.displayFrac = 0;
}