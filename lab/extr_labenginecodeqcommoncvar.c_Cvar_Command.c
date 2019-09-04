#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ cvar_t ;

/* Variables and functions */
 int Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_Args () ; 
 int /*<<< orphan*/  Cmd_Argv (int /*<<< orphan*/ ) ; 
 TYPE_1__* Cvar_FindVar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_Print (TYPE_1__*) ; 
 int /*<<< orphan*/  Cvar_Set2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean Cvar_Command( void ) {
	cvar_t	*v;

	// check variables
	v = Cvar_FindVar (Cmd_Argv(0));
	if (!v) {
		return qfalse;
	}

	// perform a variable print or set
	if ( Cmd_Argc() == 1 ) {
		Cvar_Print( v );
		return qtrue;
	}

	// set the value if forcing isn't required
	Cvar_Set2 (v->name, Cmd_Args(), qfalse);
	return qtrue;
}