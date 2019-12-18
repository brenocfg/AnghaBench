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
typedef  unsigned long ulong ;
struct x86_emulate_ctxt {int op_bytes; unsigned long _eip; } ;
struct segmented_address {unsigned long ea; int /*<<< orphan*/  seg; } ;
typedef  enum x86emul_mode { ____Placeholder_x86emul_mode } x86emul_mode ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_SREG_CS ; 
 int X86EMUL_CONTINUE ; 
 int __linearize (struct x86_emulate_ctxt*,struct segmented_address,unsigned int*,int,int,int,int,unsigned long*) ; 

__attribute__((used)) static inline int assign_eip(struct x86_emulate_ctxt *ctxt, ulong dst,
			     enum x86emul_mode mode)
{
	ulong linear;
	int rc;
	unsigned max_size;
	struct segmented_address addr = { .seg = VCPU_SREG_CS,
					   .ea = dst };

	if (ctxt->op_bytes != sizeof(unsigned long))
		addr.ea = dst & ((1UL << (ctxt->op_bytes << 3)) - 1);
	rc = __linearize(ctxt, addr, &max_size, 1, false, true, mode, &linear);
	if (rc == X86EMUL_CONTINUE)
		ctxt->_eip = addr.ea;
	return rc;
}