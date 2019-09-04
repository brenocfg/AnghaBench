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
struct TYPE_2__ {int /*<<< orphan*/  cgameStarted; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_SHUTDOWN ; 
 int KEYCATCH_CGAME ; 
 int Key_GetCatcher () ; 
 int /*<<< orphan*/  Key_SetCatcher (int) ; 
 int /*<<< orphan*/  VM_Call (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cgvm ; 
 TYPE_1__ cls ; 
 int /*<<< orphan*/  qfalse ; 

void CL_ShutdownCGame( void ) {
	Key_SetCatcher( Key_GetCatcher( ) & ~KEYCATCH_CGAME );
	cls.cgameStarted = qfalse;
	if ( !cgvm ) {
		return;
	}
	VM_Call( cgvm, CG_SHUTDOWN );
	VM_Free( cgvm );
	cgvm = NULL;
}