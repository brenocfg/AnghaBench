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
struct TYPE_5__ {intptr_t instructionCount; scalar_t__ instructionPointers; } ;
typedef  TYPE_1__ vm_t ;

/* Variables and functions */
 int /*<<< orphan*/  Emit4 (intptr_t) ; 
 int /*<<< orphan*/  EmitCallErrJump (TYPE_1__*,int) ; 
 int /*<<< orphan*/  EmitCallRel (TYPE_1__*,int) ; 
 int /*<<< orphan*/  EmitRexString (int,char*) ; 
 int /*<<< orphan*/  EmitString (char*) ; 
 int /*<<< orphan*/  SET_JMPOFS (int) ; 
 int /*<<< orphan*/  STACK_POP (int) ; 
 int /*<<< orphan*/  STACK_PUSH (int) ; 
 int compiledOfs ; 

int EmitCallProcedure(vm_t *vm, int sysCallOfs)
{
	int jmpSystemCall, jmpBadAddr;
	int retval;

	EmitString("8B 04 9F");		// mov eax, dword ptr [edi + ebx * 4]
	STACK_POP(1);			// sub bl, 1
	EmitString("85 C0");		// test eax, eax

	// Jump to syscall code, 1 byte offset should suffice
	EmitString("7C");		// jl systemCall
	jmpSystemCall = compiledOfs++;
		
	/************ Call inside VM ************/
	
	EmitString("81 F8");		// cmp eax, vm->instructionCount
	Emit4(vm->instructionCount);
		
	// Error jump if invalid jump target
	EmitString("73");		// jae badAddr
	jmpBadAddr = compiledOfs++;

#if idx64
	EmitRexString(0x49, "FF 14 C0");	// call qword ptr [r8 + eax * 8]
#else
	EmitString("FF 14 85");			// call dword ptr [vm->instructionPointers + eax * 4]
	Emit4((intptr_t) vm->instructionPointers);
#endif
	EmitString("8B 04 9F");			// mov eax, dword ptr [edi + ebx * 4]
	EmitString("C3");			// ret
		
	// badAddr:
	SET_JMPOFS(jmpBadAddr);
	EmitCallErrJump(vm, sysCallOfs);

	/************ System Call ************/
	
	// systemCall:
	SET_JMPOFS(jmpSystemCall);
	retval = compiledOfs;

	EmitCallRel(vm, sysCallOfs);

	// have opStack reg point at return value
	STACK_PUSH(1);			// add bl, 1
	EmitString("C3");		// ret

	return retval;
}