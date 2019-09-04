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
struct TYPE_5__ {int programStack; int /*<<< orphan*/  currentlyInterpreting; scalar_t__ codeBase; int /*<<< orphan*/ * dataBase; } ;
typedef  TYPE_1__ vm_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int MAX_VMMAIN_ARGS ; 
 int /*<<< orphan*/  OPSTACK_SIZE ; 
 int* PADP (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* currentVM ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

int VM_CallCompiled(vm_t *vm, int *args)
{
	byte	stack[OPSTACK_SIZE + 15];
	int	*opStack;
	int	programStack = vm->programStack;
	int	stackOnEntry = programStack;
	byte	*image = vm->dataBase;
	int	*argPointer;
	int	retVal;

	currentVM = vm;

	vm->currentlyInterpreting = qtrue;

	programStack -= ( 8 + 4 * MAX_VMMAIN_ARGS );
	argPointer = (int *)&image[ programStack + 8 ];
	memcpy( argPointer, args, 4 * MAX_VMMAIN_ARGS );
	argPointer[-1] = 0;
	argPointer[-2] = -1;


	opStack = PADP(stack, 16);
	*opStack = 0xDEADBEEF;

#if 0
	Com_Printf("r5 opStack:\t\t%p\n", opStack);
	Com_Printf("r7 codeBase:\t\t%p\n", vm->codeBase);
	Com_Printf("r8 programStack:\t0x%x\n", programStack);
	Com_Printf("r9 dataBase:\t\t%p\n", vm->dataBase);
#endif

	/* call generated code */
	{
		//int (*entry)(void *, int, void *, int);
		int (*entry)(vm_t*, int*, int*);

		entry = (void *)(vm->codeBase);
		//__asm__ volatile("bkpt");
		//retVal = entry(vm->codeBase, programStack, vm->dataBase, vm->dataMask);
		retVal = entry(vm, &programStack, opStack);
	}

	if(*opStack != 0xDEADBEEF)
	{
		Com_Error(ERR_DROP, "opStack corrupted in compiled code");
	}

	if(programStack != stackOnEntry - (8 + 4 * MAX_VMMAIN_ARGS))
		Com_Error(ERR_DROP, "programStack corrupted in compiled code");

	vm->programStack = stackOnEntry;
	vm->currentlyInterpreting = qfalse;

	return retVal;
}