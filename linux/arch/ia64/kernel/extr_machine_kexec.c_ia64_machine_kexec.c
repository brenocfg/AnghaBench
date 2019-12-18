#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct unw_frame_info {scalar_t__ sw; } ;
struct kimage {scalar_t__ type; int /*<<< orphan*/  start; int /*<<< orphan*/  head; int /*<<< orphan*/  control_code_page; } ;
typedef  int /*<<< orphan*/  (* relocate_new_kernel_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct TYPE_5__ {int /*<<< orphan*/  fp; } ;
typedef  TYPE_2__ ia64_fptr_t ;
typedef  scalar_t__ __u64 ;
struct TYPE_4__ {scalar_t__ ksp; } ;
struct TYPE_6__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GRANULEROUNDDOWN (unsigned long) ; 
 scalar_t__ IA64_SPURIOUS_INT_VECTOR ; 
 scalar_t__ KEXEC_TYPE_CRASH ; 
 int /*<<< orphan*/  SAL_VECTOR_OS_INIT ; 
 int /*<<< orphan*/  SAL_VECTOR_OS_MCA ; 
 int /*<<< orphan*/  _IA64_REG_CR_CMCV ; 
 int /*<<< orphan*/  _IA64_REG_CR_PMV ; 
 int /*<<< orphan*/  _IA64_REG_CR_TPR ; 
 int /*<<< orphan*/  _IA64_REG_GP ; 
 int /*<<< orphan*/  crash_save_this_cpu () ; 
 TYPE_3__* current ; 
 void* efi_get_pal_addr () ; 
 int /*<<< orphan*/  ia64_boot_param ; 
 int /*<<< orphan*/  ia64_eoi () ; 
 scalar_t__ ia64_get_ivr () ; 
 int /*<<< orphan*/  ia64_getreg (int /*<<< orphan*/ ) ; 
 scalar_t__ ia64_os_init_on_kdump ; 
 int /*<<< orphan*/  ia64_sal_set_vectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia64_set_itv (int) ; 
 int /*<<< orphan*/  ia64_set_lrr0 (int) ; 
 int /*<<< orphan*/  ia64_set_lrr1 (int) ; 
 int /*<<< orphan*/  ia64_setreg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ia64_srlz_d () ; 
 int /*<<< orphan*/  ia64_tpa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ia64_machine_kexec(struct unw_frame_info *info, void *arg)
{
	struct kimage *image = arg;
	relocate_new_kernel_t rnk;
	void *pal_addr = efi_get_pal_addr();
	unsigned long code_addr;
	int ii;
	u64 fp, gp;
	ia64_fptr_t *init_handler = (ia64_fptr_t *)ia64_os_init_on_kdump;

	BUG_ON(!image);
	code_addr = (unsigned long)page_address(image->control_code_page);
	if (image->type == KEXEC_TYPE_CRASH) {
		crash_save_this_cpu();
		current->thread.ksp = (__u64)info->sw - 16;

		/* Register noop init handler */
		fp = ia64_tpa(init_handler->fp);
		gp = ia64_tpa(ia64_getreg(_IA64_REG_GP));
		ia64_sal_set_vectors(SAL_VECTOR_OS_INIT, fp, gp, 0, fp, gp, 0);
	} else {
		/* Unregister init handlers of current kernel */
		ia64_sal_set_vectors(SAL_VECTOR_OS_INIT, 0, 0, 0, 0, 0, 0);
	}

	/* Unregister mca handler - No more recovery on current kernel */
	ia64_sal_set_vectors(SAL_VECTOR_OS_MCA, 0, 0, 0, 0, 0, 0);

	/* Interrupts aren't acceptable while we reboot */
	local_irq_disable();

	/* Mask CMC and Performance Monitor interrupts */
	ia64_setreg(_IA64_REG_CR_PMV, 1 << 16);
	ia64_setreg(_IA64_REG_CR_CMCV, 1 << 16);

	/* Mask ITV and Local Redirect Registers */
	ia64_set_itv(1 << 16);
	ia64_set_lrr0(1 << 16);
	ia64_set_lrr1(1 << 16);

	/* terminate possible nested in-service interrupts */
	for (ii = 0; ii < 16; ii++)
		ia64_eoi();

	/* unmask TPR and clear any pending interrupts */
	ia64_setreg(_IA64_REG_CR_TPR, 0);
	ia64_srlz_d();
	while (ia64_get_ivr() != IA64_SPURIOUS_INT_VECTOR)
		ia64_eoi();
	rnk = (relocate_new_kernel_t)&code_addr;
	(*rnk)(image->head, image->start, ia64_boot_param,
		     GRANULEROUNDDOWN((unsigned long) pal_addr));
	BUG();
}