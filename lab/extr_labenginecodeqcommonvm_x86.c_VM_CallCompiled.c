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
struct TYPE_4__ {int programStack; int entryOfs; void* codeBase; int /*<<< orphan*/ * dataBase; int /*<<< orphan*/  currentlyInterpreting; } ;
typedef  TYPE_1__ vm_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  ANNOTATE_INITIALIZED (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int MAX_VMMAIN_ARGS ; 
 int /*<<< orphan*/  OPSTACK_SIZE ; 
 int* PADP (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* currentVM ; 
 int /*<<< orphan*/  qtrue ; 

int VM_CallCompiled(vm_t *vm, int *args)
{
	byte	stack[OPSTACK_SIZE + 15];
	void	*entryPoint;
	int		programStack, stackOnEntry;
	byte	*image;
	int	*opStack;
	int		opStackOfs;
	int		arg;

	ANNOTATE_INITIALIZED(&stack, sizeof stack);

	currentVM = vm;

	// interpret the code
	vm->currentlyInterpreting = qtrue;

	// we might be called recursively, so this might not be the very top
	programStack = stackOnEntry = vm->programStack;

	// set up the stack frame 
	image = vm->dataBase;

	programStack -= ( 8 + 4 * MAX_VMMAIN_ARGS );

	for ( arg = 0; arg < MAX_VMMAIN_ARGS; arg++ )
		*(int *)&image[ programStack + 8 + arg * 4 ] = args[ arg ];

	*(int *)&image[ programStack + 4 ] = 0;	// return stack
	*(int *)&image[ programStack ] = -1;	// will terminate the loop on return

	// off we go into generated code...
	entryPoint = vm->codeBase + vm->entryOfs;
	opStack = PADP(stack, 16);
	*opStack = 0xDEADBEEF;
	opStackOfs = 0;

#ifdef _MSC_VER
  #if idx64
	opStackOfs = qvmcall64(&programStack, opStack, vm->instructionPointers, vm->dataBase);
  #else
	__asm
	{
		pushad

		mov	esi, dword ptr programStack
		mov	edi, dword ptr opStack
		mov	ebx, dword ptr opStackOfs

		call	entryPoint

		mov	dword ptr opStackOfs, ebx
		mov	dword ptr opStack, edi
		mov	dword ptr programStack, esi
		
		popad
	}
  #endif		
#elif idx64
	__asm__ volatile(
		"movq %5, %%rax\n"
		"movq %3, %%r8\n"
		"movq %4, %%r9\n"
		"push %%r15\n"
		"push %%r14\n"
		"push %%r13\n"
		"push %%r12\n"
		"callq *%%rax\n"
		"pop %%r12\n"
		"pop %%r13\n"
		"pop %%r14\n"
		"pop %%r15\n"
		: "+S" (programStack), "+D" (opStack), "+b" (opStackOfs)
		: "g" (vm->instructionPointers), "g" (vm->dataBase), "g" (entryPoint)
		: "cc", "memory", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
	);
#else
	__asm__ volatile(
		"calll *%3\n"
		: "+S" (programStack), "+D" (opStack), "+b" (opStackOfs)
		: "g" (entryPoint)
		: "cc", "memory", "%eax", "%ecx", "%edx"
	);
#endif

	if(opStackOfs != 1 || *opStack != 0xDEADBEEF)
	{
		Com_Error(ERR_DROP, "opStack corrupted in compiled code");
	}
	if(programStack != stackOnEntry - (8 + 4 * MAX_VMMAIN_ARGS))
		Com_Error(ERR_DROP, "programStack corrupted in compiled code");

	vm->programStack = stackOnEntry;

	return opStack[opStackOfs];
}