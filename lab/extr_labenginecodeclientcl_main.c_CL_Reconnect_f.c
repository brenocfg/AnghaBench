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
 int /*<<< orphan*/  Cbuf_AddText (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  cl_reconnectArgs ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,int /*<<< orphan*/ ) ; 

void CL_Reconnect_f( void ) {
	if ( !strlen( cl_reconnectArgs ) )
		return;
	Cvar_Set("ui_singlePlayerActive", "0");
	Cbuf_AddText( va("connect %s\n", cl_reconnectArgs ) );
}