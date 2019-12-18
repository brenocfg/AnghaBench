#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int i; } ;
struct src_insn {int dst_reg_flags; TYPE_1__ arg; int /*<<< orphan*/  i_count; } ;
struct func_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G0 ; 
 int /*<<< orphan*/  LDFI ; 
 int /*<<< orphan*/  ORI ; 
 int REG_FLAGS_FLOAT ; 
 int /*<<< orphan*/  SETHI ; 
 int /*<<< orphan*/  end_emit (struct func_info* const) ; 
 int /*<<< orphan*/  fFIRST (struct func_info* const) ; 
 int /*<<< orphan*/  in (int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  rFIRST (struct func_info* const) ; 
 int /*<<< orphan*/  rVMDATA ; 
 int sparc_push_data (struct func_info* const,int) ; 
 int /*<<< orphan*/  start_emit (struct func_info* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_emit_const(struct func_info * const fp, struct src_insn *sp)
{
	start_emit(fp, sp->i_count);
	if (sp->dst_reg_flags & REG_FLAGS_FLOAT) {
		in(LDFI, rVMDATA, sparc_push_data(fp, sp->arg.i), fFIRST(fp));
	} else {
		if ((sp->arg.i & ~0x3ff) == 0) {
			in(ORI, G0, sp->arg.i & 0x3ff, rFIRST(fp));
		} else if ((sp->arg.i & 0x3ff) == 0) {
			in(SETHI, sp->arg.i >> 10, rFIRST(fp));
		} else {
			in(SETHI, sp->arg.i >> 10, rFIRST(fp));
			in(ORI, rFIRST(fp), sp->arg.i & 0x3ff, rFIRST(fp));
		}
	}
	end_emit(fp);
}