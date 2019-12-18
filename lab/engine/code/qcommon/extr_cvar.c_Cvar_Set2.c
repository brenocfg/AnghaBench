#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_7__ {char* resetString; int flags; double value; int /*<<< orphan*/ * string; int /*<<< orphan*/  integer; int /*<<< orphan*/  modificationCount; void* modified; int /*<<< orphan*/ * latchedString; } ;
typedef  TYPE_1__ cvar_t ;
struct TYPE_8__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 int CVAR_CHEAT ; 
 int CVAR_INIT ; 
 int CVAR_LATCH ; 
 int CVAR_ROM ; 
 int /*<<< orphan*/  CVAR_USER_CREATED ; 
 int /*<<< orphan*/  Com_Printf (char*,char const*) ; 
 void* CopyString (char const*) ; 
 TYPE_1__* Cvar_FindVar (char const*) ; 
 TYPE_1__* Cvar_Get (char const*,char const*,int /*<<< orphan*/ ) ; 
 char* Cvar_Validate (TYPE_1__*,char const*,void*) ; 
 int /*<<< orphan*/  Cvar_ValidateString (char const*) ; 
 double FLT_MAX ; 
 int /*<<< orphan*/  Z_Free (int /*<<< orphan*/ *) ; 
 double atof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ *) ; 
 TYPE_2__* cvar_cheats ; 
 int cvar_modifiedFlags ; 
 void* qtrue ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 char* var_value ; 

cvar_t *Cvar_Set2( const char *var_name, const char *value, qboolean force ) {
	cvar_t	*var;
	double value_d;

//	Com_DPrintf( "Cvar_Set2: %s %s\n", var_name, value );

	if ( !Cvar_ValidateString( var_name ) ) {
		Com_Printf("invalid cvar name string: %s\n", var_name );
		var_name = "BADNAME";
	}

#if 0	// FIXME
	if ( value && !Cvar_ValidateString( value ) ) {
		Com_Printf("invalid cvar value string: %s\n", value );
		var_value = "BADVALUE";
	}
#endif

	var = Cvar_FindVar (var_name);
	if (!var) {
		if ( !value ) {
			return NULL;
		}
		// create it
		if ( !force ) {
			return Cvar_Get( var_name, value, CVAR_USER_CREATED );
		} else {
			return Cvar_Get (var_name, value, 0);
		}
	}

	if (!value ) {
		value = var->resetString;
	}

	value = Cvar_Validate(var, value, qtrue);

	if((var->flags & CVAR_LATCH) && var->latchedString)
	{
		if(!strcmp(value, var->string))
		{
			Z_Free(var->latchedString);
			var->latchedString = NULL;
			return var;
		}

		if(!strcmp(value, var->latchedString))
			return var;
	}
	else if(!strcmp(value, var->string))
		return var;

	// note what types of cvars have been modified (userinfo, archive, serverinfo, systeminfo)
	cvar_modifiedFlags |= var->flags;

	if (!force)
	{
		if (var->flags & CVAR_ROM)
		{
			Com_Printf ("%s is read only.\n", var_name);
			return var;
		}

		if (var->flags & CVAR_INIT)
		{
			Com_Printf ("%s is write protected.\n", var_name);
			return var;
		}

		if ((var->flags & CVAR_CHEAT) && !cvar_cheats->integer)
		{
			Com_Printf ("%s is cheat protected.\n", var_name);
			return var;
		}
		
		if (var->flags & CVAR_LATCH)
		{
			if (var->latchedString)
			{
				if (strcmp(value, var->latchedString) == 0)
					return var;
				Z_Free (var->latchedString);
			}
			else
			{
				if (strcmp(value, var->string) == 0)
					return var;
			}

			Com_Printf ("%s will be changed upon restarting.\n", var_name);
			var->latchedString = CopyString(value);
			var->modified = qtrue;
			var->modificationCount++;
			return var;
		}
	}
	else
	{
		if (var->latchedString)
		{
			Z_Free (var->latchedString);
			var->latchedString = NULL;
		}
	}

	if (!strcmp(value, var->string))
		return var;		// not changed

	var->modified = qtrue;
	var->modificationCount++;
	
	Z_Free (var->string);	// free the old value string
	
	var->string = CopyString(value);
	value_d = atof(var->string);

	// Ignore result of atof if var->string is not representable as a float.
	if (-FLT_MAX <= value_d && value_d <= FLT_MAX) {
		var->value = value_d;
	}

	var->integer = atoi (var->string);

	return var;
}