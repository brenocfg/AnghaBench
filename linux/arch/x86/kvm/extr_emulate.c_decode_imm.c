#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct x86_emulate_ctxt {int /*<<< orphan*/  _eip; } ;
struct TYPE_3__ {int /*<<< orphan*/  ea; } ;
struct TYPE_4__ {TYPE_1__ mem; } ;
struct operand {unsigned int bytes; int val; TYPE_2__ addr; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_IMM ; 
 int X86EMUL_CONTINUE ; 
 void* insn_fetch (int /*<<< orphan*/ ,struct x86_emulate_ctxt*) ; 
 int /*<<< orphan*/  s16 ; 
 int /*<<< orphan*/  s32 ; 
 int /*<<< orphan*/  s64 ; 
 int /*<<< orphan*/  s8 ; 

__attribute__((used)) static int decode_imm(struct x86_emulate_ctxt *ctxt, struct operand *op,
		      unsigned size, bool sign_extension)
{
	int rc = X86EMUL_CONTINUE;

	op->type = OP_IMM;
	op->bytes = size;
	op->addr.mem.ea = ctxt->_eip;
	/* NB. Immediates are sign-extended as necessary. */
	switch (op->bytes) {
	case 1:
		op->val = insn_fetch(s8, ctxt);
		break;
	case 2:
		op->val = insn_fetch(s16, ctxt);
		break;
	case 4:
		op->val = insn_fetch(s32, ctxt);
		break;
	case 8:
		op->val = insn_fetch(s64, ctxt);
		break;
	}
	if (!sign_extension) {
		switch (op->bytes) {
		case 1:
			op->val &= 0xff;
			break;
		case 2:
			op->val &= 0xffff;
			break;
		case 4:
			op->val &= 0xffffffff;
			break;
		}
	}
done:
	return rc;
}