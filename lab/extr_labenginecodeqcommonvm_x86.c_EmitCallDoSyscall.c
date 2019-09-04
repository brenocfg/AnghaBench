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
typedef  int /*<<< orphan*/  vm_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DoSyscall ; 
 int /*<<< orphan*/  EmitPtr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EmitRexString (int,char*) ; 
 int /*<<< orphan*/  EmitString (char*) ; 
 int compiledOfs ; 
 int /*<<< orphan*/  vm_arg ; 
 int /*<<< orphan*/  vm_opStackBase ; 
 int /*<<< orphan*/  vm_opStackOfs ; 
 int /*<<< orphan*/  vm_programStack ; 
 int /*<<< orphan*/  vm_syscallNum ; 

int EmitCallDoSyscall(vm_t *vm)
{
	// use edx register to store DoSyscall address
	EmitRexString(0x48, "BA");		// mov edx, DoSyscall
	EmitPtr(DoSyscall);

	// Push important registers to stack as we can't really make
	// any assumptions about calling conventions.
	EmitString("51");			// push ebx
	EmitString("56");			// push esi
	EmitString("57");			// push edi
#if idx64
	EmitRexString(0x41, "50");		// push r8
	EmitRexString(0x41, "51");		// push r9
#endif

	// write arguments to global vars
	// syscall number
	EmitString("A3");			// mov [0x12345678], eax
	EmitPtr(&vm_syscallNum);
	// vm_programStack value
	EmitString("89 F0");			// mov eax, esi
	EmitString("A3");			// mov [0x12345678], eax
	EmitPtr(&vm_programStack);
	// vm_opStackOfs 
	EmitString("88 D8");			// mov al, bl
	EmitString("A2");			// mov [0x12345678], al
	EmitPtr(&vm_opStackOfs);
	// vm_opStackBase
	EmitRexString(0x48, "89 F8");		// mov eax, edi
	EmitRexString(0x48, "A3");		// mov [0x12345678], eax
	EmitPtr(&vm_opStackBase);
	// vm_arg
	EmitString("89 C8");			// mov eax, ecx
	EmitString("A3");			// mov [0x12345678], eax
	EmitPtr(&vm_arg);
	
	// align the stack pointer to a 16-byte-boundary
	EmitString("55");			// push ebp
	EmitRexString(0x48, "89 E5");		// mov ebp, esp
	EmitRexString(0x48, "83 E4 F0");	// and esp, 0xFFFFFFF0
			
	// call the syscall wrapper function DoSyscall()

	EmitString("FF D2");			// call edx

	// reset the stack pointer to its previous value
	EmitRexString(0x48, "89 EC");		// mov esp, ebp
	EmitString("5D");			// pop ebp

#if idx64
	EmitRexString(0x41, "59");		// pop r9
	EmitRexString(0x41, "58");		// pop r8
#endif
	EmitString("5F");			// pop edi
	EmitString("5E");			// pop esi
	EmitString("59");			// pop ebx

	EmitString("C3");			// ret

	return compiledOfs;
}