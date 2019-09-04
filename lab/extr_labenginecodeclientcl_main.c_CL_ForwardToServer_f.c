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
struct TYPE_2__ {scalar_t__ state; scalar_t__ demoplaying; } ;

/* Variables and functions */
 scalar_t__ CA_ACTIVE ; 
 int /*<<< orphan*/  CL_AddReliableCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_Args () ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 TYPE_1__ clc ; 
 int /*<<< orphan*/  qfalse ; 

void CL_ForwardToServer_f( void ) {
	if ( clc.state != CA_ACTIVE || clc.demoplaying ) {
		Com_Printf ("Not connected to a server.\n");
		return;
	}
	
	// don't forward the first argument
	if ( Cmd_Argc() > 1 ) {
		CL_AddReliableCommand(Cmd_Args(), qfalse);
	}
}