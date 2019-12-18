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
typedef  void* uint64_t ;
typedef  int uint32_t ;
struct vmcb_state {int dbgctl; int g_pat; int /*<<< orphan*/  dr7; int /*<<< orphan*/  dr6; int /*<<< orphan*/  efer; } ;
struct vmcb_ctrl {int np_enable; int v_intr_masking; int lbr_virt_en; scalar_t__ asid; void* n_cr3; void* msrpm_base_pa; void* iopm_base_pa; } ;
struct svm_softc {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DBREG_DR6_RESERVED1 ; 
 int /*<<< orphan*/  DBREG_DR7_RESERVED1 ; 
 int /*<<< orphan*/  EFER_SVM ; 
 int IDT_MC ; 
 int /*<<< orphan*/  PAT_UNCACHEABLE ; 
 int /*<<< orphan*/  PAT_UNCACHED ; 
 int PAT_VALUE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAT_WRITE_BACK ; 
 int /*<<< orphan*/  PAT_WRITE_THROUGH ; 
 int /*<<< orphan*/  VMCB_CR_INTCPT ; 
 int /*<<< orphan*/  VMCB_CTRL1_INTCPT ; 
 int /*<<< orphan*/  VMCB_CTRL2_INTCPT ; 
 int /*<<< orphan*/  VMCB_EXC_INTCPT ; 
 int VMCB_INTCPT_CPUID ; 
 int VMCB_INTCPT_FERR_FREEZE ; 
 int VMCB_INTCPT_INIT ; 
 int VMCB_INTCPT_INTR ; 
 int VMCB_INTCPT_IO ; 
 int VMCB_INTCPT_MONITOR ; 
 int VMCB_INTCPT_MSR ; 
 int VMCB_INTCPT_MWAIT ; 
 int VMCB_INTCPT_NMI ; 
 int VMCB_INTCPT_SHUTDOWN ; 
 int VMCB_INTCPT_SMI ; 
 int VMCB_INTCPT_VMRUN ; 
 int /*<<< orphan*/  svm_disable_intercept (struct svm_softc*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svm_enable_intercept (struct svm_softc*,int,int /*<<< orphan*/ ,int) ; 
 struct vmcb_ctrl* svm_get_vmcb_ctrl (struct svm_softc*,int) ; 
 struct vmcb_state* svm_get_vmcb_state (struct svm_softc*,int) ; 
 scalar_t__ vcpu_trace_exceptions (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vmcb_init(struct svm_softc *sc, int vcpu, uint64_t iopm_base_pa,
    uint64_t msrpm_base_pa, uint64_t np_pml4)
{
	struct vmcb_ctrl *ctrl;
	struct vmcb_state *state;
	uint32_t mask;
	int n;

	ctrl = svm_get_vmcb_ctrl(sc, vcpu);
	state = svm_get_vmcb_state(sc, vcpu);

	ctrl->iopm_base_pa = iopm_base_pa;
	ctrl->msrpm_base_pa = msrpm_base_pa;

	/* Enable nested paging */
	ctrl->np_enable = 1;
	ctrl->n_cr3 = np_pml4;

	/*
	 * Intercept accesses to the control registers that are not shadowed
	 * in the VMCB - i.e. all except cr0, cr2, cr3, cr4 and cr8.
	 */
	for (n = 0; n < 16; n++) {
		mask = (BIT(n) << 16) | BIT(n);
		if (n == 0 || n == 2 || n == 3 || n == 4 || n == 8)
			svm_disable_intercept(sc, vcpu, VMCB_CR_INTCPT, mask);
		else
			svm_enable_intercept(sc, vcpu, VMCB_CR_INTCPT, mask);
	}


	/*
	 * Intercept everything when tracing guest exceptions otherwise
	 * just intercept machine check exception.
	 */
	if (vcpu_trace_exceptions(sc->vm, vcpu)) {
		for (n = 0; n < 32; n++) {
			/*
			 * Skip unimplemented vectors in the exception bitmap.
			 */
			if (n == 2 || n == 9) {
				continue;
			}
			svm_enable_intercept(sc, vcpu, VMCB_EXC_INTCPT, BIT(n));
		}
	} else {
		svm_enable_intercept(sc, vcpu, VMCB_EXC_INTCPT, BIT(IDT_MC));
	}

	/* Intercept various events (for e.g. I/O, MSR and CPUID accesses) */
	svm_enable_intercept(sc, vcpu, VMCB_CTRL1_INTCPT, VMCB_INTCPT_IO);
	svm_enable_intercept(sc, vcpu, VMCB_CTRL1_INTCPT, VMCB_INTCPT_MSR);
	svm_enable_intercept(sc, vcpu, VMCB_CTRL1_INTCPT, VMCB_INTCPT_CPUID);
	svm_enable_intercept(sc, vcpu, VMCB_CTRL1_INTCPT, VMCB_INTCPT_INTR);
	svm_enable_intercept(sc, vcpu, VMCB_CTRL1_INTCPT, VMCB_INTCPT_INIT);
	svm_enable_intercept(sc, vcpu, VMCB_CTRL1_INTCPT, VMCB_INTCPT_NMI);
	svm_enable_intercept(sc, vcpu, VMCB_CTRL1_INTCPT, VMCB_INTCPT_SMI);
	svm_enable_intercept(sc, vcpu, VMCB_CTRL1_INTCPT, VMCB_INTCPT_SHUTDOWN);
	svm_enable_intercept(sc, vcpu, VMCB_CTRL1_INTCPT,
	    VMCB_INTCPT_FERR_FREEZE);

	svm_enable_intercept(sc, vcpu, VMCB_CTRL2_INTCPT, VMCB_INTCPT_MONITOR);
	svm_enable_intercept(sc, vcpu, VMCB_CTRL2_INTCPT, VMCB_INTCPT_MWAIT);

	/*
	 * From section "Canonicalization and Consistency Checks" in APMv2
	 * the VMRUN intercept bit must be set to pass the consistency check.
	 */
	svm_enable_intercept(sc, vcpu, VMCB_CTRL2_INTCPT, VMCB_INTCPT_VMRUN);

	/*
	 * The ASID will be set to a non-zero value just before VMRUN.
	 */
	ctrl->asid = 0;

	/*
	 * Section 15.21.1, Interrupt Masking in EFLAGS
	 * Section 15.21.2, Virtualizing APIC.TPR
	 *
	 * This must be set for %rflag and %cr8 isolation of guest and host.
	 */
	ctrl->v_intr_masking = 1;

	/* Enable Last Branch Record aka LBR for debugging */
	ctrl->lbr_virt_en = 1;
	state->dbgctl = BIT(0);

	/* EFER_SVM must always be set when the guest is executing */
	state->efer = EFER_SVM;

	/* Set up the PAT to power-on state */
	state->g_pat = PAT_VALUE(0, PAT_WRITE_BACK)	|
	    PAT_VALUE(1, PAT_WRITE_THROUGH)	|
	    PAT_VALUE(2, PAT_UNCACHED)		|
	    PAT_VALUE(3, PAT_UNCACHEABLE)	|
	    PAT_VALUE(4, PAT_WRITE_BACK)	|
	    PAT_VALUE(5, PAT_WRITE_THROUGH)	|
	    PAT_VALUE(6, PAT_UNCACHED)		|
	    PAT_VALUE(7, PAT_UNCACHEABLE);

	/* Set up DR6/7 to power-on state */
	state->dr6 = DBREG_DR6_RESERVED1;
	state->dr7 = DBREG_DR7_RESERVED1;
}