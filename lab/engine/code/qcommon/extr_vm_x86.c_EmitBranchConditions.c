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
 int /*<<< orphan*/  Constant4 () ; 
 int /*<<< orphan*/  EmitJumpIns (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
#define  OP_EQ 137 
#define  OP_GEI 136 
#define  OP_GEU 135 
#define  OP_GTI 134 
#define  OP_GTU 133 
#define  OP_LEI 132 
#define  OP_LEU 131 
#define  OP_LTI 130 
#define  OP_LTU 129 
#define  OP_NE 128 

void EmitBranchConditions(vm_t *vm, int op)
{
	switch(op)
	{
	case OP_EQ:
		EmitJumpIns(vm, "0F 84", Constant4());	// je 0x12345678
	break;
	case OP_NE:
		EmitJumpIns(vm, "0F 85", Constant4());	// jne 0x12345678
	break;
	case OP_LTI:
		EmitJumpIns(vm, "0F 8C", Constant4());	// jl 0x12345678
	break;
	case OP_LEI:
		EmitJumpIns(vm, "0F 8E", Constant4());	// jle 0x12345678
	break;
	case OP_GTI:
		EmitJumpIns(vm, "0F 8F", Constant4());	// jg 0x12345678
	break;
	case OP_GEI:
		EmitJumpIns(vm, "0F 8D", Constant4());	// jge 0x12345678
	break;
	case OP_LTU:
		EmitJumpIns(vm, "0F 82", Constant4());	// jb 0x12345678
	break;
	case OP_LEU:
		EmitJumpIns(vm, "0F 86", Constant4());	// jbe 0x12345678
	break;
	case OP_GTU:
		EmitJumpIns(vm, "0F 87", Constant4());	// ja 0x12345678
	break;
	case OP_GEU:
		EmitJumpIns(vm, "0F 83", Constant4());	// jae 0x12345678
	break;
	}
}