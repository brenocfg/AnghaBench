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
struct vmspace {int dummy; } ;
struct thread {TYPE_1__* td_proc; } ;
struct pmap {int* pm_context; int pm_tsb; int /*<<< orphan*/  pm_active; } ;
struct TYPE_2__ {struct vmspace* p_vmspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_DMMU_PCXR ; 
 int /*<<< orphan*/  AA_DMMU_TSB ; 
 int /*<<< orphan*/  AA_IMMU_TSB ; 
 int /*<<< orphan*/  ASI_DMMU ; 
 int /*<<< orphan*/  ASI_IMMU ; 
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET_ATOMIC (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERNBASE ; 
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ PCPU_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,...) ; 
 int TLB_CXR_PGSZ_MASK ; 
 int /*<<< orphan*/  atomic_store_acq_ptr (uintptr_t*,uintptr_t) ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 size_t curcpu ; 
 int /*<<< orphan*/  flush (int /*<<< orphan*/ ) ; 
 int ldxa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap ; 
 int /*<<< orphan*/  stxa (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tlb_ctx ; 
 int /*<<< orphan*/  tlb_ctx_max ; 
 int /*<<< orphan*/  tlb_ctx_min ; 
 int /*<<< orphan*/  tlb_flush_user () ; 
 struct pmap* vmspace_pmap (struct vmspace*) ; 

void
pmap_activate(struct thread *td)
{
	struct vmspace *vm;
	struct pmap *pm;
	int context;

	critical_enter();
	vm = td->td_proc->p_vmspace;
	pm = vmspace_pmap(vm);

	context = PCPU_GET(tlb_ctx);
	if (context == PCPU_GET(tlb_ctx_max)) {
		tlb_flush_user();
		context = PCPU_GET(tlb_ctx_min);
	}
	PCPU_SET(tlb_ctx, context + 1);

	pm->pm_context[curcpu] = context;
#ifdef SMP
	CPU_SET_ATOMIC(PCPU_GET(cpuid), &pm->pm_active);
	atomic_store_acq_ptr((uintptr_t *)PCPU_PTR(pmap), (uintptr_t)pm);
#else
	CPU_SET(PCPU_GET(cpuid), &pm->pm_active);
	PCPU_SET(pmap, pm);
#endif

	stxa(AA_DMMU_TSB, ASI_DMMU, pm->pm_tsb);
	stxa(AA_IMMU_TSB, ASI_IMMU, pm->pm_tsb);
	stxa(AA_DMMU_PCXR, ASI_DMMU, (ldxa(AA_DMMU_PCXR, ASI_DMMU) &
	    TLB_CXR_PGSZ_MASK) | context);
	flush(KERNBASE);
	critical_exit();
}