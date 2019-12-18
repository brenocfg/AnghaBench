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
struct TYPE_2__ {unsigned long address; scalar_t__ size; } ;
struct saved_context {int misc_enable_saved; int /*<<< orphan*/  misc_enable; int /*<<< orphan*/  cr4; int /*<<< orphan*/  cr3; int /*<<< orphan*/  cr2; int /*<<< orphan*/  cr0; int /*<<< orphan*/  efer; int /*<<< orphan*/  usermode_gs_base; int /*<<< orphan*/  kernelmode_gs_base; int /*<<< orphan*/  fs_base; int /*<<< orphan*/  es; int /*<<< orphan*/  ds; int /*<<< orphan*/  fs; int /*<<< orphan*/  gs; int /*<<< orphan*/  tr; TYPE_1__ gdt_desc; int /*<<< orphan*/  idt; } ;

/* Variables and functions */
 scalar_t__ GDT_SIZE ; 
 int /*<<< orphan*/  MSR_EFER ; 
 int /*<<< orphan*/  MSR_FS_BASE ; 
 int /*<<< orphan*/  MSR_GS_BASE ; 
 int /*<<< orphan*/  MSR_IA32_MISC_ENABLE ; 
 int /*<<< orphan*/  MSR_KERNEL_GS_BASE ; 
 int /*<<< orphan*/  __read_cr3 () ; 
 int /*<<< orphan*/  __read_cr4 () ; 
 int /*<<< orphan*/  ds ; 
 int /*<<< orphan*/  es ; 
 int /*<<< orphan*/  fs ; 
 scalar_t__ get_cpu_gdt_rw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  msr_save_context (struct saved_context*) ; 
 int /*<<< orphan*/  mtrr_save_fixed_ranges (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdmsrl_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_cr0 () ; 
 int /*<<< orphan*/  read_cr2 () ; 
 int /*<<< orphan*/  savesegment (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  store_idt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_tr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __save_processor_state(struct saved_context *ctxt)
{
#ifdef CONFIG_X86_32
	mtrr_save_fixed_ranges(NULL);
#endif
	kernel_fpu_begin();

	/*
	 * descriptor tables
	 */
	store_idt(&ctxt->idt);

	/*
	 * We save it here, but restore it only in the hibernate case.
	 * For ACPI S3 resume, this is loaded via 'early_gdt_desc' in 64-bit
	 * mode in "secondary_startup_64". In 32-bit mode it is done via
	 * 'pmode_gdt' in wakeup_start.
	 */
	ctxt->gdt_desc.size = GDT_SIZE - 1;
	ctxt->gdt_desc.address = (unsigned long)get_cpu_gdt_rw(smp_processor_id());

	store_tr(ctxt->tr);

	/* XMM0..XMM15 should be handled by kernel_fpu_begin(). */
	/*
	 * segment registers
	 */
#ifdef CONFIG_X86_32_LAZY_GS
	savesegment(gs, ctxt->gs);
#endif
#ifdef CONFIG_X86_64
	savesegment(gs, ctxt->gs);
	savesegment(fs, ctxt->fs);
	savesegment(ds, ctxt->ds);
	savesegment(es, ctxt->es);

	rdmsrl(MSR_FS_BASE, ctxt->fs_base);
	rdmsrl(MSR_GS_BASE, ctxt->kernelmode_gs_base);
	rdmsrl(MSR_KERNEL_GS_BASE, ctxt->usermode_gs_base);
	mtrr_save_fixed_ranges(NULL);

	rdmsrl(MSR_EFER, ctxt->efer);
#endif

	/*
	 * control registers
	 */
	ctxt->cr0 = read_cr0();
	ctxt->cr2 = read_cr2();
	ctxt->cr3 = __read_cr3();
	ctxt->cr4 = __read_cr4();
	ctxt->misc_enable_saved = !rdmsrl_safe(MSR_IA32_MISC_ENABLE,
					       &ctxt->misc_enable);
	msr_save_context(ctxt);
}