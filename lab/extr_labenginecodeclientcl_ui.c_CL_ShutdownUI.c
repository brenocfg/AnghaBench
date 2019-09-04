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
struct TYPE_2__ {int /*<<< orphan*/  uiStarted; } ;

/* Variables and functions */
 int KEYCATCH_UI ; 
 int Key_GetCatcher () ; 
 int /*<<< orphan*/  Key_SetCatcher (int) ; 
 int /*<<< orphan*/  UI_SHUTDOWN ; 
 int /*<<< orphan*/  VM_Call (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_Free (int /*<<< orphan*/ *) ; 
 TYPE_1__ cls ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/ * uivm ; 

void CL_ShutdownUI( void ) {
	Key_SetCatcher( Key_GetCatcher( ) & ~KEYCATCH_UI );
	cls.uiStarted = qfalse;
	if ( !uivm ) {
		return;
	}
	VM_Call( uivm, UI_SHUTDOWN );
	VM_Free( uivm );
	uivm = NULL;
}