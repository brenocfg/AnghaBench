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
typedef  int /*<<< orphan*/  ulong ;
typedef  int u64 ;
struct x86_emulate_ctxt {int mode; TYPE_1__* ops; } ;
struct desc_struct {scalar_t__ d; scalar_t__ l; } ;
typedef  enum x86emul_mode { ____Placeholder_x86emul_mode } x86emul_mode ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_msr ) (struct x86_emulate_ctxt*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int EFER_LMA ; 
 int /*<<< orphan*/  MSR_EFER ; 
 int X86EMUL_CONTINUE ; 
 scalar_t__ X86EMUL_MODE_PROT16 ; 
 int X86EMUL_MODE_PROT32 ; 
 int X86EMUL_MODE_PROT64 ; 
 int assign_eip (struct x86_emulate_ctxt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct x86_emulate_ctxt*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int assign_eip_far(struct x86_emulate_ctxt *ctxt, ulong dst,
			  const struct desc_struct *cs_desc)
{
	enum x86emul_mode mode = ctxt->mode;
	int rc;

#ifdef CONFIG_X86_64
	if (ctxt->mode >= X86EMUL_MODE_PROT16) {
		if (cs_desc->l) {
			u64 efer = 0;

			ctxt->ops->get_msr(ctxt, MSR_EFER, &efer);
			if (efer & EFER_LMA)
				mode = X86EMUL_MODE_PROT64;
		} else
			mode = X86EMUL_MODE_PROT32; /* temporary value */
	}
#endif
	if (mode == X86EMUL_MODE_PROT16 || mode == X86EMUL_MODE_PROT32)
		mode = cs_desc->d ? X86EMUL_MODE_PROT32 : X86EMUL_MODE_PROT16;
	rc = assign_eip(ctxt, dst, mode);
	if (rc == X86EMUL_CONTINUE)
		ctxt->mode = mode;
	return rc;
}