#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  CG_CONSOLE_COMMAND ; 
 int /*<<< orphan*/  VM_Call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgvm ; 
 int /*<<< orphan*/  qfalse ; 

qboolean CL_GameCommand( void ) {
	if ( !cgvm ) {
		return qfalse;
	}

	return VM_Call( cgvm, CG_CONSOLE_COMMAND );
}