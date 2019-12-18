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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vm86frame {int vmf_trapno; uintptr_t vmf_ip; uintptr_t vmf_sp; int vmf_eflags; scalar_t__ kernel_ds; scalar_t__ kernel_es; scalar_t__ kernel_fs; scalar_t__ vmf_ss; scalar_t__ vmf_cs; } ;
struct vm86_kernel {int vm86_eflags; int /*<<< orphan*/  vm86_has_vme; } ;
struct TYPE_4__ {TYPE_1__* pcb_ext; } ;
struct TYPE_3__ {struct vm86_kernel ext_vm86; } ;

/* Variables and functions */
 int HLT ; 
 int INTn ; 
 int /*<<< orphan*/  MAKE_VEC (int /*<<< orphan*/ ,uintptr_t) ; 
 int PAGE_MASK ; 
 int PSL_USER ; 
 int PSL_VIF ; 
 int PSL_VM ; 
 TYPE_2__* curpcb ; 

void
vm86_prepcall(struct vm86frame *vmf)
{
	struct vm86_kernel *vm86;
	uint32_t *stack;
	uint8_t *code;

	code = (void *)0xa00;
	stack = (void *)(0x1000 - 2);	/* keep aligned */
	if ((vmf->vmf_trapno & PAGE_MASK) <= 0xff) {
		/* interrupt call requested */
		code[0] = INTn;
		code[1] = vmf->vmf_trapno & 0xff;
		code[2] = HLT;
		vmf->vmf_ip = (uintptr_t)code;
		vmf->vmf_cs = 0;
	} else {
		code[0] = HLT;
		stack--;
		stack[0] = MAKE_VEC(0, (uintptr_t)code);
	}
	vmf->vmf_sp = (uintptr_t)stack;
	vmf->vmf_ss = 0;
	vmf->kernel_fs = vmf->kernel_es = vmf->kernel_ds = 0;
	vmf->vmf_eflags = PSL_VIF | PSL_VM | PSL_USER;

	vm86 = &curpcb->pcb_ext->ext_vm86;
	if (!vm86->vm86_has_vme) 
		vm86->vm86_eflags = vmf->vmf_eflags;  /* save VIF, VIP */
}