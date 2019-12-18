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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  enum vm_reg_name { ____Placeholder_vm_reg_name } vm_reg_name ;

/* Variables and functions */
 int /*<<< orphan*/  BSP ; 
#define  MSR_EFER 128 
 int /*<<< orphan*/  USERBOOT_EXIT_QUIT ; 
 int VM_REG_GUEST_EFER ; 
 int VM_REG_LAST ; 
 int /*<<< orphan*/  cb_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int vm_set_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cb_setmsr(void *arg, int r, uint64_t v)
{
	int error;
	enum vm_reg_name vmreg;
	
	vmreg = VM_REG_LAST;

	switch (r) {
	case MSR_EFER:
		vmreg = VM_REG_GUEST_EFER;
		break;
	default:
		break;
	}

	if (vmreg == VM_REG_LAST) {
		printf("test_setmsr(%d): not implemented\n", r);
		cb_exit(NULL, USERBOOT_EXIT_QUIT);
	}

	error = vm_set_register(ctx, BSP, vmreg, v);
	if (error) {
		perror("vm_set_msr");
		cb_exit(NULL, USERBOOT_EXIT_QUIT);
	}
}