#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int si; int i; int* us; int /*<<< orphan*/ * ss; } ;
struct TYPE_5__ {int regR; long regPos; TYPE_1__ arg; int /*<<< orphan*/  i_count; } ;
typedef  TYPE_2__ source_instruction_t ;

/* Variables and functions */
 int /*<<< orphan*/  PPC_PushData (int) ; 
 int /*<<< orphan*/  emitEnd () ; 
 int /*<<< orphan*/  emitStart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fFIRST ; 
 int /*<<< orphan*/  iLFS ; 
 int /*<<< orphan*/  iLI ; 
 int /*<<< orphan*/  iLIS ; 
 int /*<<< orphan*/  iORI ; 
 int /*<<< orphan*/  in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  rFIRST ; 
 int rTYPE_FLOAT ; 
 int rVMDATA ; 

__attribute__((used)) static void
PPC_EmitConst( source_instruction_t * const i_const )
{
	emitStart( i_const->i_count );

	if ( !(i_const->regR & rTYPE_FLOAT) ) {
		// gpr_pos needed for "rFIRST" to work
		long int gpr_pos = i_const->regPos;

		if ( i_const->arg.si >= -0x8000 && i_const->arg.si < 0x8000 ) {
			in( iLI, rFIRST, i_const->arg.si );
		} else if ( i_const->arg.i < 0x10000 ) {
			in( iLI, rFIRST, 0 );
			in( iORI, rFIRST, rFIRST, i_const->arg.i );
		} else {
			in( iLIS, rFIRST, i_const->arg.ss[ 0 ] );
			if ( i_const->arg.us[ 1 ] != 0 )
				in( iORI, rFIRST, rFIRST, i_const->arg.us[ 1 ] );
		}

	} else {
		// fpr_pos needed for "fFIRST" to work
		long int fpr_pos = i_const->regPos;

		// there's no good way to generate the data,
		// just read it from data section
		in( iLFS, fFIRST, PPC_PushData( i_const->arg.i ), rVMDATA );
	}

	emitEnd();
}