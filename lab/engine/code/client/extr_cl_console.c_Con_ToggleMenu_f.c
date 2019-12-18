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

/* Variables and functions */
 int /*<<< orphan*/  CL_KeyEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  K_ESCAPE ; 
 int /*<<< orphan*/  Sys_Milliseconds () ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

void Con_ToggleMenu_f( void ) {
	CL_KeyEvent( K_ESCAPE, qtrue, Sys_Milliseconds() );
	CL_KeyEvent( K_ESCAPE, qfalse, Sys_Milliseconds() );
}