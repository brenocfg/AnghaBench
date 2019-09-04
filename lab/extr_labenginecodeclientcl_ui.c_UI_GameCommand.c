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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_2__ {int /*<<< orphan*/  realtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  UI_CONSOLE_COMMAND ; 
 int /*<<< orphan*/  VM_Call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ cls ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  uivm ; 

qboolean UI_GameCommand( void ) {
	if ( !uivm ) {
		return qfalse;
	}

	return VM_Call( uivm, UI_CONSOLE_COMMAND, cls.realtime );
}