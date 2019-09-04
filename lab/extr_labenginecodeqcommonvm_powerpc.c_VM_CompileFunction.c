#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {long si; int i; long* ss; long* us; long b; } ;
struct TYPE_8__ {int op; int regR; long regPos; struct TYPE_8__* next; TYPE_1__ arg; int /*<<< orphan*/  i_count; } ;
typedef  TYPE_2__ source_instruction_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_INT ; 
 int /*<<< orphan*/  AsmCall ; 
 int /*<<< orphan*/  BlockCopy ; 
 int /*<<< orphan*/  DIE (char*) ; 
 int /*<<< orphan*/  EMIT_FALSE_CONST () ; 
 long FPRLEN ; 
 long GPRLEN ; 
 int /*<<< orphan*/  GPRLEN_SHIFT ; 
 int /*<<< orphan*/  MAYBE_EMIT_CONST () ; 
#define  OP_ADD 187 
#define  OP_ADDF 186 
#define  OP_ARG 185 
#define  OP_BAND 184 
#define  OP_BCOM 183 
#define  OP_BLOCK_COPY 182 
#define  OP_BOR 181 
#define  OP_BREAK 180 
#define  OP_BXOR 179 
#define  OP_CALL 178 
#define  OP_CONST 177 
#define  OP_CVFI 176 
#define  OP_CVIF 175 
#define  OP_DIVF 174 
#define  OP_DIVI 173 
#define  OP_DIVU 172 
#define  OP_ENTER 171 
#define  OP_EQ 170 
#define  OP_EQF 169 
#define  OP_GEF 168 
#define  OP_GEI 167 
#define  OP_GEU 166 
#define  OP_GTF 165 
#define  OP_GTI 164 
#define  OP_GTU 163 
#define  OP_IGNORE 162 
#define  OP_JUMP 161 
#define  OP_LEAVE 160 
#define  OP_LEF 159 
#define  OP_LEI 158 
#define  OP_LEU 157 
#define  OP_LOAD1 156 
#define  OP_LOAD2 155 
#define  OP_LOAD4 154 
#define  OP_LOCAL 153 
#define  OP_LSH 152 
#define  OP_LTF 151 
#define  OP_LTI 150 
#define  OP_LTU 149 
#define  OP_MODI 148 
#define  OP_MODU 147 
#define  OP_MULF 146 
#define  OP_MULI 145 
#define  OP_MULU 144 
#define  OP_NE 143 
#define  OP_NEF 142 
#define  OP_NEGF 141 
#define  OP_NEGI 140 
#define  OP_POP 139 
#define  OP_PUSH 138 
#define  OP_RSHI 137 
#define  OP_RSHU 136 
#define  OP_SEX16 135 
#define  OP_SEX8 134 
#define  OP_STORE1 133 
#define  OP_STORE2 132 
#define  OP_STORE4 131 
#define  OP_SUB 130 
#define  OP_SUBF 129 
#define  OP_UNDEF 128 
 int /*<<< orphan*/  PPC_EmitConst (TYPE_2__*) ; 
 int /*<<< orphan*/  PPC_Free (TYPE_2__*) ; 
 scalar_t__ RET_INT ; 
 int /*<<< orphan*/  STACK_LR ; 
 long STACK_RTEMP ; 
 long STACK_SAVE ; 
 long STACK_TEMP ; 
 int /*<<< orphan*/  VM_AnalyzeFunction (TYPE_2__* const,long*,long*,long*) ; 
 long VM_Data_Offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  branchAlways ; 
 int /*<<< orphan*/  branchExtLink ; 
 int /*<<< orphan*/  branchFalse ; 
 int /*<<< orphan*/  branchTrue ; 
 int cr7 ; 
 int /*<<< orphan*/  dataMask ; 
 int /*<<< orphan*/  emitEnd () ; 
 int /*<<< orphan*/  emitJump (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitStart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eq ; 
 long fFIRST ; 
 long fSECOND ; 
 long fTMP ; 
 int /*<<< orphan*/  floatBase ; 
 int force_emit ; 
 long* fpr_list ; 
 long fpr_vstart ; 
 long* gpr_list ; 
 long gpr_vstart ; 
 int /*<<< orphan*/  gt ; 
 int /*<<< orphan*/  iADD ; 
 int /*<<< orphan*/  iADDI ; 
 int /*<<< orphan*/  iADDIS ; 
 int /*<<< orphan*/  iAND ; 
 int /*<<< orphan*/  iB ; 
 int /*<<< orphan*/  iBCTR ; 
 int /*<<< orphan*/  iBCTRL ; 
 int /*<<< orphan*/  iBLR ; 
 int /*<<< orphan*/  iBLTm ; 
 int /*<<< orphan*/  iCMPLW ; 
 int /*<<< orphan*/  iCMPLWI ; 
 int /*<<< orphan*/  iCMPW ; 
 int /*<<< orphan*/  iCMPWI ; 
 int /*<<< orphan*/  iDIVW ; 
 int /*<<< orphan*/  iDIVWU ; 
 int /*<<< orphan*/  iEXTSB ; 
 int /*<<< orphan*/  iEXTSH ; 
 int /*<<< orphan*/  iFADDS ; 
 int /*<<< orphan*/  iFCMPU ; 
 int /*<<< orphan*/  iFCTIWZ ; 
 int /*<<< orphan*/  iFDIVS ; 
 int /*<<< orphan*/  iFMULS ; 
 int /*<<< orphan*/  iFNEG ; 
 int /*<<< orphan*/  iFRSP ; 
 int /*<<< orphan*/  iFSUB ; 
 int /*<<< orphan*/  iFSUBS ; 
 int /*<<< orphan*/  iLBZX ; 
 int /*<<< orphan*/  iLFD ; 
 int /*<<< orphan*/  iLFS ; 
 int /*<<< orphan*/  iLFSX ; 
 int /*<<< orphan*/  iLHZX ; 
 int /*<<< orphan*/  iLI ; 
 int /*<<< orphan*/  iLIS ; 
 int /*<<< orphan*/  iLL ; 
 int /*<<< orphan*/  iLLX ; 
 int /*<<< orphan*/  iLWZ ; 
 int /*<<< orphan*/  iLWZX ; 
 int /*<<< orphan*/  iMFLR ; 
 int /*<<< orphan*/  iMR ; 
 int /*<<< orphan*/  iMTCTR ; 
 int /*<<< orphan*/  iMTLR ; 
 int /*<<< orphan*/  iMULLW ; 
 int /*<<< orphan*/  iNEG ; 
 int /*<<< orphan*/  iNOP ; 
 int /*<<< orphan*/  iNOT ; 
 int /*<<< orphan*/  iOR ; 
 int /*<<< orphan*/  iORI ; 
 int /*<<< orphan*/  iPointers ; 
 int /*<<< orphan*/  iRLWINM ; 
 int /*<<< orphan*/  iSLW ; 
 int /*<<< orphan*/  iSRAW ; 
 int /*<<< orphan*/  iSRW ; 
 int /*<<< orphan*/  iSTBX ; 
 int /*<<< orphan*/  iSTFD ; 
 int /*<<< orphan*/  iSTFS ; 
 int /*<<< orphan*/  iSTFSX ; 
 int /*<<< orphan*/  iSTHX ; 
 int /*<<< orphan*/  iSTL ; 
 int /*<<< orphan*/  iSTLU ; 
 int /*<<< orphan*/  iSTW ; 
 int /*<<< orphan*/  iSTWX ; 
 int /*<<< orphan*/  iSUB ; 
 int /*<<< orphan*/  iXOR ; 
 int /*<<< orphan*/  iXORIS ; 
 int /*<<< orphan*/  in (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  lt ; 
 long r0 ; 
 long r1 ; 
 long r3 ; 
 long r4 ; 
 long r5 ; 
 long rDATABASE ; 
 long rFIRST ; 
 long rPSTACK ; 
 long rSECOND ; 
 int rTYPE_FLOAT ; 
 long rVMDATA ; 

__attribute__((used)) static void
VM_CompileFunction( source_instruction_t * const i_first )
{
	long int prepareStack = 0;
	long int gpr_start_pos, fpr_start_pos;

	VM_AnalyzeFunction( i_first, &prepareStack, &gpr_start_pos, &fpr_start_pos );

	long int gpr_pos = gpr_start_pos, fpr_pos = fpr_start_pos;

	// OP_CONST combines well with many opcodes so we treat it in a special way
	source_instruction_t *i_const = NULL;
	source_instruction_t *i_now = i_first;

	// how big the stack has to be
	long int save_space = STACK_SAVE;
	{
		if ( gpr_start_pos < gpr_vstart )
			save_space += (gpr_vstart - gpr_start_pos) * GPRLEN;
		save_space = ( save_space + 15 ) & ~0x0f;

		if ( fpr_start_pos < fpr_vstart )
			save_space += (fpr_vstart - fpr_start_pos) * FPRLEN;
		save_space = ( save_space + 15 ) & ~0x0f;
	}

	long int stack_temp = prepareStack ? STACK_TEMP : STACK_RTEMP;

	while ( (i_now = i_now->next) ) {
		emitStart( i_now->i_count );

		switch ( i_now->op )
		{
			default:
			case OP_UNDEF:
			case OP_IGNORE:
				MAYBE_EMIT_CONST();
				in( iNOP );
				break;

			case OP_BREAK:
				MAYBE_EMIT_CONST();
				// force SEGV
				in( iLWZ, r0, 0, r0 );
				break;

			case OP_ENTER:
				if ( i_const )
					DIE( "Weird opcode order" );

				// don't prepare stack if not needed
				if ( prepareStack ) {
					long int i, save_pos = STACK_SAVE;

					in( iMFLR, r0 );
					in( iSTLU, r1, -save_space, r1 );
					in( iSTL, r0, save_space + STACK_LR, r1 );

					/* save registers */
					for ( i = gpr_start_pos; i < gpr_vstart; i++ ) {
						in( iSTL, gpr_list[ i ], save_pos, r1 );
						save_pos += GPRLEN;
					}
					save_pos = ( save_pos + 15 ) & ~0x0f;

					for ( i = fpr_start_pos; i < fpr_vstart; i++ ) {
						in( iSTFD, fpr_list[ i ], save_pos, r1 );
						save_pos += FPRLEN;
					}
					prepareStack = 2;
				}

				in( iADDI, rPSTACK, rPSTACK, - i_now->arg.si );
				break;

			case OP_LEAVE:
				if ( i_const ) {
					EMIT_FALSE_CONST();

					if ( i_const->regR & rTYPE_FLOAT)
						DIE( "constant float in OP_LEAVE" );

					if ( i_const->arg.si >= -0x8000 && i_const->arg.si < 0x8000 ) {
						in( iLI, r3, i_const->arg.si );
					} else if ( i_const->arg.i < 0x10000 ) {
						in( iLI, r3, 0 );
						in( iORI, r3, r3, i_const->arg.i );
					} else {
						in( iLIS, r3, i_const->arg.ss[ 0 ] );
						if ( i_const->arg.us[ 1 ] != 0 )
							in( iORI, r3, r3, i_const->arg.us[ 1 ] );
					}
					gpr_pos--;
				} else {
					MAYBE_EMIT_CONST();

					/* place return value in r3 */
					if ( ARG_INT ) {
						if ( rFIRST != r3 )
							in( iMR, r3, rFIRST );
						gpr_pos--;
					} else {
						in( iSTFS, fFIRST, stack_temp, r1 );
						in( iLWZ, r3, stack_temp, r1 );
						fpr_pos--;
					}
				}

				// don't undo stack if not prepared
				if ( prepareStack >= 2 ) {
					long int i, save_pos = STACK_SAVE;

					in( iLL, r0, save_space + STACK_LR, r1 );


					/* restore registers */
					for ( i = gpr_start_pos; i < gpr_vstart; i++ ) {
						in( iLL, gpr_list[ i ], save_pos, r1 );
						save_pos += GPRLEN;
					}
					save_pos = ( save_pos + 15 ) & ~0x0f;
					for ( i = fpr_start_pos; i < fpr_vstart; i++ ) {
						in( iLFD, fpr_list[ i ], save_pos, r1 );
						save_pos += FPRLEN;
					}

					in( iMTLR, r0 );
					in( iADDI, r1, r1, save_space );
				}
				in( iADDI, rPSTACK, rPSTACK, i_now->arg.si);
				in( iBLR );
				assert( gpr_pos == gpr_start_pos );
				assert( fpr_pos == fpr_start_pos );
				break;

			case OP_CALL:
				if ( i_const ) {
					EMIT_FALSE_CONST();

					if ( i_const->arg.si >= 0 ) {
						emitJump(
							i_const->arg.i,
							branchAlways, 0, branchExtLink
						);
					} else {
						/* syscall */
						in( iLL, r0, VM_Data_Offset( AsmCall ), rVMDATA );

						in( iLI, r3, i_const->arg.si ); // negative value
						in( iMR, r4, rPSTACK ); // push PSTACK on argument list

						in( iMTCTR, r0 );
						in( iBCTRL );
					}
					if ( rFIRST != r3 )
						in( iMR, rFIRST, r3 );
				} else {
					MAYBE_EMIT_CONST();

					in( iCMPWI, cr7, rFIRST, 0 );
					in( iBLTm, cr7, +4*5 /* syscall */ ); // XXX jump !
					/* instruction call */

					// get instruction address
					in( iLL, r0, VM_Data_Offset( iPointers ), rVMDATA );
					in( iRLWINM, rFIRST, rFIRST, GPRLEN_SHIFT, 0, 31-GPRLEN_SHIFT ); // mul * GPRLEN
					in( iLLX, r0, rFIRST, r0 ); // load pointer

					in( iB, +4*(3 + (rFIRST != r3 ? 1 : 0) ) ); // XXX jump !

					/* syscall */
					in( iLL, r0, VM_Data_Offset( AsmCall ), rVMDATA ); // get asmCall pointer
					/* rFIRST can be r3 or some static register */
					if ( rFIRST != r3 )
						in( iMR, r3, rFIRST ); // push OPSTACK top value on argument list
					in( iMR, r4, rPSTACK ); // push PSTACK on argument list

					/* common code */
					in( iMTCTR, r0 );
					in( iBCTRL );

					if ( rFIRST != r3 )
						in( iMR, rFIRST, r3 ); // push return value on the top of the opstack
				}
				break;

			case OP_PUSH:
				MAYBE_EMIT_CONST();
				if ( RET_INT )
					gpr_pos++;
				else
					fpr_pos++;
				/* no instructions here */
				force_emit = 1;
				break;

			case OP_POP:
				MAYBE_EMIT_CONST();
				if ( ARG_INT )
					gpr_pos--;
				else
					fpr_pos--;
				/* no instructions here */
				force_emit = 1;
				break;

			case OP_CONST:
				MAYBE_EMIT_CONST();
				/* nothing here */
				break;

			case OP_LOCAL:
				MAYBE_EMIT_CONST();
				{
					signed long int hi, lo;
					hi = i_now->arg.ss[ 0 ];
					lo = i_now->arg.ss[ 1 ];
					if ( lo < 0 )
						hi += 1;

					gpr_pos++;
					if ( hi == 0 ) {
						in( iADDI, rFIRST, rPSTACK, lo );
					} else {
						in( iADDIS, rFIRST, rPSTACK, hi );
						if ( lo != 0 )
							in( iADDI, rFIRST, rFIRST, lo );
					}
				}
				break;

			case OP_JUMP:
				if ( i_const ) {
					EMIT_FALSE_CONST();

					emitJump(
						i_const->arg.i,
						branchAlways, 0, 0
					);
				} else {
					MAYBE_EMIT_CONST();

					in( iLL, r0, VM_Data_Offset( iPointers ), rVMDATA );
					in( iRLWINM, rFIRST, rFIRST, GPRLEN_SHIFT, 0, 31-GPRLEN_SHIFT ); // mul * GPRLEN
					in( iLLX, r0, rFIRST, r0 ); // load pointer
					in( iMTCTR, r0 );
					in( iBCTR );
				}
				gpr_pos--;
				break;

			case OP_EQ:
			case OP_NE:
				if ( i_const && i_const->arg.si >= -0x8000 && i_const->arg.si < 0x10000 ) {
					EMIT_FALSE_CONST();
					if ( i_const->arg.si >= 0x8000 )
						in( iCMPLWI, cr7, rSECOND, i_const->arg.i );
					else
						in( iCMPWI, cr7, rSECOND, i_const->arg.si );
				} else {
					MAYBE_EMIT_CONST();
					in( iCMPW, cr7, rSECOND, rFIRST );
				}
				emitJump(
					i_now->arg.i,
					(i_now->op == OP_EQ ? branchTrue : branchFalse),
					4*cr7+eq, 0
				);
				gpr_pos -= 2;
				break;

			case OP_LTI:
			case OP_GEI:
				if ( i_const && i_const->arg.si >= -0x8000 && i_const->arg.si < 0x8000 ) {
					EMIT_FALSE_CONST();
					in( iCMPWI, cr7, rSECOND, i_const->arg.si );
				} else {
					MAYBE_EMIT_CONST();
					in( iCMPW, cr7, rSECOND, rFIRST );
				}
				emitJump(
					i_now->arg.i,
					( i_now->op == OP_LTI ? branchTrue : branchFalse ),
					4*cr7+lt, 0
				);
				gpr_pos -= 2;
				break;

			case OP_GTI:
			case OP_LEI:
				if ( i_const && i_const->arg.si >= -0x8000 && i_const->arg.si < 0x8000 ) {
					EMIT_FALSE_CONST();
					in( iCMPWI, cr7, rSECOND, i_const->arg.si );
				} else {
					MAYBE_EMIT_CONST();
					in( iCMPW, cr7, rSECOND, rFIRST );
				}
				emitJump(
					i_now->arg.i,
					( i_now->op == OP_GTI ? branchTrue : branchFalse ),
					4*cr7+gt, 0
				);
				gpr_pos -= 2;
				break;

			case OP_LTU:
			case OP_GEU:
				if ( i_const && i_const->arg.i < 0x10000 ) {
					EMIT_FALSE_CONST();
					in( iCMPLWI, cr7, rSECOND, i_const->arg.i );
				} else {
					MAYBE_EMIT_CONST();
					in( iCMPLW, cr7, rSECOND, rFIRST );
				}
				emitJump(
					i_now->arg.i,
					( i_now->op == OP_LTU ? branchTrue : branchFalse ),
					4*cr7+lt, 0
				);
				gpr_pos -= 2;
				break;

			case OP_GTU:
			case OP_LEU:
				if ( i_const && i_const->arg.i < 0x10000 ) {
					EMIT_FALSE_CONST();
					in( iCMPLWI, cr7, rSECOND, i_const->arg.i );
				} else {
					MAYBE_EMIT_CONST();
					in( iCMPLW, cr7, rSECOND, rFIRST );
				}
				emitJump(
					i_now->arg.i,
					( i_now->op == OP_GTU ? branchTrue : branchFalse ),
					4*cr7+gt, 0
				);
				gpr_pos -= 2;
				break;

			case OP_EQF:
			case OP_NEF:
				MAYBE_EMIT_CONST();
				in( iFCMPU, cr7, fSECOND, fFIRST );
				emitJump(
					i_now->arg.i,
					( i_now->op == OP_EQF ? branchTrue : branchFalse ),
					4*cr7+eq, 0
				);
				fpr_pos -= 2;
				break;

			case OP_LTF:
			case OP_GEF:
				MAYBE_EMIT_CONST();
				in( iFCMPU, cr7, fSECOND, fFIRST );
				emitJump(
					i_now->arg.i,
					( i_now->op == OP_LTF ? branchTrue : branchFalse ),
					4*cr7+lt, 0
				);
				fpr_pos -= 2;
				break;

			case OP_GTF:
			case OP_LEF:
				MAYBE_EMIT_CONST();
				in( iFCMPU, cr7, fSECOND, fFIRST );
				emitJump(
					i_now->arg.i,
					( i_now->op == OP_GTF ? branchTrue : branchFalse ),
					4*cr7+gt, 0
				);
				fpr_pos -= 2;
				break;

			case OP_LOAD1:
				MAYBE_EMIT_CONST();
#if OPTIMIZE_MASK
				in( iRLWINM, rFIRST, rFIRST, 0, fastMaskHi, fastMaskLo );
#else
				in( iLWZ, r0, VM_Data_Offset( dataMask ), rVMDATA );
				in( iAND, rFIRST, rFIRST, r0 );
#endif
				in( iLBZX, rFIRST, rFIRST, rDATABASE );
				break;

			case OP_LOAD2:
				MAYBE_EMIT_CONST();
#if OPTIMIZE_MASK
				in( iRLWINM, rFIRST, rFIRST, 0, fastMaskHi, fastMaskLo );
#else
				in( iLWZ, r0, VM_Data_Offset( dataMask ), rVMDATA );
				in( iAND, rFIRST, rFIRST, r0 );
#endif
				in( iLHZX, rFIRST, rFIRST, rDATABASE );
				break;

			case OP_LOAD4:
				MAYBE_EMIT_CONST();
#if OPTIMIZE_MASK
				in( iRLWINM, rFIRST, rFIRST, 0, fastMaskHi, fastMaskLo );
#else
				in( iLWZ, r0, VM_Data_Offset( dataMask ), rVMDATA );
				in( iAND, rFIRST, rFIRST, r0 );
#endif
				if ( RET_INT ) {
					in( iLWZX, rFIRST, rFIRST, rDATABASE );
				} else {
					fpr_pos++;
					in( iLFSX, fFIRST, rFIRST, rDATABASE );
					gpr_pos--;
				}
				break;

			case OP_STORE1:
				MAYBE_EMIT_CONST();
#if OPTIMIZE_MASK
				in( iRLWINM, rSECOND, rSECOND, 0, fastMaskHi, fastMaskLo );
#else
				in( iLWZ, r0, VM_Data_Offset( dataMask ), rVMDATA );
				in( iAND, rSECOND, rSECOND, r0 );
#endif
				in( iSTBX, rFIRST, rSECOND, rDATABASE );
				gpr_pos -= 2;
				break;

			case OP_STORE2:
				MAYBE_EMIT_CONST();
#if OPTIMIZE_MASK
				in( iRLWINM, rSECOND, rSECOND, 0, fastMaskHi, fastMaskLo );
#else
				in( iLWZ, r0, VM_Data_Offset( dataMask ), rVMDATA );
				in( iAND, rSECOND, rSECOND, r0 );
#endif
				in( iSTHX, rFIRST, rSECOND, rDATABASE );
				gpr_pos -= 2;
				break;

			case OP_STORE4:
				MAYBE_EMIT_CONST();
				if ( ARG_INT ) {
#if OPTIMIZE_MASK
					in( iRLWINM, rSECOND, rSECOND, 0, fastMaskHi, fastMaskLo );
#else
					in( iLWZ, r0, VM_Data_Offset( dataMask ), rVMDATA );
					in( iAND, rSECOND, rSECOND, r0 );
#endif

					in( iSTWX, rFIRST, rSECOND, rDATABASE );
					gpr_pos--;
				} else {
#if OPTIMIZE_MASK
					in( iRLWINM, rFIRST, rFIRST, 0, fastMaskHi, fastMaskLo );
#else
					in( iLWZ, r0, VM_Data_Offset( dataMask ), rVMDATA );
					in( iAND, rFIRST, rFIRST, r0 );
#endif

					in( iSTFSX, fFIRST, rFIRST, rDATABASE );
					fpr_pos--;
				}
				gpr_pos--;
				break;

			case OP_ARG:
				MAYBE_EMIT_CONST();
				in( iADDI, r0, rPSTACK, i_now->arg.b );
				if ( ARG_INT ) {
					in( iSTWX, rFIRST, rDATABASE, r0 );
					gpr_pos--;
				} else {
					in( iSTFSX, fFIRST, rDATABASE, r0 );
					fpr_pos--;
				}
				break;

			case OP_BLOCK_COPY:
				MAYBE_EMIT_CONST();
#if OPTIMIZE_COPY
				if ( i_now->arg.i <= SL( 16, 32 ) ) {
					/* block is very short so copy it in-place */

					unsigned int len = i_now->arg.i;
					unsigned int copied = 0, left = len;

					in( iADD, rFIRST, rFIRST, rDATABASE );
					in( iADD, rSECOND, rSECOND, rDATABASE );

					if ( len >= GPRLEN ) {
						long int i, words = len / GPRLEN;
						in( iLL, r0, 0, rFIRST );
						for ( i = 1; i < words; i++ )
							in( iLL, rTEMP( i - 1 ), GPRLEN * i, rFIRST );

						in( iSTL, r0, 0, rSECOND );
						for ( i = 1; i < words; i++ )
							in( iSTL, rTEMP( i - 1 ), GPRLEN * i, rSECOND );

						copied += words * GPRLEN;
						left -= copied;
					}

					if ( SL( 0, left >= 4 ) ) {
						in( iLWZ, r0, copied+0, rFIRST );
						in( iSTW, r0, copied+0, rSECOND );
						copied += 4;
						left -= 4;
					}
					if ( left >= 4 ) {
						DIE("Bug in OP_BLOCK_COPY");
					}
					if ( left == 3 ) {
						in( iLHZ, r0,	copied+0, rFIRST );
						in( iLBZ, rTMP,	copied+2, rFIRST );
						in( iSTH, r0,	copied+0, rSECOND );
						in( iSTB, rTMP,	copied+2, rSECOND );
					} else if ( left == 2 ) {
						in( iLHZ, r0, copied+0, rFIRST );
						in( iSTH, r0, copied+0, rSECOND );
					} else if ( left == 1 ) {
						in( iLBZ, r0, copied+0, rFIRST );
						in( iSTB, r0, copied+0, rSECOND );
					}
				} else
#endif
				{
					unsigned long int r5_ori = 0;
					if ( i_now->arg.si >= -0x8000 && i_now->arg.si < 0x8000 ) {
						in( iLI, r5, i_now->arg.si );
					} else if ( i_now->arg.i < 0x10000 ) {
						in( iLI, r5, 0 );
						r5_ori = i_now->arg.i;
					} else {
						in( iLIS, r5, i_now->arg.ss[ 0 ] );
						r5_ori = i_now->arg.us[ 1 ];
					}

					in( iLL, r0, VM_Data_Offset( BlockCopy ), rVMDATA ); // get blockCopy pointer

					if ( r5_ori )
						in( iORI, r5, r5, r5_ori );

					in( iMTCTR, r0 );

					if ( rFIRST != r4 )
						in( iMR, r4, rFIRST );
					if ( rSECOND != r3 )
						in( iMR, r3, rSECOND );

					in( iBCTRL );
				}

				gpr_pos -= 2;
				break;

			case OP_SEX8:
				MAYBE_EMIT_CONST();
				in( iEXTSB, rFIRST, rFIRST );
				break;

			case OP_SEX16:
				MAYBE_EMIT_CONST();
				in( iEXTSH, rFIRST, rFIRST );
				break;

			case OP_NEGI:
				MAYBE_EMIT_CONST();
				in( iNEG, rFIRST, rFIRST );
				break;

			case OP_ADD:
				if ( i_const ) {
					EMIT_FALSE_CONST();

					signed short int hi, lo;
					hi = i_const->arg.ss[ 0 ];
					lo = i_const->arg.ss[ 1 ];
					if ( lo < 0 )
						hi += 1;

					if ( hi != 0 )
						in( iADDIS, rSECOND, rSECOND, hi );
					if ( lo != 0 )
						in( iADDI, rSECOND, rSECOND, lo );

					// if both are zero no instruction will be written
					if ( hi == 0 && lo == 0 )
						force_emit = 1;
				} else {
					MAYBE_EMIT_CONST();
					in( iADD, rSECOND, rSECOND, rFIRST );
				}
				gpr_pos--;
				break;

			case OP_SUB:
				MAYBE_EMIT_CONST();
				in( iSUB, rSECOND, rSECOND, rFIRST );
				gpr_pos--;
				break;

			case OP_DIVI:
				MAYBE_EMIT_CONST();
				in( iDIVW, rSECOND, rSECOND, rFIRST );
				gpr_pos--;
				break;

			case OP_DIVU:
				MAYBE_EMIT_CONST();
				in( iDIVWU, rSECOND, rSECOND, rFIRST );
				gpr_pos--;
				break;

			case OP_MODI:
				MAYBE_EMIT_CONST();
				in( iDIVW, r0, rSECOND, rFIRST );
				in( iMULLW, r0, r0, rFIRST );
				in( iSUB, rSECOND, rSECOND, r0 );
				gpr_pos--;
				break;

			case OP_MODU:
				MAYBE_EMIT_CONST();
				in( iDIVWU, r0, rSECOND, rFIRST );
				in( iMULLW, r0, r0, rFIRST );
				in( iSUB, rSECOND, rSECOND, r0 );
				gpr_pos--;
				break;

			case OP_MULI:
			case OP_MULU:
				MAYBE_EMIT_CONST();
				in( iMULLW, rSECOND, rSECOND, rFIRST );
				gpr_pos--;
				break;

			case OP_BAND:
				MAYBE_EMIT_CONST();
				in( iAND, rSECOND, rSECOND, rFIRST );
				gpr_pos--;
				break;

			case OP_BOR:
				MAYBE_EMIT_CONST();
				in( iOR, rSECOND, rSECOND, rFIRST );
				gpr_pos--;
				break;

			case OP_BXOR:
				MAYBE_EMIT_CONST();
				in( iXOR, rSECOND, rSECOND, rFIRST );
				gpr_pos--;
				break;

			case OP_BCOM:
				MAYBE_EMIT_CONST();
				in( iNOT, rFIRST, rFIRST );
				break;

			case OP_LSH:
				MAYBE_EMIT_CONST();
				in( iSLW, rSECOND, rSECOND, rFIRST );
				gpr_pos--;
				break;

			case OP_RSHI:
				MAYBE_EMIT_CONST();
				in( iSRAW, rSECOND, rSECOND, rFIRST );
				gpr_pos--;
				break;

			case OP_RSHU:
				MAYBE_EMIT_CONST();
				in( iSRW, rSECOND, rSECOND, rFIRST );
				gpr_pos--;
				break;

			case OP_NEGF:
				MAYBE_EMIT_CONST();
				in( iFNEG, fFIRST, fFIRST );
				break;

			case OP_ADDF:
				MAYBE_EMIT_CONST();
				in( iFADDS, fSECOND, fSECOND, fFIRST );
				fpr_pos--;
				break;

			case OP_SUBF:
				MAYBE_EMIT_CONST();
				in( iFSUBS, fSECOND, fSECOND, fFIRST );
				fpr_pos--;
				break;

			case OP_DIVF:
				MAYBE_EMIT_CONST();
				in( iFDIVS, fSECOND, fSECOND, fFIRST );
				fpr_pos--;
				break;

			case OP_MULF:
				MAYBE_EMIT_CONST();
				in( iFMULS, fSECOND, fSECOND, fFIRST );
				fpr_pos--;
				break;

			case OP_CVIF:
				MAYBE_EMIT_CONST();
				fpr_pos++;
				in( iXORIS, rFIRST, rFIRST, 0x8000 );
				in( iLIS, r0, 0x4330 );
				in( iSTW, rFIRST, stack_temp + 4, r1 );
				in( iSTW, r0, stack_temp, r1 );
				in( iLFS, fTMP, VM_Data_Offset( floatBase ), rVMDATA );
				in( iLFD, fFIRST, stack_temp, r1 );
				in( iFSUB, fFIRST, fFIRST, fTMP );
				in( iFRSP, fFIRST, fFIRST );
				gpr_pos--;
				break;

			case OP_CVFI:
				MAYBE_EMIT_CONST();
				gpr_pos++;
				in( iFCTIWZ, fFIRST, fFIRST );
				in( iSTFD, fFIRST, stack_temp, r1 );
				in( iLWZ, rFIRST, stack_temp + 4, r1 );
				fpr_pos--;
				break;
		}

		i_const = NULL;

		if ( i_now->op != OP_CONST ) {
			// emit the instructions if it isn't OP_CONST
			emitEnd();
		} else {
			// mark in what register the value should be saved
			if ( RET_INT )
				i_now->regPos = ++gpr_pos;
			else
				i_now->regPos = ++fpr_pos;

#if OPTIMIZE_HOLE
			i_const = i_now;
#else
			PPC_EmitConst( i_now );
#endif
		}
	}
	if ( i_const )
		DIE( "left (unused) OP_CONST" );

	{
		// free opcode information, don't free first dummy one
		source_instruction_t *i_next = i_first->next;
		while ( i_next ) {
			i_now = i_next;
			i_next = i_now->next;
			PPC_Free( i_now );
		}
	}
}