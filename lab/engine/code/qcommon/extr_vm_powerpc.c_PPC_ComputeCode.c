#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {unsigned char* codeBase; size_t codeLength; scalar_t__ instructionPointers; int /*<<< orphan*/  dataMask; } ;
typedef  TYPE_2__ vm_t ;
struct TYPE_15__ {scalar_t__* function; int /*<<< orphan*/  env; int /*<<< orphan*/  toc; } ;
struct TYPE_17__ {scalar_t__* iPointers; int dataLength; int codeLength; int floatBase; int /*<<< orphan*/ * data; int /*<<< orphan*/  dataMask; scalar_t__ BlockCopy; scalar_t__ AsmCall; TYPE_1__ opd; } ;
typedef  TYPE_3__ vm_data_t ;
struct TYPE_18__ {unsigned long length; unsigned long i_count; size_t jump_to; int ext; long bo; long count; struct TYPE_18__* jump; struct TYPE_18__* next; int /*<<< orphan*/ * data; int /*<<< orphan*/  bi; void* parent; struct TYPE_18__* nextJump; int /*<<< orphan*/ * code; } ;
typedef  TYPE_4__ symbolic_jump_t ;
typedef  scalar_t__ ppc_instruction_t ;
typedef  int /*<<< orphan*/  powerpc_iname_t ;
struct TYPE_19__ {scalar_t__ function; int /*<<< orphan*/  env; int /*<<< orphan*/  toc; } ;
typedef  TYPE_5__ opd_t ;
typedef  TYPE_4__ local_data_t ;
typedef  TYPE_4__ dest_instruction_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIE (char*) ; 
 unsigned long FALSE_ICOUNT ; 
 scalar_t__ IN (int /*<<< orphan*/ ,...) ; 
 int MAP_ANONYMOUS ; 
 unsigned char* MAP_FAILED ; 
 int MAP_SHARED ; 
 int /*<<< orphan*/  PPC_Free (TYPE_4__*) ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 scalar_t__ VM_AsmCall ; 
 scalar_t__ VM_BlockCopy ; 
 int VM_Data_Offset (TYPE_3__) ; 
 long branchAlways ; 
 int branchExtLink ; 
#define  branchFalse 129 
#define  branchTrue 128 
 TYPE_3__* data ; 
 int data_acc ; 
 TYPE_4__* data_first ; 
 TYPE_4__* di_first ; 
 void** di_pointers ; 
 int /*<<< orphan*/  iB ; 
 int /*<<< orphan*/  iBC ; 
 int /*<<< orphan*/  iBCL ; 
 int /*<<< orphan*/  iBL ; 
 int /*<<< orphan*/  iNOP ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 unsigned char* mmap (int /*<<< orphan*/ *,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* sj_first ; 

__attribute__((used)) static void
PPC_ComputeCode( vm_t *vm )
{
	dest_instruction_t *di_now = di_first;

	unsigned long int codeInstructions = 0;
	// count total instruciton number
	while ( (di_now = di_now->next ) )
		codeInstructions += di_now->length;

	size_t codeLength = sizeof( vm_data_t )
		+ sizeof( unsigned int ) * data_acc
		+ sizeof( ppc_instruction_t ) * codeInstructions;

	// get the memory for the generated code, smarter ppcs need the
	// mem to be marked as executable (whill change later)
	unsigned char *dataAndCode = mmap( NULL, codeLength,
		PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0 );

	if (dataAndCode == MAP_FAILED)
		DIE( "Not enough memory" );

	ppc_instruction_t *codeNow, *codeBegin;
	codeNow = codeBegin = (ppc_instruction_t *)( dataAndCode + VM_Data_Offset( data[ data_acc ] ) );

	ppc_instruction_t nop = IN( iNOP );

	// copy instructions to the destination
	// fills the jump instructions with nops
	// saves pointers of all instructions
	di_now = di_first;
	while ( (di_now = di_now->next ) ) {
		unsigned long int i_count = di_now->i_count;
		if ( i_count != FALSE_ICOUNT ) {
			if ( ! di_pointers[ i_count ] )
				di_pointers[ i_count ] = (void *) codeNow;
		}

		if ( di_now->jump == NULL ) {
			memcpy( codeNow, &(di_now->code[0]), di_now->length * sizeof( ppc_instruction_t ) );
			codeNow += di_now->length;
		} else {
			long int i;
			symbolic_jump_t *sj;
			for ( i = 0; i < di_now->length; i++ )
				codeNow[ i ] = nop;
			codeNow += di_now->length;

			sj = di_now->jump;
			// save position of jumping instruction
			sj->parent = (void *)(codeNow - 1);
		}
	}

	// compute the jumps and write corresponding instructions
	symbolic_jump_t *sj_now = sj_first;
	while ( (sj_now = sj_now->nextJump ) ) {
		ppc_instruction_t *jumpFrom = (void *) sj_now->parent;
		ppc_instruction_t *jumpTo = (void *) di_pointers[ sj_now->jump_to ];
		signed long int jumpLength = jumpTo - jumpFrom;

		// if jump is short, just write it
		if ( jumpLength >= - 8192 && jumpLength < 8192 ) {
			powerpc_iname_t branchConditional = sj_now->ext & branchExtLink ? iBCL : iBC;
			*jumpFrom = IN( branchConditional, sj_now->bo, sj_now->bi, jumpLength * 4 );
			continue;
		}

		// jump isn't short so write it as two instructions
		//
		// the letter one is a non-conditional branch instruction which
		// accepts immediate values big enough (26 bits)
		*jumpFrom = IN( (sj_now->ext & branchExtLink ? iBL : iB), jumpLength * 4 );
		if ( sj_now->bo == branchAlways )
			continue;

		// there should have been additional space prepared for this case
		if ( jumpFrom[ -1 ] != nop )
			DIE( "additional space for long jump not prepared" );

		// invert instruction condition
		long int bo = 0;
		switch ( sj_now->bo ) {
			case branchTrue:
				bo = branchFalse;
				break;
			case branchFalse:
				bo = branchTrue;
				break;
			default:
				DIE( "unrecognized branch type" );
				break;
		}

		// the former instruction is an inverted conditional branch which
		// jumps over the non-conditional one
		jumpFrom[ -1 ] = IN( iBC, bo, sj_now->bi, +2*4 );
	}

	vm->codeBase = dataAndCode;
	vm->codeLength = codeLength;

	vm_data_t *data = (vm_data_t *)dataAndCode;

#if ELF64
	// prepare Official Procedure Descriptor for the generated code
	// and retrieve real function pointer for helper functions

	opd_t *ac = (void *)VM_AsmCall, *bc = (void *)VM_BlockCopy;
	data->opd.function = codeBegin;
	// trick it into using the same TOC
	// this way we won't have to switch TOC before calling AsmCall or BlockCopy
	data->opd.toc = ac->toc;
	data->opd.env = ac->env;

	data->AsmCall = ac->function;
	data->BlockCopy = bc->function;
#else
	data->AsmCall = VM_AsmCall;
	data->BlockCopy = VM_BlockCopy;
#endif

	data->dataMask = vm->dataMask;
	data->iPointers = (ppc_instruction_t *)vm->instructionPointers;
	data->dataLength = VM_Data_Offset( data[ data_acc ] );
	data->codeLength = ( codeNow - codeBegin ) * sizeof( ppc_instruction_t );
	data->floatBase = 0x59800004;


	/* write dynamic data (float constants) */
	{
		local_data_t *d_next, *d_now = data_first;
		long int accumulated = 0;

		do {
			long int i;
			for ( i = 0; i < d_now->count; i++ )
				data->data[ accumulated + i ] = d_now->data[ i ];

			accumulated += d_now->count;
			d_next = d_now->next;
			PPC_Free( d_now );

			if ( !d_next )
				break;
			d_now = d_next;
		} while (1);
		data_first = NULL;
	}

	/* free most of the compilation memory */
	{
		di_now = di_first->next;
		PPC_Free( di_first );
		PPC_Free( sj_first );

		while ( di_now ) {
			di_first = di_now->next;
			if ( di_now->jump )
				PPC_Free( di_now->jump );
			PPC_Free( di_now );
			di_now = di_first;
		}
	}
}