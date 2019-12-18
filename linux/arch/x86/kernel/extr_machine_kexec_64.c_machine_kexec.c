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
struct kimage {scalar_t__ type; int /*<<< orphan*/  preserve_context; int /*<<< orphan*/  start; scalar_t__ head; int /*<<< orphan*/  swap_page; int /*<<< orphan*/  control_code_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEXEC_CONTROL_CODE_MAX_SIZE ; 
 scalar_t__ KEXEC_TYPE_DEFAULT ; 
 int PAGES_NR ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 size_t PA_CONTROL_PAGE ; 
 size_t PA_SWAP_PAGE ; 
 size_t PA_TABLE_PAGE ; 
 size_t VA_CONTROL_PAGE ; 
 int /*<<< orphan*/  __ftrace_enabled_restore (int) ; 
 int __ftrace_enabled_save () ; 
 scalar_t__ __pa (void*) ; 
 int /*<<< orphan*/  clear_IO_APIC () ; 
 int /*<<< orphan*/  hw_breakpoint_disable () ; 
 int /*<<< orphan*/  load_segments () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  (*) (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ),int /*<<< orphan*/ ) ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 unsigned long page_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relocate_kernel (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_boot_irq_mode () ; 
 int /*<<< orphan*/  restore_processor_state () ; 
 int /*<<< orphan*/  save_processor_state () ; 
 int /*<<< orphan*/  set_gdt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_idt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sme_active () ; 
 unsigned long virt_to_phys (void*) ; 

void machine_kexec(struct kimage *image)
{
	unsigned long page_list[PAGES_NR];
	void *control_page;
	int save_ftrace_enabled;

#ifdef CONFIG_KEXEC_JUMP
	if (image->preserve_context)
		save_processor_state();
#endif

	save_ftrace_enabled = __ftrace_enabled_save();

	/* Interrupts aren't acceptable while we reboot */
	local_irq_disable();
	hw_breakpoint_disable();

	if (image->preserve_context) {
#ifdef CONFIG_X86_IO_APIC
		/*
		 * We need to put APICs in legacy mode so that we can
		 * get timer interrupts in second kernel. kexec/kdump
		 * paths already have calls to restore_boot_irq_mode()
		 * in one form or other. kexec jump path also need one.
		 */
		clear_IO_APIC();
		restore_boot_irq_mode();
#endif
	}

	control_page = page_address(image->control_code_page) + PAGE_SIZE;
	memcpy(control_page, relocate_kernel, KEXEC_CONTROL_CODE_MAX_SIZE);

	page_list[PA_CONTROL_PAGE] = virt_to_phys(control_page);
	page_list[VA_CONTROL_PAGE] = (unsigned long)control_page;
	page_list[PA_TABLE_PAGE] =
	  (unsigned long)__pa(page_address(image->control_code_page));

	if (image->type == KEXEC_TYPE_DEFAULT)
		page_list[PA_SWAP_PAGE] = (page_to_pfn(image->swap_page)
						<< PAGE_SHIFT);

	/*
	 * The segment registers are funny things, they have both a
	 * visible and an invisible part.  Whenever the visible part is
	 * set to a specific selector, the invisible part is loaded
	 * with from a table in memory.  At no other time is the
	 * descriptor table in memory accessed.
	 *
	 * I take advantage of this here by force loading the
	 * segments, before I zap the gdt with an invalid value.
	 */
	load_segments();
	/*
	 * The gdt & idt are now invalid.
	 * If you want to load them you must set up your own idt & gdt.
	 */
	set_gdt(phys_to_virt(0), 0);
	set_idt(phys_to_virt(0), 0);

	/* now call it */
	image->start = relocate_kernel((unsigned long)image->head,
				       (unsigned long)page_list,
				       image->start,
				       image->preserve_context,
				       sme_active());

#ifdef CONFIG_KEXEC_JUMP
	if (image->preserve_context)
		restore_processor_state();
#endif

	__ftrace_enabled_restore(save_ftrace_enabled);
}