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
struct TYPE_3__ {int* instructionPointers; } ;
typedef  TYPE_1__ vm_t ;

/* Variables and functions */
 int /*<<< orphan*/  Emit4 (int) ; 
 int /*<<< orphan*/  EmitString (char*) ; 
 scalar_t__ LAST_COMMAND_MOV_STACK_EAX ; 
 scalar_t__ LastCommand ; 
 scalar_t__ OP_CONST ; 
 scalar_t__ OP_DIVI ; 
 scalar_t__ OP_DIVU ; 
 scalar_t__ OP_MULI ; 
 scalar_t__ OP_MULU ; 
 scalar_t__ OP_STORE1 ; 
 scalar_t__ OP_STORE2 ; 
 scalar_t__ OP_STORE4 ; 
 int* buf ; 
 int compiledOfs ; 
 int instruction ; 
 int /*<<< orphan*/  jlabel ; 
 int lastConst ; 
 scalar_t__ pop1 ; 

__attribute__((used)) static void EmitMovEAXStack(vm_t *vm, int andit)
{
	if(!jlabel)
	{
		if(LastCommand == LAST_COMMAND_MOV_STACK_EAX) 
		{	// mov [edi + ebx * 4], eax
			compiledOfs -= 3;
			vm->instructionPointers[instruction - 1] = compiledOfs;
		}
		else if(pop1 == OP_CONST && buf[compiledOfs-7] == 0xC7 && buf[compiledOfs-6] == 0x04 && buf[compiledOfs - 5] == 0x9F)
		{	// mov [edi + ebx * 4], 0x12345678
			compiledOfs -= 7;
			vm->instructionPointers[instruction - 1] = compiledOfs;
			EmitString("B8");	// mov	eax, 0x12345678

			if(andit)
				Emit4(lastConst & andit);
			else
				Emit4(lastConst);
			
			return;
		}
		else if(pop1 != OP_DIVI && pop1 != OP_DIVU && pop1 != OP_MULI && pop1 != OP_MULU &&
			pop1 != OP_STORE4 && pop1 != OP_STORE2 && pop1 != OP_STORE1)
		{	
			EmitString("8B 04 9F");	// mov eax, dword ptr [edi + ebx * 4]
		}
	}
	else
		EmitString("8B 04 9F");		// mov eax, dword ptr [edi + ebx * 4]

	if(andit)
	{
		EmitString("25");		// and eax, 0x12345678
		Emit4(andit);
	}
}