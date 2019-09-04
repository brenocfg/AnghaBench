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
struct TYPE_3__ {int programStack; int* dataBase; int dataMask; int (* systemCall ) (intptr_t*) ;unsigned int instructionCount; int* instructionPointers; unsigned int codeLength; int /*<<< orphan*/  currentlyInterpreting; int /*<<< orphan*/  breakCount; scalar_t__ codeBase; } ;
typedef  TYPE_1__ vm_t ;
typedef  size_t uint8_t ;
typedef  int byte ;

/* Variables and functions */
 int ARRAY_LEN (intptr_t*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int MAX_VMMAIN_ARGS ; 
 int MAX_VMSYSCALL_ARGS ; 
 int /*<<< orphan*/  OPSTACK_SIZE ; 
#define  OP_ADD 185 
#define  OP_ADDF 184 
#define  OP_ARG 183 
#define  OP_BAND 182 
#define  OP_BCOM 181 
#define  OP_BLOCK_COPY 180 
#define  OP_BOR 179 
#define  OP_BREAK 178 
#define  OP_BXOR 177 
#define  OP_CALL 176 
#define  OP_CONST 175 
#define  OP_CVFI 174 
#define  OP_CVIF 173 
#define  OP_DIVF 172 
#define  OP_DIVI 171 
#define  OP_DIVU 170 
#define  OP_ENTER 169 
#define  OP_EQ 168 
#define  OP_EQF 167 
#define  OP_GEF 166 
#define  OP_GEI 165 
#define  OP_GEU 164 
#define  OP_GTF 163 
#define  OP_GTI 162 
#define  OP_GTU 161 
#define  OP_JUMP 160 
#define  OP_LEAVE 159 
#define  OP_LEF 158 
#define  OP_LEI 157 
#define  OP_LEU 156 
#define  OP_LOAD1 155 
#define  OP_LOAD2 154 
#define  OP_LOAD4 153 
#define  OP_LOCAL 152 
#define  OP_LSH 151 
#define  OP_LTF 150 
#define  OP_LTI 149 
#define  OP_LTU 148 
#define  OP_MODI 147 
#define  OP_MODU 146 
#define  OP_MULF 145 
#define  OP_MULI 144 
#define  OP_MULU 143 
#define  OP_NE 142 
#define  OP_NEF 141 
#define  OP_NEGF 140 
#define  OP_NEGI 139 
#define  OP_POP 138 
#define  OP_PUSH 137 
#define  OP_RSHI 136 
#define  OP_RSHU 135 
#define  OP_SEX16 134 
#define  OP_SEX8 133 
#define  OP_STORE1 132 
#define  OP_STORE2 131 
#define  OP_STORE4 130 
#define  OP_SUB 129 
#define  OP_SUBF 128 
 int* PADP (int*,int) ; 
 int Q_ftol (float) ; 
 int /*<<< orphan*/  VM_BlockCopy (int,int,int) ; 
 int /*<<< orphan*/  VM_Debug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int stub1 (intptr_t*) ; 
 int stub2 (intptr_t*) ; 

int	VM_CallInterpreted( vm_t *vm, int *args ) {
	byte		stack[OPSTACK_SIZE + 15];
	int		*opStack;
	uint8_t 	opStackOfs;
	int		programCounter;
	int		programStack;
	int		stackOnEntry;
	byte	*image;
	int		*codeImage;
	int		v1;
	int		dataMask;
	int		arg;
#ifdef DEBUG_VM
	vmSymbol_t	*profileSymbol;
#endif

	// interpret the code
	vm->currentlyInterpreting = qtrue;

	// we might be called recursively, so this might not be the very top
	programStack = stackOnEntry = vm->programStack;

#ifdef DEBUG_VM
	profileSymbol = VM_ValueToFunctionSymbol( vm, 0 );
	// uncomment this for debugging breakpoints
	vm->breakFunction = 0;
#endif
	// set up the stack frame 

	image = vm->dataBase;
	codeImage = (int *)vm->codeBase;
	dataMask = vm->dataMask;
	
	programCounter = 0;

	programStack -= ( 8 + 4 * MAX_VMMAIN_ARGS );

	for ( arg = 0; arg < MAX_VMMAIN_ARGS; arg++ )
		*(int *)&image[ programStack + 8 + arg * 4 ] = args[ arg ];

	*(int *)&image[ programStack + 4 ] = 0;	// return stack
	*(int *)&image[ programStack ] = -1;	// will terminate the loop on return

	VM_Debug(0);

	// leave a free spot at start of stack so
	// that as long as opStack is valid, opStack-1 will
	// not corrupt anything
	opStack = PADP(stack, 16);
	*opStack = 0xDEADBEEF;
	opStackOfs = 0;

//	vm_debugLevel=2;
	// main interpreter loop, will exit when a LEAVE instruction
	// grabs the -1 program counter

#define r2 codeImage[programCounter]

	while ( 1 ) {
		int		opcode,	r0, r1;
//		unsigned int	r2;

nextInstruction:
		r0 = opStack[opStackOfs];
		r1 = opStack[(uint8_t) (opStackOfs - 1)];
nextInstruction2:
#ifdef DEBUG_VM
		if ( (unsigned)programCounter >= vm->codeLength ) {
			Com_Error( ERR_DROP, "VM pc out of range" );
			return 0;
		}

		if ( programStack <= vm->stackBottom ) {
			Com_Error( ERR_DROP, "VM stack overflow" );
			return 0;
		}

		if ( programStack & 3 ) {
			Com_Error( ERR_DROP, "VM program stack misaligned" );
			return 0;
		}

		if ( vm_debugLevel > 1 ) {
			Com_Printf( "%s %s\n", DEBUGSTR, opnames[opcode] );
		}
		profileSymbol->profileCount++;
#endif
		opcode = codeImage[ programCounter++ ];

		switch ( opcode ) {
#ifdef DEBUG_VM
		default:
			Com_Error( ERR_DROP, "Bad VM instruction" );  // this should be scanned on load!
			return 0;
#endif
		case OP_BREAK:
			vm->breakCount++;
			goto nextInstruction2;
		case OP_CONST:
			opStackOfs++;
			r1 = r0;
			r0 = opStack[opStackOfs] = r2;
			
			programCounter += 1;
			goto nextInstruction2;
		case OP_LOCAL:
			opStackOfs++;
			r1 = r0;
			r0 = opStack[opStackOfs] = r2+programStack;

			programCounter += 1;
			goto nextInstruction2;

		case OP_LOAD4:
#ifdef DEBUG_VM
			if(opStack[opStackOfs] & 3)
			{
				Com_Error( ERR_DROP, "OP_LOAD4 misaligned" );
				return 0;
			}
#endif
			r0 = opStack[opStackOfs] = *(int *) &image[ r0 & dataMask ];
			goto nextInstruction2;
		case OP_LOAD2:
			r0 = opStack[opStackOfs] = *(unsigned short *)&image[ r0 & dataMask ];
			goto nextInstruction2;
		case OP_LOAD1:
			r0 = opStack[opStackOfs] = image[ r0 & dataMask ];
			goto nextInstruction2;

		case OP_STORE4:
			*(int *)&image[ r1 & dataMask ] = r0;
			opStackOfs -= 2;
			goto nextInstruction;
		case OP_STORE2:
			*(short *)&image[ r1 & dataMask ] = r0;
			opStackOfs -= 2;
			goto nextInstruction;
		case OP_STORE1:
			image[ r1 & dataMask ] = r0;
			opStackOfs -= 2;
			goto nextInstruction;

		case OP_ARG:
			// single byte offset from programStack
			*(int *)&image[ (codeImage[programCounter] + programStack) & dataMask ] = r0;
			opStackOfs--;
			programCounter += 1;
			goto nextInstruction;

		case OP_BLOCK_COPY:
			VM_BlockCopy(r1, r0, r2);
			programCounter += 1;
			opStackOfs -= 2;
			goto nextInstruction;

		case OP_CALL:
			// save current program counter
			*(int *)&image[ programStack ] = programCounter;
			
			// jump to the location on the stack
			programCounter = r0;
			opStackOfs--;
			if ( programCounter < 0 ) {
				// system call
				int		r;
//				int		temp;
#ifdef DEBUG_VM
				int		stomped;

				if ( vm_debugLevel ) {
					Com_Printf( "%s---> systemcall(%i)\n", DEBUGSTR, -1 - programCounter );
				}
#endif
				// save the stack to allow recursive VM entry
//				temp = vm->callLevel;
				vm->programStack = programStack - 4;
#ifdef DEBUG_VM
				stomped = *(int *)&image[ programStack + 4 ];
#endif
				*(int *)&image[ programStack + 4 ] = -1 - programCounter;

//VM_LogSyscalls( (int *)&image[ programStack + 4 ] );
				{
					// the vm has ints on the stack, we expect
					// pointers so we might have to convert it
					if (sizeof(intptr_t) != sizeof(int)) {
						intptr_t argarr[ MAX_VMSYSCALL_ARGS ];
						int *imagePtr = (int *)&image[ programStack ];
						int i;
						for (i = 0; i < ARRAY_LEN(argarr); ++i) {
							argarr[i] = *(++imagePtr);
						}
						r = vm->systemCall( argarr );
					} else {
						intptr_t* argptr = (intptr_t *)&image[ programStack + 4 ];
						r = vm->systemCall( argptr );
					}
				}

#ifdef DEBUG_VM
				// this is just our stack frame pointer, only needed
				// for debugging
				*(int *)&image[ programStack + 4 ] = stomped;
#endif

				// save return value
				opStackOfs++;
				opStack[opStackOfs] = r;
				programCounter = *(int *)&image[ programStack ];
//				vm->callLevel = temp;
#ifdef DEBUG_VM
				if ( vm_debugLevel ) {
					Com_Printf( "%s<--- %s\n", DEBUGSTR, VM_ValueToSymbol( vm, programCounter ) );
				}
#endif
			} else if ( (unsigned)programCounter >= vm->instructionCount ) {
				Com_Error( ERR_DROP, "VM program counter out of range in OP_CALL" );
				return 0;
			} else {
				programCounter = vm->instructionPointers[ programCounter ];
			}
			goto nextInstruction;

		// push and pop are only needed for discarded or bad function return values
		case OP_PUSH:
			opStackOfs++;
			goto nextInstruction;
		case OP_POP:
			opStackOfs--;
			goto nextInstruction;

		case OP_ENTER:
#ifdef DEBUG_VM
			profileSymbol = VM_ValueToFunctionSymbol( vm, programCounter );
#endif
			// get size of stack frame
			v1 = r2;

			programCounter += 1;
			programStack -= v1;
#ifdef DEBUG_VM
			// save old stack frame for debugging traces
			*(int *)&image[programStack+4] = programStack + v1;
			if ( vm_debugLevel ) {
				Com_Printf( "%s---> %s\n", DEBUGSTR, VM_ValueToSymbol( vm, programCounter - 5 ) );
				if ( vm->breakFunction && programCounter - 5 == vm->breakFunction ) {
					// this is to allow setting breakpoints here in the debugger
					vm->breakCount++;
//					vm_debugLevel = 2;
//					VM_StackTrace( vm, programCounter, programStack );
				}
//				vm->callLevel++;
			}
#endif
			goto nextInstruction;
		case OP_LEAVE:
			// remove our stack frame
			v1 = r2;

			programStack += v1;

			// grab the saved program counter
			programCounter = *(int *)&image[ programStack ];
#ifdef DEBUG_VM
			profileSymbol = VM_ValueToFunctionSymbol( vm, programCounter );
			if ( vm_debugLevel ) {
//				vm->callLevel--;
				Com_Printf( "%s<--- %s\n", DEBUGSTR, VM_ValueToSymbol( vm, programCounter ) );
			}
#endif
			// check for leaving the VM
			if ( programCounter == -1 ) {
				goto done;
			} else if ( (unsigned)programCounter >= vm->codeLength ) {
				Com_Error( ERR_DROP, "VM program counter out of range in OP_LEAVE" );
				return 0;
			}
			goto nextInstruction;

		/*
		===================================================================
		BRANCHES
		===================================================================
		*/

		case OP_JUMP:
			if ( (unsigned)r0 >= vm->instructionCount )
			{
				Com_Error( ERR_DROP, "VM program counter out of range in OP_JUMP" );
				return 0;
			}

			programCounter = vm->instructionPointers[ r0 ];

			opStackOfs--;
			goto nextInstruction;

		case OP_EQ:
			opStackOfs -= 2;
			if ( r1 == r0 ) {
				programCounter = r2;	//vm->instructionPointers[r2];
				goto nextInstruction;
			} else {
				programCounter += 1;
				goto nextInstruction;
			}

		case OP_NE:
			opStackOfs -= 2;
			if ( r1 != r0 ) {
				programCounter = r2;	//vm->instructionPointers[r2];
				goto nextInstruction;
			} else {
				programCounter += 1;
				goto nextInstruction;
			}

		case OP_LTI:
			opStackOfs -= 2;
			if ( r1 < r0 ) {
				programCounter = r2;	//vm->instructionPointers[r2];
				goto nextInstruction;
			} else {
				programCounter += 1;
				goto nextInstruction;
			}

		case OP_LEI:
			opStackOfs -= 2;
			if ( r1 <= r0 ) {
				programCounter = r2;	//vm->instructionPointers[r2];
				goto nextInstruction;
			} else {
				programCounter += 1;
				goto nextInstruction;
			}

		case OP_GTI:
			opStackOfs -= 2;
			if ( r1 > r0 ) {
				programCounter = r2;	//vm->instructionPointers[r2];
				goto nextInstruction;
			} else {
				programCounter += 1;
				goto nextInstruction;
			}

		case OP_GEI:
			opStackOfs -= 2;
			if ( r1 >= r0 ) {
				programCounter = r2;	//vm->instructionPointers[r2];
				goto nextInstruction;
			} else {
				programCounter += 1;
				goto nextInstruction;
			}

		case OP_LTU:
			opStackOfs -= 2;
			if ( ((unsigned)r1) < ((unsigned)r0) ) {
				programCounter = r2;	//vm->instructionPointers[r2];
				goto nextInstruction;
			} else {
				programCounter += 1;
				goto nextInstruction;
			}

		case OP_LEU:
			opStackOfs -= 2;
			if ( ((unsigned)r1) <= ((unsigned)r0) ) {
				programCounter = r2;	//vm->instructionPointers[r2];
				goto nextInstruction;
			} else {
				programCounter += 1;
				goto nextInstruction;
			}

		case OP_GTU:
			opStackOfs -= 2;
			if ( ((unsigned)r1) > ((unsigned)r0) ) {
				programCounter = r2;	//vm->instructionPointers[r2];
				goto nextInstruction;
			} else {
				programCounter += 1;
				goto nextInstruction;
			}

		case OP_GEU:
			opStackOfs -= 2;
			if ( ((unsigned)r1) >= ((unsigned)r0) ) {
				programCounter = r2;	//vm->instructionPointers[r2];
				goto nextInstruction;
			} else {
				programCounter += 1;
				goto nextInstruction;
			}

		case OP_EQF:
			opStackOfs -= 2;
			
			if(((float *) opStack)[(uint8_t) (opStackOfs + 1)] == ((float *) opStack)[(uint8_t) (opStackOfs + 2)])
			{
				programCounter = r2;	//vm->instructionPointers[r2];
				goto nextInstruction;
			} else {
				programCounter += 1;
				goto nextInstruction;
			}

		case OP_NEF:
			opStackOfs -= 2;

			if(((float *) opStack)[(uint8_t) (opStackOfs + 1)] != ((float *) opStack)[(uint8_t) (opStackOfs + 2)])
			{
				programCounter = r2;	//vm->instructionPointers[r2];
				goto nextInstruction;
			} else {
				programCounter += 1;
				goto nextInstruction;
			}

		case OP_LTF:
			opStackOfs -= 2;

			if(((float *) opStack)[(uint8_t) (opStackOfs + 1)] < ((float *) opStack)[(uint8_t) (opStackOfs + 2)])
			{
				programCounter = r2;	//vm->instructionPointers[r2];
				goto nextInstruction;
			} else {
				programCounter += 1;
				goto nextInstruction;
			}

		case OP_LEF:
			opStackOfs -= 2;

			if(((float *) opStack)[(uint8_t) ((uint8_t) (opStackOfs + 1))] <= ((float *) opStack)[(uint8_t) ((uint8_t) (opStackOfs + 2))])
			{
				programCounter = r2;	//vm->instructionPointers[r2];
				goto nextInstruction;
			} else {
				programCounter += 1;
				goto nextInstruction;
			}

		case OP_GTF:
			opStackOfs -= 2;

			if(((float *) opStack)[(uint8_t) (opStackOfs + 1)] > ((float *) opStack)[(uint8_t) (opStackOfs + 2)])
			{
				programCounter = r2;	//vm->instructionPointers[r2];
				goto nextInstruction;
			} else {
				programCounter += 1;
				goto nextInstruction;
			}

		case OP_GEF:
			opStackOfs -= 2;

			if(((float *) opStack)[(uint8_t) (opStackOfs + 1)] >= ((float *) opStack)[(uint8_t) (opStackOfs + 2)])
			{
				programCounter = r2;	//vm->instructionPointers[r2];
				goto nextInstruction;
			} else {
				programCounter += 1;
				goto nextInstruction;
			}


		//===================================================================

		case OP_NEGI:
			opStack[opStackOfs] = -r0;
			goto nextInstruction;
		case OP_ADD:
			opStackOfs--;
			opStack[opStackOfs] = r1 + r0;
			goto nextInstruction;
		case OP_SUB:
			opStackOfs--;
			opStack[opStackOfs] = r1 - r0;
			goto nextInstruction;
		case OP_DIVI:
			opStackOfs--;
			opStack[opStackOfs] = r1 / r0;
			goto nextInstruction;
		case OP_DIVU:
			opStackOfs--;
			opStack[opStackOfs] = ((unsigned) r1) / ((unsigned) r0);
			goto nextInstruction;
		case OP_MODI:
			opStackOfs--;
			opStack[opStackOfs] = r1 % r0;
			goto nextInstruction;
		case OP_MODU:
			opStackOfs--;
			opStack[opStackOfs] = ((unsigned) r1) % ((unsigned) r0);
			goto nextInstruction;
		case OP_MULI:
			opStackOfs--;
			opStack[opStackOfs] = r1 * r0;
			goto nextInstruction;
		case OP_MULU:
			opStackOfs--;
			opStack[opStackOfs] = ((unsigned) r1) * ((unsigned) r0);
			goto nextInstruction;

		case OP_BAND:
			opStackOfs--;
			opStack[opStackOfs] = ((unsigned) r1) & ((unsigned) r0);
			goto nextInstruction;
		case OP_BOR:
			opStackOfs--;
			opStack[opStackOfs] = ((unsigned) r1) | ((unsigned) r0);
			goto nextInstruction;
		case OP_BXOR:
			opStackOfs--;
			opStack[opStackOfs] = ((unsigned) r1) ^ ((unsigned) r0);
			goto nextInstruction;
		case OP_BCOM:
			opStack[opStackOfs] = ~((unsigned) r0);
			goto nextInstruction;

		case OP_LSH:
			opStackOfs--;
			opStack[opStackOfs] = r1 << r0;
			goto nextInstruction;
		case OP_RSHI:
			opStackOfs--;
			opStack[opStackOfs] = r1 >> r0;
			goto nextInstruction;
		case OP_RSHU:
			opStackOfs--;
			opStack[opStackOfs] = ((unsigned) r1) >> r0;
			goto nextInstruction;

		case OP_NEGF:
			((float *) opStack)[opStackOfs] =  -((float *) opStack)[opStackOfs];
			goto nextInstruction;
		case OP_ADDF:
			opStackOfs--;
			((float *) opStack)[opStackOfs] = ((float *) opStack)[opStackOfs] + ((float *) opStack)[(uint8_t) (opStackOfs + 1)];
			goto nextInstruction;
		case OP_SUBF:
			opStackOfs--;
			((float *) opStack)[opStackOfs] = ((float *) opStack)[opStackOfs] - ((float *) opStack)[(uint8_t) (opStackOfs + 1)];
			goto nextInstruction;
		case OP_DIVF:
			opStackOfs--;
			((float *) opStack)[opStackOfs] = ((float *) opStack)[opStackOfs] / ((float *) opStack)[(uint8_t) (opStackOfs + 1)];
			goto nextInstruction;
		case OP_MULF:
			opStackOfs--;
			((float *) opStack)[opStackOfs] = ((float *) opStack)[opStackOfs] * ((float *) opStack)[(uint8_t) (opStackOfs + 1)];
			goto nextInstruction;

		case OP_CVIF:
			((float *) opStack)[opStackOfs] = (float) opStack[opStackOfs];
			goto nextInstruction;
		case OP_CVFI:
			opStack[opStackOfs] = Q_ftol(((float *) opStack)[opStackOfs]);
			goto nextInstruction;
		case OP_SEX8:
			opStack[opStackOfs] = (signed char) opStack[opStackOfs];
			goto nextInstruction;
		case OP_SEX16:
			opStack[opStackOfs] = (short) opStack[opStackOfs];
			goto nextInstruction;
		}
	}

done:
	vm->currentlyInterpreting = qfalse;

	if (opStackOfs != 1 || *opStack != 0xDEADBEEF)
		Com_Error(ERR_DROP, "Interpreter error: opStack[0] = %X, opStackOfs = %d", opStack[0], opStackOfs);

	vm->programStack = stackOnEntry;

	// return the result
	return opStack[opStackOfs];
}