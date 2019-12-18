#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_5__ {int flags; struct TYPE_5__* next; int /*<<< orphan*/  resetString; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ cvar_t ;

/* Variables and functions */
 int CVAR_INIT ; 
 int CVAR_NORESTART ; 
 int CVAR_ROM ; 
 int CVAR_USER_CREATED ; 
 int CVAR_VM_CREATED ; 
 int /*<<< orphan*/  Cvar_Set2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* Cvar_Unset (TYPE_1__*) ; 
 TYPE_1__* cvar_vars ; 
 int /*<<< orphan*/  qfalse ; 

void Cvar_Restart(qboolean unsetVM)
{
	cvar_t	*curvar;

	curvar = cvar_vars;

	while(curvar)
	{
		if((curvar->flags & CVAR_USER_CREATED) ||
			(unsetVM && (curvar->flags & CVAR_VM_CREATED)))
		{
			// throw out any variables the user/vm created
			curvar = Cvar_Unset(curvar);
			continue;
		}
		
		if(!(curvar->flags & (CVAR_ROM | CVAR_INIT | CVAR_NORESTART)))
		{
			// Just reset the rest to their default values.
			Cvar_Set2(curvar->name, curvar->resetString, qfalse);
		}
		
		curvar = curvar->next;
	}
}