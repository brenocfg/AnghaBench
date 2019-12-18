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
 scalar_t__ LAST_COMMAND_SUB_BL_1 ; 
 scalar_t__ LAST_COMMAND_SUB_BL_2 ; 
 scalar_t__ LastCommand ; 
 int /*<<< orphan*/  STACK_POP (int) ; 
 int /*<<< orphan*/  STACK_PUSH (int) ; 
 int compiledOfs ; 
 int instruction ; 
 int /*<<< orphan*/  jlabel ; 

__attribute__((used)) static void EmitPushStack(vm_t *vm)
{
	if (!jlabel)
	{
		if(LastCommand == LAST_COMMAND_SUB_BL_1)
		{	// sub bl, 1
			compiledOfs -= 3;
			vm->instructionPointers[instruction - 1] = compiledOfs;
			return;
		}
		if(LastCommand == LAST_COMMAND_SUB_BL_2)
		{	// sub bl, 2
			compiledOfs -= 3;
			vm->instructionPointers[instruction - 1] = compiledOfs;
			STACK_POP(1);		//	sub bl, 1
			return;
		}
	}

	STACK_PUSH(1);		// add bl, 1
}