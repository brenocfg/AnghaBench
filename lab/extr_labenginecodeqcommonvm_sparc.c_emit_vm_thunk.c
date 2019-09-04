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
struct func_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA ; 
 int G0 ; 
 int I0 ; 
 int I1 ; 
 int I2 ; 
 int I3 ; 
 int I7 ; 
 int /*<<< orphan*/  JMPL ; 
 int /*<<< orphan*/  JMPLI ; 
 int L0 ; 
 int L1 ; 
 int L2 ; 
 int L3 ; 
 int O0 ; 
 int O1 ; 
 int O2 ; 
 int O3 ; 
 int O6 ; 
 int O7 ; 
 int /*<<< orphan*/  OR ; 
 int /*<<< orphan*/  RESTORE ; 
 int /*<<< orphan*/  SAVEI ; 
 int SL (int,int) ; 
 int /*<<< orphan*/  THUNK_ICOUNT ; 
 int /*<<< orphan*/  end_emit (struct func_info* const) ; 
 int /*<<< orphan*/  in (int /*<<< orphan*/ ,int,...) ; 
 int rDATABASE ; 
 int rDATAMASK ; 
 int rPSTACK ; 
 int rVMDATA ; 
 int /*<<< orphan*/  start_emit (struct func_info* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emit_vm_thunk(struct func_info * const fp)
{
	/* int vm_thunk(void *vmdata, int programstack, void *database, int datamask) */
	start_emit(fp, THUNK_ICOUNT);

	in(OR, G0, O0, rVMDATA);
	in(OR, G0, O1, rPSTACK);
	in(OR, G0, O2, rDATABASE);
	in(BA, +4*17);
	in(OR, G0, O3, rDATAMASK);

	/* int call_thunk(int arg0, int arg1, int arg2, int (*func)(int int int)) */
#define CALL_THUNK_INSN_OFFSET		5
	in(SAVEI, O6, -SL(64, 128), O6);

	in(OR, G0, rVMDATA, L0);
	in(OR, G0, rPSTACK, L1);
	in(OR, G0, rDATABASE, L2);
	in(OR, G0, rDATAMASK, L3);

	in(OR, G0, I0, O0);
	in(OR, G0, I1, O1);
	in(JMPL, I3, G0, O7);
	in(OR, G0, I2, O2);

	in(OR, G0, L0, rVMDATA);
	in(OR, G0, L1, rPSTACK);
	in(OR, G0, L2, rDATABASE);
	in(OR, G0, L3, rDATAMASK);

	in(JMPLI, I7, 8, G0);
	in(RESTORE, O0, G0, O0);

	end_emit(fp);
}