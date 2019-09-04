#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int codeLength; int* instructionPointers; int instructionCount; scalar_t__ codeBase; } ;
typedef  TYPE_1__ vm_t ;
struct TYPE_6__ {int codeOffset; int instructionCount; int codeLength; } ;
typedef  TYPE_2__ vmHeader_t ;
typedef  scalar_t__ byte ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 scalar_t__ Hunk_Alloc (int,int /*<<< orphan*/ ) ; 
#define  OP_ARG 149 
#define  OP_BLOCK_COPY 148 
#define  OP_CONST 147 
#define  OP_ENTER 146 
#define  OP_EQ 145 
#define  OP_EQF 144 
#define  OP_GEF 143 
#define  OP_GEI 142 
#define  OP_GEU 141 
#define  OP_GTF 140 
#define  OP_GTI 139 
#define  OP_GTU 138 
#define  OP_LEAVE 137 
#define  OP_LEF 136 
#define  OP_LEI 135 
#define  OP_LEU 134 
#define  OP_LOCAL 133 
#define  OP_LTF 132 
#define  OP_LTI 131 
#define  OP_LTU 130 
#define  OP_NE 129 
#define  OP_NEF 128 
 int /*<<< orphan*/  h_high ; 
 int loadWord (scalar_t__*) ; 

void VM_PrepareInterpreter( vm_t *vm, vmHeader_t *header ) {
	int		op;
	int		byte_pc;
	int		int_pc;
	byte	*code;
	int		instruction;
	int		*codeBase;

	vm->codeBase = Hunk_Alloc( vm->codeLength*4, h_high );			// we're now int aligned
//	memcpy( vm->codeBase, (byte *)header + header->codeOffset, vm->codeLength );

	// we don't need to translate the instructions, but we still need
	// to find each instructions starting point for jumps
	int_pc = byte_pc = 0;
	instruction = 0;
	code = (byte *)header + header->codeOffset;
	codeBase = (int *)vm->codeBase;

	// Copy and expand instructions to words while building instruction table
	while ( instruction < header->instructionCount ) {
		vm->instructionPointers[ instruction ] = int_pc;
		instruction++;

		op = (int)code[ byte_pc ];
		codeBase[int_pc] = op;
		if(byte_pc > header->codeLength)
			Com_Error(ERR_DROP, "VM_PrepareInterpreter: pc > header->codeLength");

		byte_pc++;
		int_pc++;

		// these are the only opcodes that aren't a single byte
		switch ( op ) {
		case OP_ENTER:
		case OP_CONST:
		case OP_LOCAL:
		case OP_LEAVE:
		case OP_EQ:
		case OP_NE:
		case OP_LTI:
		case OP_LEI:
		case OP_GTI:
		case OP_GEI:
		case OP_LTU:
		case OP_LEU:
		case OP_GTU:
		case OP_GEU:
		case OP_EQF:
		case OP_NEF:
		case OP_LTF:
		case OP_LEF:
		case OP_GTF:
		case OP_GEF:
		case OP_BLOCK_COPY:
			codeBase[int_pc] = loadWord(&code[byte_pc]);
			byte_pc += 4;
			int_pc++;
			break;
		case OP_ARG:
			codeBase[int_pc] = (int)code[byte_pc];
			byte_pc++;
			int_pc++;
			break;
		default:
			break;
		}

	}
	int_pc = 0;
	instruction = 0;
	
	// Now that the code has been expanded to int-sized opcodes, we'll translate instruction index
	//into an index into codeBase[], which contains opcodes and operands.
	while ( instruction < header->instructionCount ) {
		op = codeBase[ int_pc ];
		instruction++;
		int_pc++;
		
		switch ( op ) {
		// These ops need to translate addresses in jumps from instruction index to int index
		case OP_EQ:
		case OP_NE:
		case OP_LTI:
		case OP_LEI:
		case OP_GTI:
		case OP_GEI:
		case OP_LTU:
		case OP_LEU:
		case OP_GTU:
		case OP_GEU:
		case OP_EQF:
		case OP_NEF:
		case OP_LTF:
		case OP_LEF:
		case OP_GTF:
		case OP_GEF:
			if(codeBase[int_pc] < 0 || codeBase[int_pc] > vm->instructionCount)
				Com_Error(ERR_DROP, "VM_PrepareInterpreter: Jump to invalid instruction number");

			// codeBase[pc] is the instruction index. Convert that into an offset into
			//the int-aligned codeBase[] by the lookup table.
			codeBase[int_pc] = vm->instructionPointers[codeBase[int_pc]];
			int_pc++;
			break;

		// These opcodes have an operand that isn't an instruction index
		case OP_ENTER:
		case OP_CONST:
		case OP_LOCAL:
		case OP_LEAVE:
		case OP_BLOCK_COPY:
		case OP_ARG:
			int_pc++;
			break;

		default:
			break;
		}

	}
}