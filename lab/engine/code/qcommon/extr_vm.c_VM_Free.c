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
struct TYPE_5__ {scalar_t__ instructionPointers; scalar_t__ dataBase; scalar_t__ codeBase; scalar_t__ dllHandle; int /*<<< orphan*/  (* destroy ) (TYPE_1__*) ;int /*<<< orphan*/  name; scalar_t__ callLevel; } ;
typedef  TYPE_1__ vm_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/  Sys_UnloadDll (scalar_t__) ; 
 int /*<<< orphan*/  Z_Free (scalar_t__) ; 
 int /*<<< orphan*/ * currentVM ; 
 int /*<<< orphan*/  forced_unload ; 
 int /*<<< orphan*/ * lastVM ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void VM_Free( vm_t *vm ) {

	if(!vm) {
		return;
	}

	if(vm->callLevel) {
		if(!forced_unload) {
			Com_Error( ERR_FATAL, "VM_Free(%s) on running vm", vm->name );
			return;
		} else {
			Com_Printf( "forcefully unloading %s vm\n", vm->name );
		}
	}

	if(vm->destroy)
		vm->destroy(vm);

	if ( vm->dllHandle ) {
		Sys_UnloadDll( vm->dllHandle );
		Com_Memset( vm, 0, sizeof( *vm ) );
	}
#if 0	// now automatically freed by hunk
	if ( vm->codeBase ) {
		Z_Free( vm->codeBase );
	}
	if ( vm->dataBase ) {
		Z_Free( vm->dataBase );
	}
	if ( vm->instructionPointers ) {
		Z_Free( vm->instructionPointers );
	}
#endif
	Com_Memset( vm, 0, sizeof( *vm ) );

	currentVM = NULL;
	lastVM = NULL;
}