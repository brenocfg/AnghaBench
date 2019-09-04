#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ codeLength; scalar_t__ codeBase; int /*<<< orphan*/  name; int /*<<< orphan*/  compiled; int /*<<< orphan*/  (* destroy ) (TYPE_3__*) ;scalar_t__ instructionPointers; int /*<<< orphan*/  dataMask; } ;
typedef  TYPE_3__ vm_t ;
struct TYPE_16__ {int instructionCount; int codeOffset; } ;
typedef  TYPE_4__ vmHeader_t ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_14__ {unsigned int i; char b; } ;
struct TYPE_17__ {unsigned char op; unsigned long i_count; struct TYPE_17__* next; TYPE_2__ arg; scalar_t__ regPos; scalar_t__ regR; scalar_t__ regA2; scalar_t__ regA1; } ;
typedef  TYPE_5__ source_instruction_t ;
struct TYPE_13__ {char member_0; char member_1; char member_2; char member_3; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,unsigned long,unsigned long,...) ; 
 int /*<<< orphan*/  DIE (char*) ; 
 unsigned char OP_ENTER ; 
 int /*<<< orphan*/  PPC_CompileInit () ; 
 int /*<<< orphan*/  PPC_ComputeCode (TYPE_3__*) ; 
 int /*<<< orphan*/  PPC_Free (TYPE_5__*) ; 
 int /*<<< orphan*/  PPC_MakeFastMask (int /*<<< orphan*/ ) ; 
 TYPE_5__* PPC_Malloc (int) ; 
 int /*<<< orphan*/  PPC_ShrinkJumps () ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int /*<<< orphan*/  VM_CompileFunction (TYPE_5__*) ; 
 int /*<<< orphan*/  VM_Destroy_Compiled (TYPE_3__*) ; 
 int /*<<< orphan*/  Z_Free (scalar_t__) ; 
 scalar_t__ Z_Malloc (int) ; 
 void* di_pointers ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mprotect (scalar_t__,scalar_t__,int) ; 
 int opImm1 ; 
 int opImm4 ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  timersub (struct timeval*,struct timeval*,struct timeval*) ; 
 int* vm_opInfo ; 

void
VM_Compile( vm_t *vm, vmHeader_t *header )
{
	long int pc = 0;
	unsigned long int i_count;
	char* code;
	struct timeval tvstart = {0, 0};
	source_instruction_t *i_first /* dummy */, *i_last = NULL, *i_now;

	vm->compiled = qfalse;

	gettimeofday(&tvstart, NULL);

	PPC_MakeFastMask( vm->dataMask );

	i_first = PPC_Malloc( sizeof( source_instruction_t ) );
	i_first->next = NULL;

	// realloc instructionPointers with correct size
	// use Z_Malloc so vm.c will be able to free the memory
	if ( sizeof( void * ) != sizeof( int ) ) {
		Z_Free( vm->instructionPointers );
		vm->instructionPointers = Z_Malloc( header->instructionCount * sizeof( void * ) );
	}
	di_pointers = (void *)vm->instructionPointers;
	memset( di_pointers, 0, header->instructionCount * sizeof( void * ) );


	PPC_CompileInit();

	/*
	 * read the input program
	 * divide it into functions and send each function to compiler
	 */
	code = (char *)header + header->codeOffset;
	for ( i_count = 0; i_count < header->instructionCount; ++i_count )
	{
		unsigned char op = code[ pc++ ];

		if ( op == OP_ENTER ) {
			if ( i_first->next )
				VM_CompileFunction( i_first );
			i_first->next = NULL;
			i_last = i_first;
		}

		i_now = PPC_Malloc( sizeof( source_instruction_t ) );
		i_now->op = op;
		i_now->i_count = i_count;
		i_now->arg.i = 0;
		i_now->regA1 = 0;
		i_now->regA2 = 0;
		i_now->regR = 0;
		i_now->regPos = 0;
		i_now->next = NULL;

		if ( vm_opInfo[op] & opImm4 ) {
			union {
				unsigned char b[4];
				unsigned int i;
			} c = { { code[ pc + 3 ], code[ pc + 2 ], code[ pc + 1 ], code[ pc + 0 ] }, };

			i_now->arg.i = c.i;
			pc += 4;
		} else if ( vm_opInfo[op] & opImm1 ) {
			i_now->arg.b = code[ pc++ ];
		}

		i_last->next = i_now;
		i_last = i_now;
	}
	VM_CompileFunction( i_first );
	PPC_Free( i_first );

	PPC_ShrinkJumps();
	memset( di_pointers, 0, header->instructionCount * sizeof( void * ) );
	PPC_ComputeCode( vm );

	/* check for uninitialized pointers */
#ifdef DEBUG_VM
	long int i;
	for ( i = 0; i < header->instructionCount; i++ )
		if ( di_pointers[ i ] == 0 )
			Com_Printf( S_COLOR_RED "Pointer %ld not initialized !\n", i );
#endif

	/* mark memory as executable and not writeable */
	if ( mprotect( vm->codeBase, vm->codeLength, PROT_READ|PROT_EXEC ) ) {

		// it has failed, make sure memory is unmapped before throwing the error
		VM_Destroy_Compiled( vm );
		DIE( "mprotect failed" );
	}

	vm->destroy = VM_Destroy_Compiled;
	vm->compiled = qtrue;

	{
		struct timeval tvdone = {0, 0};
		struct timeval dur = {0, 0};
		Com_Printf( "VM file %s compiled to %i bytes of code (%p - %p)\n",
			vm->name, vm->codeLength, vm->codeBase, vm->codeBase+vm->codeLength );

		gettimeofday(&tvdone, NULL);
		timersub(&tvdone, &tvstart, &dur);
		Com_Printf( "compilation took %lu.%06lu seconds\n",
			(long unsigned int)dur.tv_sec, (long unsigned int)dur.tv_usec );
	}
}