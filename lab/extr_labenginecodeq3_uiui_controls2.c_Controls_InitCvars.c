#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* value; int /*<<< orphan*/  name; void* defaultvalue; } ;
typedef  TYPE_1__ configcvar_t ;

/* Variables and functions */
 TYPE_1__* g_configcvars ; 
 int /*<<< orphan*/  trap_Cvar_Reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (int /*<<< orphan*/ ,void*) ; 
 void* trap_Cvar_VariableValue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Controls_InitCvars( void )
{
	int				i;
	configcvar_t*	cvarptr;

	cvarptr = g_configcvars;
	for (i=0; ;i++,cvarptr++)
	{
		if (!cvarptr->name)
			break;

		// get current value
		cvarptr->value = trap_Cvar_VariableValue( cvarptr->name );

		// get default value
		trap_Cvar_Reset( cvarptr->name );
		cvarptr->defaultvalue = trap_Cvar_VariableValue( cvarptr->name );

		// restore current value
		trap_Cvar_SetValue( cvarptr->name, cvarptr->value );
	}
}