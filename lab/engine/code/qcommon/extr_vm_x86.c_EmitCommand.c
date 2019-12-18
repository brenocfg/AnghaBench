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
typedef  int ELastCommand ;

/* Variables and functions */
 int /*<<< orphan*/  EmitString (char*) ; 
#define  LAST_COMMAND_MOV_STACK_EAX 130 
#define  LAST_COMMAND_SUB_BL_1 129 
#define  LAST_COMMAND_SUB_BL_2 128 
 int LastCommand ; 
 int /*<<< orphan*/  STACK_POP (int) ; 

__attribute__((used)) static void EmitCommand(ELastCommand command)
{
	switch(command)
	{
		case LAST_COMMAND_MOV_STACK_EAX:
			EmitString("89 04 9F");		// mov dword ptr [edi + ebx * 4], eax
			break;

		case LAST_COMMAND_SUB_BL_1:
			STACK_POP(1);			// sub bl, 1
			break;

		case LAST_COMMAND_SUB_BL_2:
			STACK_POP(2);			// sub bl, 2
			break;
		default:
			break;
	}
	LastCommand = command;
}