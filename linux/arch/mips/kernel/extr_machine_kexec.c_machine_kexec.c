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
struct kimage {unsigned long start; scalar_t__ type; unsigned long head; int /*<<< orphan*/  control_code_page; } ;

/* Variables and functions */
 unsigned long IND_DESTINATION ; 
 unsigned long IND_DONE ; 
 unsigned long IND_INDIRECTION ; 
 unsigned long IND_SOURCE ; 
 scalar_t__ KEXEC_TYPE_DEFAULT ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  __flush_cache_all () ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 unsigned long kexec_indirection_page ; 
 int /*<<< orphan*/  kexec_ready_to_reboot ; 
 int /*<<< orphan*/  kexec_reboot () ; 
 scalar_t__ kexec_smp_wait ; 
 unsigned long kexec_start_address ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 unsigned long* phys_to_virt (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 long reboot_code_buffer ; 
 scalar_t__ relocate_new_kernel ; 
 int /*<<< orphan*/  relocate_new_kernel_size ; 
 void* relocated_kexec_smp_wait ; 
 int /*<<< orphan*/  set_cpu_online (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  smp_wmb () ; 

void
machine_kexec(struct kimage *image)
{
	unsigned long entry;
	unsigned long *ptr;

	reboot_code_buffer =
	  (unsigned long)page_address(image->control_code_page);

	kexec_start_address =
		(unsigned long) phys_to_virt(image->start);

	if (image->type == KEXEC_TYPE_DEFAULT) {
		kexec_indirection_page =
			(unsigned long) phys_to_virt(image->head & PAGE_MASK);
	} else {
		kexec_indirection_page = (unsigned long)&image->head;
	}

	memcpy((void*)reboot_code_buffer, relocate_new_kernel,
	       relocate_new_kernel_size);

	/*
	 * The generic kexec code builds a page list with physical
	 * addresses. they are directly accessible through KSEG0 (or
	 * CKSEG0 or XPHYS if on 64bit system), hence the
	 * phys_to_virt() call.
	 */
	for (ptr = &image->head; (entry = *ptr) && !(entry &IND_DONE);
	     ptr = (entry & IND_INDIRECTION) ?
	       phys_to_virt(entry & PAGE_MASK) : ptr + 1) {
		if (*ptr & IND_SOURCE || *ptr & IND_INDIRECTION ||
		    *ptr & IND_DESTINATION)
			*ptr = (unsigned long) phys_to_virt(*ptr);
	}

	/* Mark offline BEFORE disabling local irq. */
	set_cpu_online(smp_processor_id(), false);

	/*
	 * we do not want to be bothered.
	 */
	local_irq_disable();

	printk("Will call new kernel at %08lx\n", image->start);
	printk("Bye ...\n");
	/* Make reboot code buffer available to the boot CPU. */
	__flush_cache_all();
#ifdef CONFIG_SMP
	/* All secondary cpus now may jump to kexec_wait cycle */
	relocated_kexec_smp_wait = reboot_code_buffer +
		(void *)(kexec_smp_wait - relocate_new_kernel);
	smp_wmb();
	atomic_set(&kexec_ready_to_reboot, 1);
#endif
	kexec_reboot();
}