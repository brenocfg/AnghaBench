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
 int CVAR_NONEXISTENT ; 
 int CVAR_PROTECTED ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int Cvar_Flags (char const*) ; 
 int /*<<< orphan*/  Cvar_Set (char const*,char const*) ; 
 int /*<<< orphan*/  ERR_DROP ; 

void Cvar_SetSafe( const char *var_name, const char *value )
{
	int flags = Cvar_Flags( var_name );

	if((flags != CVAR_NONEXISTENT) && (flags & CVAR_PROTECTED))
	{
		if( value )
			Com_Error( ERR_DROP, "Restricted source tried to set "
				"\"%s\" to \"%s\"", var_name, value );
		else
			Com_Error( ERR_DROP, "Restricted source tried to "
				"modify \"%s\"", var_name );
		return;
	}
	Cvar_Set( var_name, value );
}