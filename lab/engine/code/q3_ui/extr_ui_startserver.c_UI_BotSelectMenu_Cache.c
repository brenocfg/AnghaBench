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
 int /*<<< orphan*/  BOTSELECT_ACCEPT0 ; 
 int /*<<< orphan*/  BOTSELECT_ACCEPT1 ; 
 int /*<<< orphan*/  BOTSELECT_ARROWS ; 
 int /*<<< orphan*/  BOTSELECT_ARROWSL ; 
 int /*<<< orphan*/  BOTSELECT_ARROWSR ; 
 int /*<<< orphan*/  BOTSELECT_BACK0 ; 
 int /*<<< orphan*/  BOTSELECT_BACK1 ; 
 int /*<<< orphan*/  BOTSELECT_SELECT ; 
 int /*<<< orphan*/  BOTSELECT_SELECTED ; 
 int /*<<< orphan*/  trap_R_RegisterShaderNoMip (int /*<<< orphan*/ ) ; 

void UI_BotSelectMenu_Cache( void ) {
	trap_R_RegisterShaderNoMip( BOTSELECT_BACK0 );
	trap_R_RegisterShaderNoMip( BOTSELECT_BACK1 );
	trap_R_RegisterShaderNoMip( BOTSELECT_ACCEPT0 );
	trap_R_RegisterShaderNoMip( BOTSELECT_ACCEPT1 );
	trap_R_RegisterShaderNoMip( BOTSELECT_SELECT );
	trap_R_RegisterShaderNoMip( BOTSELECT_SELECTED );
	trap_R_RegisterShaderNoMip( BOTSELECT_ARROWS );
	trap_R_RegisterShaderNoMip( BOTSELECT_ARROWSL );
	trap_R_RegisterShaderNoMip( BOTSELECT_ARROWSR );
}