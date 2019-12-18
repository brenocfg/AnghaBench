#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {intptr_t (* systemCall ) (intptr_t*) ;int /*<<< orphan*/  name; scalar_t__ dllHandle; } ;
typedef  TYPE_1__ vm_t ;
typedef  int /*<<< orphan*/  vmHeader_t ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  FS_FreeFile (int /*<<< orphan*/ *) ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VMI_NATIVE ; 
 TYPE_1__* VM_Create (char*,intptr_t (*) (intptr_t*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_Free (TYPE_1__*) ; 
 int /*<<< orphan*/ * VM_LoadQVM (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 

vm_t *VM_Restart(vm_t *vm, qboolean unpure)
{
	vmHeader_t	*header;

	// DLL's can't be restarted in place
	if ( vm->dllHandle ) {
		char	name[MAX_QPATH];
		intptr_t	(*systemCall)( intptr_t *parms );
		
		systemCall = vm->systemCall;	
		Q_strncpyz( name, vm->name, sizeof( name ) );

		VM_Free( vm );

		vm = VM_Create( name, systemCall, VMI_NATIVE );
		return vm;
	}

	// load the image
	Com_Printf("VM_Restart()\n");

	if(!(header = VM_LoadQVM(vm, qfalse, unpure)))
	{
		Com_Error(ERR_DROP, "VM_Restart failed");
		return NULL;
	}

	// free the original file
	FS_FreeFile(header);

	return vm;
}