#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int type; } ;
typedef  TYPE_2__ tss_desc ;
struct desc_struct {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  active_mm; } ;
struct TYPE_7__ {int /*<<< orphan*/  x86_tss; } ;
struct TYPE_9__ {TYPE_1__ tss; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_TSS ; 
 size_t GDT_ENTRY_TSS ; 
 int /*<<< orphan*/  X86_FEATURE_SEP ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 TYPE_6__* current ; 
 int /*<<< orphan*/  enable_sep_cpu () ; 
 int /*<<< orphan*/  fpu__resume_cpu () ; 
 TYPE_5__* get_cpu_entry_area (int) ; 
 struct desc_struct* get_cpu_gdt_rw (int) ; 
 int /*<<< orphan*/  initialize_tlbstate_and_flush () ; 
 int /*<<< orphan*/  load_TR_desc () ; 
 int /*<<< orphan*/  load_fixmap_gdt (int) ; 
 int /*<<< orphan*/  load_mm_ldt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct desc_struct*,int) ; 
 int /*<<< orphan*/  set_tss_desc (int,int /*<<< orphan*/ *) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  syscall_init () ; 
 int /*<<< orphan*/  write_gdt_entry (struct desc_struct*,size_t,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fix_processor_context(void)
{
	int cpu = smp_processor_id();
#ifdef CONFIG_X86_64
	struct desc_struct *desc = get_cpu_gdt_rw(cpu);
	tss_desc tss;
#endif

	/*
	 * We need to reload TR, which requires that we change the
	 * GDT entry to indicate "available" first.
	 *
	 * XXX: This could probably all be replaced by a call to
	 * force_reload_TR().
	 */
	set_tss_desc(cpu, &get_cpu_entry_area(cpu)->tss.x86_tss);

#ifdef CONFIG_X86_64
	memcpy(&tss, &desc[GDT_ENTRY_TSS], sizeof(tss_desc));
	tss.type = 0x9; /* The available 64-bit TSS (see AMD vol 2, pg 91 */
	write_gdt_entry(desc, GDT_ENTRY_TSS, &tss, DESC_TSS);

	syscall_init();				/* This sets MSR_*STAR and related */
#else
	if (boot_cpu_has(X86_FEATURE_SEP))
		enable_sep_cpu();
#endif
	load_TR_desc();				/* This does ltr */
	load_mm_ldt(current->active_mm);	/* This does lldt */
	initialize_tlbstate_and_flush();

	fpu__resume_cpu();

	/* The processor is back on the direct GDT, load back the fixmap */
	load_fixmap_gdt(cpu);
}